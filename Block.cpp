//
// Created by shaked571 on 6/10/17.
//

#include "Block.h"

Block::Block(char* memoryU) :memory(memory)
{
    freq = 1;
}


unsigned int Block::getFreq() const {
    return freq;
}

char *Block::getMemory() const {
    return memory;
}

void Block::upFreq() {
    freq++;
}
