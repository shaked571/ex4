//
// Created by shaked571 on 6/10/17.
//

#include "Block.h"

Block::Block(void* memoryU, std::string path, int blockNum) :memory(memory), filePath(path),
                                                          blockNum(blockNum)
{
    freq = 1;
}


unsigned int Block::getFreq() const {
    return freq;
}

void *Block::getMemory() const {
    return memory;
}

void Block::upFreq() {
    freq++;
}

const std::string &Block::getFilePath() const {
    return filePath;
}

int Block::getBlockNum() const {
    return blockNum;
}
