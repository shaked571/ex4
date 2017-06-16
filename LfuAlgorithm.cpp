//
// Created by shaked571 on 6/10/17.
//

#include "LfuAlgorithm.h"

LfuAlgorithm::LfuAlgorithm(int blocks_num) : Algorithm(blocks_num)
{
    newPartitionFinishLocation = 0;
    oldPartitionFinishLocation = blocks_num;
}


void LfuAlgorithm::addBlockToCache(Block *block)
{
}