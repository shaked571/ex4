//
// Created by shaked571 on 6/10/17.
//

#ifndef EX4_ALGORITHM_H
#define EX4_ALGORITHM_H

#include <vector>
#include <bits/unordered_map.h>
#include "CacheFS.h"
#include "Block.h"
class Algorithm
{
public:
    virtual Algorithm(int blocks_num) = 0;
    virtual ~Algorithm() = 0;
    virtual int ChachePread(int file_id, void *buf, size_t count, off_t offset) = 0;

protected:
    int blockNum;
    std::vector<Block*> vectorOfBlocks;
    std::unordered_map<char*, std::vector<int>> pathOpenedeMap;

};


#endif //EX4_ALGORITHM_H
