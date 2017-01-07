/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pi_serial.cpp
 * Author: ali
 *
 * Created on January 4, 2017, 6:41 PM
 */

#include <cstdlib>
#include <stdio.h>
#include <omp.h>
#include "headers.h"

using namespace std;

/*
 * Serial version of calculating the pi.
 */
int pi_serial(int argc, char** argv) {
    double num_steps = 10000000;
    long double step = 1.0/num_steps;
    double pi = 0, sum = 0, x;
    
    double stime = omp_get_wtime();
    for(int i=0;i < num_steps; i++)
    {
        x = (i+0.5)* step;
        sum += 4.0/(1.0+x*x);
        //printf("[Tread %d] i = %d, x = %f, local_sum = %f\n", id, i, x, local_sum);
    }
    //printf("[Thread %d] local_sum = %f, \n", id, local_sum);
    pi =  sum*step;
    double dtime = omp_get_wtime();
    
    printf("pi = %.16f, in elapsed time: %.8f\n", pi, dtime - stime);
    return 0;
}

