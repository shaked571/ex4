//
// Created by shaked on 09/06/17.
//
#include "string.h"
#include <iostream>
#include <bits/stat.h>
#include <fcntl.h>
#include "CacheFS.h"

struct stat fi;
stat("/tmp", &fi);
int blksize = fi.st_blksize;

int main(int argc, char* argv[])
{
    open(argv[0],  O_RDONLY | O_DIRECT | O_SYNC);
    std::cout << "Hello, World!" << std::endl;
    std::cout <<"this is LRU "<<LRU <<" and this baby is LFU and other gut"<<LFU<<FBR<<std::endl;
    
    std::cout <<97 * 0.5;
    return 0;
}