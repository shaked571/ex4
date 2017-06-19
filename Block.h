#ifndef EX4_BLOCK_H
#define EX4_BLOCK_H
#include <iostream>
#include "CacheFS.h"
#include "fcntl.h"

class Block
{

public:
    bool operator<(const Block &rhs) const;

    Block(const Block &block);

    Block(void* memory, std::string path, int blocNum);

    void *getMemory() const;

    unsigned int getFreq() const;

    void upFreq();
    const std::string &getFilePath() const;

    int getBlockNum() const;


private:
    unsigned int freq;
    void * memory;
    std::string filePath;
    int blockNum;

};


#endif //EX4_BLOCK_H
