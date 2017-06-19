#include <stdlib.h>
#include <fcntl.h>
#include <mm_malloc.h>
#include <malloc.h>
#include <iostream>
#include <limits.h>
#include "Algorithm.h"
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>


#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ios>
#include <bits/ios_base.h>
#include "CacheFS.h"
#define BLOCKSIZE 512
using namespace std;


int main(int argc, char* argv[])
{
//    open(argv[0],  O_RDONLY | O_DIRECT | O_SYNC);
//    std::cout << "Hello, World!" << std::endl;
//    std::string hi = "hello world dog";
//    std::cout <<"this is LRU "<<LRU <<" and this baby is LFU and other gut"<<LFU<<FBR<<std::endl;
    struct stat fi;
    stat("/tmp", &fi);
    int blksize = (int) fi.st_blksize;


    CacheFS_init(100 , LFU , 0.3333 , 0.5);
    int a = CacheFS_open("/tmp/README");

    void* buffer = aligned_alloc(blksize , blksize);

    int b = CacheFS_pread(a , buffer , 800 , 0);

    cout << "num of bytes read " << b << endl;
    cout << (char*)(buffer) << endl;

    b = CacheFS_pread(a , buffer , 800 , 800);

    cout << "num of bytes read " << b << endl;
    cout << (char*)(buffer) << endl;

    CacheFS_destroy();
    free(buffer);



//    char* full_path = realpath(argv[1], NULL);
//    if(realpath(argv[1], NULL) == nullptr)
//    {
//        std::cerr<<"ME SAD"<<std::endl;
//        return -1;
//    }
//    cout << "this is the real path" << full_path << endl;
//    cout<<"this is the blksize: "<<blksize<<endl;


    /**
    std::string strFullPath = (std::string) full_path;
    free(full_path);
    cout<<"this is strFullpath: "<<strFullPath<<endl;

    cout<<"this is find func: "<<strFullPath.find("/cs")<<endl;
    if(strFullPath.find("/cs") == 0)
    {
        std::cout << "String starts with Hello\n";
    }
    std::cout<<"this is the full path: " <<strFullPath<<std::endl;
*/
//    std::string path = (std::string)argv[1];
//    if (path.find("ex") == 0)
//    {
//        std::cout << "String starts with /cs\n";
//    }
//

//    unsigned long fileLength;
//    blksize = 512;
//
//
//    std::cout <<"SHOW TIME"<<std::endl;
//
//    buffer = aligned_alloc(blksize , blksize);
//    int f = open("/tmp/README", O_RDONLY|O_SYNC|O_DIRECT);
//
//
//    std::ifstream is("/tmp/README", std::ifstream::ate | std::ifstream::binary);
//    if(is)
//    {
//        fileLength = (unsigned long)is.tellg();
//        cout << "File length is: " << fileLength << endl;
//    }
//    cout << "This is the block size "  << blksize << endl;
//    std::cout << "this is pread: "<<pread(f, buffer, blksize, 0) << std::endl;
//    std::cout <<"this is buffer: "<< (char*)buffer << std::endl;
//    close(f);
//    free(buffer);
    return 0;

}