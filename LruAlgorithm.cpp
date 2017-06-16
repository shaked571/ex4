//
// Created by shaked571 on 6/10/17.
//

#include <stdlib.h>
#include <unistd.h>
#include "LruAlgorithm.h"

LruAlgorithm::LruAlgorithm(int blocks_num) :Algorithm(blocks_num)
{
    oldPartitionFinishLocation = blocks_num;
    newPartitionFinishLocation = blocks_num - 1;

}

void LruAlgorithm::addBlockToCache(Block *block)
{
}
