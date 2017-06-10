//
// Created by shaked571 on 6/10/17.
//

#ifndef EX4_LRUALGORITHM_H
#define EX4_LRUALGORITHM_H

#include "Algorithm.h"

class LruAlgorithm:Algorithm
{

public:
    LruAlgorithm(int blocks_num);

    int ChachePread(int file_id, void *buf, size_t count, off_t offset)override;
};


#endif //EX4_LRUALGORITHM_H
