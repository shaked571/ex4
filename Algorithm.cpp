//
// Created by shaked571 on 6/10/17.
//

#include "Algorithm.h"


#define ERROR -1
Algorithm::Algorithm(int blocks_num):blockNum(blocks_num)
{
    //block size call
    struct stat fi;
    stat("/tmp", &fi);
    blksize = fi.st_blksize;
    pathOpenedMap  =  new std::unordered_map<std::string, std::vector<Block*>>();
    fidToPath = new std::unordered_map<int, std::string>();

}

Algorithm::~Algorithm()
{
    delete(pathOpenedMap);
    delete(fidToPath);
    pathOpenedMap->clear();
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
          fileLength = is.tellg();
    } else
    {
        return ERROR;
    }
    unsigned long  numOfMaxBlock = ((fileLength + blksize  - 1) / blksize);//To round up the result
    fidToPath->insert(std::make_pair(fid, pathName));
    std::vector<Block*> *fileBlocks = new std::vector<Block*> (numOfMaxBlock);
    pathOpenedMap->insert(std::make_pair(pathName, fileBlocks)); //TODO Elad!i wrote this lines fast- ith ink they are ok-double check me
    return fid;

}





