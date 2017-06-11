//
// Created by shaked571 on 6/10/17.
//

#include <stdlib.h>
#include "LruAlgorithm.h"

LruAlgorithm::LruAlgorithm(int blocks_num) :Algorithm(blocks_num)
{

}

int LruAlgorithm::ChachePread(int file_id, void *buf, size_t count, off_t offset)
{


    if (pathOpenedMap.at(3))
    void* buffer = aligned_alloc(blksize , blksize);

    std::cout << pread(file_id, buffer, blksize, 0) << std::endl;
    std::cout << (char*)buffer << std::endl;
    if(vectorOfBlocks.size() < blockNum)
    {

    }
    return 0;
}
