//
// Created by shaked571 on 6/10/17.
//

#ifndef EX4_ALGORITHM_H
#define EX4_ALGORITHM_H

#include <vector>
#include <unordered_map>
#include "CacheFS.h"
#include "Block.h"
#include <sys/stat.h>
//#include <zconf.h>
#include <stdlib.h>
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream

class Algorithm
{
public:
    Algorithm(int blocks_num, cache_algo_t);
    virtual ~Algorithm();
    virtual void addBlockToCache(Block* block) = 0;
    int CachePread(int file_id, void *buf, size_t count, off_t offset);
    int programOpen(std::string pathName);
    bool isInCache(std::string filePath, int blockNum);

    const cache_algo_t &getAlgoName() const;

protected:
    unsigned int blksize;
    int blockNum;
    double oldPartitionFinishLocation;
    double newPartitionFinishLocation;
    cache_algo_t algoName;
    std::vector<Block*> vectorOfBlocks;
    std::unordered_map<int, std::string> *fidToPath;
    //give you
    std::unordered_map<std::string, std::vector<bool>> *pathToVectorOfBlocks;
    std::vector<int>* openFile;

};


#endif //EX4_ALGORITHM_H
