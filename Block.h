//

// Created by shaked571 on 6/10/17.
//

#ifndef EX4_BLOCK_H
#define EX4_BLOCK_H
#include <iostream>
#include "CacheFS.h"
#include "fcntl.h"
//struct stat fi;
//stat("/tmp", &fi);
//int blksize = fi.st_blksize;

class Block
{

public:
    Block(char* memoryU, std::string path, int blocNum);

    char *getMemory() const;

    unsigned int getFreq() const;

    void upFreq();


private:
    unsigned int freq;
    char * memory;
    std::string filePath;
    int blockNum;
public:
    const std::string &getFilePath() const;

    int getBlockNum() const;

};


#endif //EX4_BLOCK_H
