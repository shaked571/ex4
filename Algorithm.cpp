//
// Created by shaked571 on 6/10/17.
//

#include "Algorithm.h"
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>


#define ERROR -1
Algorithm::Algorithm(int blocks_num):blockNum(blocks_num)
{
    //block size call
    struct stat fi;
    stat("/tmp", &fi);
    blksize = fi.st_blksize;
    pathToVectorOfBlocks  =  new std::unordered_map<std::string, std::vector<Block*>>();
    fidToPath = new std::unordered_map<int, std::string>();

}

Algorithm::~Algorithm()
{
    delete(pathToVectorOfBlocks);
    delete(fidToPath);
    pathToVectorOfBlocks->clear();
    fidToPath->clear();
}

int Algorithm::programOpen(std::string pathName) {
    unsigned long fileLength;
    int fid = open(pathName.c_str(), O_RDONLY|O_SYNC|O_DIRECT);
    if(fid  == ERROR)
    {
        return ERROR;
    }
    std::ifstream is(pathName, std::ifstream::ate | std::ifstream::binary);
    if(is)
    {
          fileLength = (unsigned long)is.tellg();
    } else
    {
        return ERROR;
    }
    unsigned long  numOfMaxBlock = ((fileLength + blksize  - 1) / blksize);//To round up the result
    (*fidToPath)[fid] = pathName;
    std::vector<Block*> fileBlocks(numOfMaxBlock);
    (*pathToVectorOfBlocks)[pathName] = fileBlocks;
    auto pair = std::make_pair(pathName, fileBlocks);
    return fid;

}

int Algorithm::ChachePread(int file_id, void *buf, size_t count, off_t offset)
{

    std::string path = (*fidToPath)[file_id];
    auto vectorOfBlocksOfTheFid = (*pathToVectorOfBlocks)[path];

    int i , end;
    i =(int)(offset/blksize);
    end = (int)((offset + count) / blksize);
    for (i; i < end ; ++i)
    {
        unsigned long pos = (unsigned long) buf;//saving the position
        if (vectorOfBlocksOfTheFid[i] != nullptr)//need to verify
        {
            if(isInCache(path, i))
            {
                //TODO implementation is needed of:
                // 1. put the memory from cache to the buffer
                // 2. if the block location not in the begin do ++ to the freq (using upFreq() )
                //pread(file_id, buf + pos, blksize, offset + pos);//TODO i thimk it is not right- Elad- need to chandge the syntax
            }
            else
            {
                char * memChunk;//TODO put the memory in the block
                Block * block  = new Block(memChunk, path, i);
                insertBlock(block);
            }



           // std::memcpy()
            //put the block in the buf usr memcopy and  starting from the last pos +
        }
    }

/**
 * use memcopy
 * const int key = file_id;
    std::string fullPath;
    fullPath = fidToPath->at(key);
    void* buffer = aligned_alloc(blksize , blksize);
    std::cout << pread(file_id, buffer, blksize, 0) << std::endl;
    std::cout << (char*)buffer << std::endl;
    if(vectorOfBlocks.size() < blockNum)
    {

    }
 */
    return 0;
}

bool Algorithm::isInCache(std::string filePath, int blockNum)
{
    Block *block = ((*pathToVectorOfBlocks)[filePath])[blockNum];
    return block != nullptr;
}

int Algorithm::insertBlock(Block)
{
    for (int i = )
    return 0;
}





