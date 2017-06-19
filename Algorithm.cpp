//
// Created by shaked571 on 6/10/17.
//

#include "Algorithm.h"
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include <malloc.h>

using namespace std;


#define ERROR -1
Algorithm::Algorithm(int blocks_num , cache_algo_t algoName):blockNum(blocks_num) , algoName(algoName)
{
    //block size call
    struct stat fi;
    stat("/tmp", &fi);
    blksize = fi.st_blksize;
    pathToVectorOfBlocks  =  new std::unordered_map<std::string, std::vector<bool>>();
    fidToPath = new std::unordered_map<int, std::string>();

}

Algorithm::~Algorithm()
{
    delete(pathToVectorOfBlocks);
    delete(fidToPath);
    pathToVectorOfBlocks->clear();
    fidToPath->clear();
}

const cache_algo_t &Algorithm::getAlgoName() const {
    return algoName;
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
    std::vector<bool> fileBlocks(numOfMaxBlock , false);
    (*pathToVectorOfBlocks)[pathName] = fileBlocks;
    return fid;

}

int Algorithm::CachePread(int file_id, void *buf, size_t count, off_t offset)
{
    string currentData;
    std::string path = (*fidToPath)[file_id];
    string dataToReturn;

    int startBlock , currentBlock , endBlock;
    startBlock =(int)(offset/blksize);
    currentBlock = startBlock;
    endBlock = (int)((offset + count) / blksize) + 1;
    for (currentBlock; currentBlock < endBlock ; ++currentBlock)
    {
        void *buffer;
        if(!isInCache(path, currentBlock))
        {
            buffer = aligned_alloc(blksize , blksize);
            pread(file_id, buffer, blksize, (currentBlock*blksize));
            Block * block  = new Block(buffer, path, currentBlock);
            ((*pathToVectorOfBlocks)[path])[currentBlock] = block;
            addBlockToCache(block);
        } else {
            cout << "Size " << vectorOfBlocks.size() << endl;
            for (auto i = vectorOfBlocks.begin(); i != vectorOfBlocks.end(); ++i ) {
                cout<<"path is: "<< path<<endl;
                cout<<"path is: "<< (*i)->getFilePath()<<endl;
                if (!path.compare((*i)->getFilePath()))
                {
                    if (currentBlock == (*i)->getBlockNum()){
                        buffer = (*i)->getMemory();
                        (*i)->upFreq();
                    }
                }
            }
        }
        currentData = ((char *)buffer);
        if (currentBlock == (endBlock - 1)){
            currentData = currentData.substr(0, (count+offset)%blksize);
        }
        if (currentBlock == startBlock){
            currentData = currentData.substr(((unsigned long)offset)%blksize , currentData.size());
        }
        dataToReturn += currentData;
    }

    void* toBuf = (void *)currentData.c_str();
    memcpy(buf , toBuf , currentData.size());
    return (int)currentData.size();
}


bool Algorithm::isInCache(std::string filePath, int blockNum)
{
    return (*pathToVectorOfBlocks)[filePath][blockNum];
}






