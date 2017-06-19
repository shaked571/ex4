//
// Created by shaked571 on 6/10/17.
//

#include <math.h>
#include <cmath>
#include <algorithm>
#include "CacheAlgorithm.h"
using namespace std;

CacheAlgorithm::CacheAlgorithm(int blocks_num,double f_old , double f_new , cache_algo_t
algoName) : Algorithm(blocks_num , algoName)
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
        string filePath = (*min)->getFilePath();
        int blockNum = (*min)->getBlockNum();
        (*pathToVectorOfBlocks)[filePath][blockNum] = false;
        vectorOfBlocks.erase(min);
    }
    (*pathToVectorOfBlocks)[block->getFilePath()][block->getBlockNum()] = true;
    vectorOfBlocks.push_back(block);

}