//
// Created by shaked571 on 6/10/17.
//

#ifndef EX4_LFUALGORITHM_H
#define EX4_LFUALGORITHM_H

#include "Algorithm.h"

class LfuAlgorithm :public Algorithm{
public:
    LfuAlgorithm(int blocks_num);
    void addBlockToCache(Block* block);



};


#endif //EX4_LFUALGORITHM_H
