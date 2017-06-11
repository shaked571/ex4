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
    pathOpenedMap  =  new std::unordered_map<std::string, std::vector<int>>();
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

    int fid = open(pathName.c_str(), O_RDONLY|O_SYNC|O_DIRECT);
    if(fid  == ERROR)
    {
        return ERROR;
    }
    fidToPath->insert(std::make_pair(fid, pathName));
    return fid;

}





