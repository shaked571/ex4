//
// Created by shaked571 on 6/10/17.
//

#include <math.h>
#include "FbrAlgorithm.h"

FbrAlgorithm::FbrAlgorithm(int blocks_num,double f_old , double f_new ) : Algorithm(blocks_num)
{
    oldPartitionLocation = (int)std::floor(blocks_num *f_old);
    newPartitionLocation = (int)std::floor(blocks_num * f_new);
}
