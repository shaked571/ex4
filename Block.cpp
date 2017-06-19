#include "Block.h"

Block::Block(void* memory, std::string path, int blockNum) :memory(memory), filePath(path),
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

bool Block::operator<(const Block &rhs) const
{
    return freq < rhs.freq;
}
/**
 * copy constructor
 * @param block
 * @return
 */
Block::Block(const Block &block) :memory(block.memory), filePath(block.filePath), blockNum(block.blockNum)
{
        *this = block;
}

