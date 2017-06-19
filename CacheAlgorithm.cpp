//
// Created by shaked571 on 6/10/17.
//

#include <math.h>
#include <cmath>
#include <algorithm>
#include "CacheAlgorithm.h"
using namespace std;

CacheAlgorithm::CacheAlgorithm(int blocks_num,double f_old , double f_new ) : Algorithm(blocks_num)
{
    oldPartitionFinishLocation = (int)std::floor(blocks_num * f_old);
    newPartitionFinishLocation = (int)std::floor(blocks_num * f_new);

}


void CacheAlgorithm::addBlockToCache(Block *block)
{
    vector<Block*>::iterator endOfOld = vectorOfBlocks.begin() + oldPartitionFinishLocation;
    if (vectorOfBlocks.size() >= blockNum)
    {
        auto min = std::min_element(vectorOfBlocks.begin(), endOfOld , [](Block *a, Block * b)
                                    { return a->getFreq() < b->getFreq(); });
        vectorOfBlocks.erase(min);
        vectorOfBlocks.push_back(block);
    }

}