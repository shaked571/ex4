//
// Created by shaked571 on 6/10/17.
//

#ifndef EX4_FBRALGORITHM_H
#define EX4_FBRALGORITHM_H

#include "Algorithm.h"

class CacheAlgorithm :public Algorithm{
public:
    CacheAlgorithm(int blocks_num,double f_old , double f_new, cache_algo_t algoName );

    void addBlockToCache(Block* block);


private:
};


#endif //EX4_FBRALGORITHM_H
