#include <stdlib.h>
#include <fcntl.h>
#include <zconf.h>
#include <mm_malloc.h>
#include <malloc.h>
#include <iostream>


//#include <bits/stat.h>
#include <fcntl.h>
#include "CacheFS.h"
#define BLOCKSIZE 512

//struct stat fi;
//stat("/tmp", &fi);
//int blksize = fi.st_blksize;

int main(int argc, char* argv[])
{
    open(argv[0],  O_RDONLY | O_DIRECT | O_SYNC);
    std::cout << "Hello, World!" << std::endl;
//    std::cout <<"this is LRU "<<LRU <<" and this baby is LFU and other gut"<<LFU<<FBR<<std::endl;
    std::cout <<h<<std::endl;
    void* buffer = aligned_alloc(BLOCKSIZE , BLOCKSIZE);
    int f = open("/tmp/README.txt", O_RDONLY|O_SYNC|O_DIRECT);
    std::cout << pread(f, buffer, BLOCKSIZE , BLOCKSIZE) << std::endl;
    std::cout << (char*)buffer << std::endl;
    close(f);
    free(buffer);
    return 0;

    return 0;
}