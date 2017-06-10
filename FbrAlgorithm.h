//
// Created by shaked571 on 6/10/17.
//

#ifndef EX4_FBRALGORITHM_H
#define EX4_FBRALGORITHM_H

#include "Algorithm.h"

class FbrAlgorithm :public Algorithm{
public:
    FbrAlgorithm(int blocks_num,double f_old , double f_new );

private:
    double f_old;
    double f_new;
};


#endif //EX4_FBRALGORITHM_H
