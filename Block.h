//
// Created by shaked571 on 6/10/17.
//

#ifndef EX4_BLOCK_H
#define EX4_BLOCK_H
#include <iostream>
#include "CacheFS.h"
#include "fcntl.h"
struct stat fi;
stat("/tmp", &fi);
int blksize = fi.st_blksize;

class Block {

    Block()
};


#endif //EX4_BLOCK_H
