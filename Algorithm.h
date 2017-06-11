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
#include <zconf.h>
#include <stdlib.h>
class Algorithm
{
public:
    Algorithm(int blocks_num);
    virtual ~Algorithm() = 0;
    virtual int ChachePread(int file_id, void *buf, size_t count, off_t offset) = 0;
    int programOpen(std::string pathName);
protected:
    int blksize;
    int blockNum;
    std::vector<Block*> vectorOfBlocks;
    std::unordered_map<int, std::string> *pathOpenedMap;

};


#endif //EX4_ALGORITHM_H
