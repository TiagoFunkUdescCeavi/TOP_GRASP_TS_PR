#include "OperatorWorstRemove.h"
#include "Utils.h"

#include <iostream>

void OperatorWorstRemove::initialize(){
    this->is_empty = true;
    this->update_worst( 0.0, 0.0, 0, 1 );
}

void OperatorWorstRemove::check_if_not_empty( Solution * sol ){
    for( int i = 0; i < sol->get_number_paths(); i++ ){
        if( sol->get_length_of_path( i ) != 2 ){
            worst_reward = sol->get_vertice_in_path( i, 1 )->get_reward();
            worst_distance = sol->get_distance( 0, 1 );
            worst_path = i;
            is_empty = false;
            break;
        }
    }
}

void OperatorWorstRemove::find_worst( Solution * sol ){
    double d = 0.0;
    Vertice * v = 0;
    for( int i = 0; i < sol->get_number_paths(); i++ ){
        for( int j = 1; j < sol->get_length_of_path( i ) - 1; j++ ){
            d = sol->get_distance( i, j );
            v = sol->get_vertice_in_path( i, j );
            if( this->worst_reward > v->get_reward() ){
                this->update_worst( v->get_reward(), d, i, j );

            }else if( this->worst_reward == v->get_reward() ){
                if( this->worst_distance > d ){
                    this->update_worst( v->get_reward(), d, i, j );
                    
                }
            }
        }
    }
}

void OperatorWorstRemove::update_worst( double worst_reward, double worst_distance, int worst_path, int worst_position ){
    this->worst_reward = worst_reward;
    this->worst_distance = worst_distance;
    this->worst_path = worst_path;
    this->worst_position = worst_position;
}

Solution * OperatorWorstRemove::remove_worst( Solution * sol ){
    Vertice * v = sol->get_vertice_in_path( this->worst_path, this->worst_position );
    sol->remove( this->worst_path, this->worst_position );
    this->unused_vertices.push_back( v );
    return sol;
}

Solution * OperatorWorstRemove::execute( Solution * sol, vector< Vertice * > unused_vertices ){
    this->initialize();

    this->check_if_not_empty( sol );
    if( this->is_empty ) return sol;

    this->unused_vertices = unused_vertices;
    Solution * actual = new Solution( *sol );

    this->find_worst( actual );

    actual = this->remove_worst( actual );
    delete sol;
    return actual;
}