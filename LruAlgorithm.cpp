//
// Created by shaked571 on 6/10/17.
//

#include "LruAlgorithm.h"

LruAlgorithm::LruAlgorithm(int blocks_num) : Algorithm(blocks_num)
{

}

int LruAlgorithm::ChachePread(int file_id, void *buf, size_t count, off_t offset)
{
    if(vectorOfBlocks.size() < blockNum)
    {
        
    }
    return 0;
}
