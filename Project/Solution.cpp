#include "Solution.h"

#include "Utils.h"

Solution::Solution( int number_paths, double time_per_path ){
    this->paths.resize( number_paths );
    this->path_rewards.resize( number_paths );
    this->path_times.resize( number_paths );
    this->time_per_path = time_per_path;
    this->total_rewards = 0.0;
}

void Solution::update_reward_in_add( int path, Vertice * v ){
    this->path_rewards[ path ] += v->get_reward();
    this->total_rewards += v->get_reward();
}

double Solution::calculate_time_in_add( int path, int position, Vertice * v ){
    double d1 = calculate_distance( this->paths[ path ][ position-1 ], this->paths[ path ][ position ] );
    double d2 = calculate_distance( this->paths[ path ][ position-1 ], v );
    double d3 = calculate_distance( this->paths[ path ][ position ], v );
    return this->path_times[ path ] - d1 + d2 + d3;
}

bool Solution::add_initial_and_final_vertice( int path, Vertice * initial, Vertice * final ){
    if( path < 0 || (unsigned int) path >= this->paths.size() ){
        return false;
    }
    this->paths[ path ].push_back( initial );
    this->paths[ path ].push_back( final );
    this->path_times[ path ] = calculate_distance( initial, final );
    return true;
}

bool Solution::add_vertice( int path, Vertice * v ){
    if( path < 0 ||  (unsigned int) path >= this->paths.size() ){
        return false;
    }

    int position = this->paths[ path ].size() - 1;
    double n_time = calculate_time_in_add( path, position, v );

    if( this->time_per_path > n_time ){
        this->paths[ path ].insert( this->paths[ path ].begin() + position, v );
        update_reward_in_add( path, v );
        this->path_times[ path ] = n_time;
        return true;
    }
    
    return false;
}

Vertice * Solution::get_last_path_vertice_in_path( int path ){
    if( path < 0 || (unsigned int) path >= this->paths.size() ){
        return 0;
    }
    int last_position = this->paths[ path ].size() - 1;
    return this->paths[ path ][ last_position ];
}

double Solution::get_total_rewards(){
    return this->total_rewards;
}

string Solution::to_string(){
    string s;
    s = "number paths: " + std::to_string(this->paths.size()) + "\n";
    s += "total reward: " + std::to_string( this->total_rewards ) + "\n";
    s += "paths:\n";
    for (unsigned int i = 0; i < this->paths.size(); i++){
        s += "size: " + std::to_string( this->paths[ i ].size() ) + "\n" ;
        for (unsigned int j = 0; j < this->paths[ i ].size(); j++){
            s += this->paths[ i ][ j ]->to_string() + "\n";
        }
        s += "reward: " + std::to_string( this->path_rewards[ i ])+"\n";
        s += "time: " + std::to_string( this->path_times[ i ])+"\n";
        s += ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
    }
    s += "total reward: " + std::to_string( this->total_rewards ) + "\n";
    
    return s;
}