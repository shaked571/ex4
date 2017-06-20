#ifndef EX4_ALGORITHM_H
#define EX4_ALGORITHM_H

#include <vector>
#include <unordered_map>
#include "CacheFS.h"
#include "Block.h"
#include <sys/stat.h>
#include <stdlib.h>
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream

class Algorithm
{
public:
    Algorithm(int blocks_num,double f_old , double f_new, cache_algo_t algoName);

    std::unordered_map<std::string, std::vector<bool, std::allocator<bool>>> *getPathToVectorOfBlocks() const;

    virtual ~Algorithm();
    int CachePread(int file_id, void *buf, size_t count, off_t offset);
    int programOpen(std::string pathName);
    bool isInCache(std::string filePath, int blockNum);
    const cache_algo_t &getAlgoName() const;
    void addBlockToCache(Block* block);


    std::vector<Block*> arrangedVec();

    int getHitsNum() const;

    int getMissNum() const;

    void HitsNumPlus();

    void MissNumPlus();

    int closeFile(int fileId);

    const std::vector<Block *> &getVectorOfBlocks() const;
    void* hit(void *buffer, std::string path, int currentBlock );
    void* miss(void *buffer, std::string path, int currentBlock, int file_id );
private:
    unsigned int blksize;
    int blockNum;
    double oldPartitionFinishLocation;
    double newPartitionFinishLocation;
    int hitsNum;
    int missNum;
    cache_algo_t algoName;
    std::vector<Block*> vectorOfBlocks;
    std::unordered_map<int, std::string> *fidToPath;
    std::unordered_map<std::string, std::vector<bool>> *pathToVectorOfBlocks;

};


#endif //EX4_ALGORITHM_H
