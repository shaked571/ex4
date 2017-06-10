//
// Created by shaked571 on 6/10/17.
//

#ifndef EX4_ALGORITHM_H
#define EX4_ALGORITHM_H

#include <unordered_map>
#include "CacheFS.h"
#include "Block.h"
class Algorithm
{
public:
    virtual Algorithm(int blocks_num, cache_algo_t cache_algo) = 0;
    virtual ~Algorithm();


private:
    int blockNum;
    cache_algo_t cache_algo;
    std::unordered_map<int, Block*> mapOfBlocks;
};


#endif //EX4_ALGORITHM_H
