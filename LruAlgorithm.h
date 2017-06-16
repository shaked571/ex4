//
// Created by shaked571 on 6/10/17.
//

#ifndef EX4_LRUALGORITHM_H
#define EX4_LRUALGORITHM_H

#include "Algorithm.h"

class LruAlgorithm:public Algorithm
{

public:
    LruAlgorithm(int blocks_num);
    void addBlockToCache(Block* block);
};


#endif //EX4_LRUALGORITHM_H
