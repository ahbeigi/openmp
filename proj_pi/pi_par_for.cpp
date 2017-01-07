/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   par_for.cpp
 * Author: ali
 *
 * Created on January 7, 2017, 6:41 PM
 */

#include <cstdlib>
#include <stdio.h>
#include <omp.h>
#include "headers.h"

using namespace std;

/*
 * use parallel for to calculate the pi.
 */
int pi_par_for(int argc, char** argv) {
    int num_steps = 100000000;
    double step = 1.0/num_steps;
    double pi = 0, sum = 0, x = 0;
    omp_sched_t kind;
    int modifier;
    
    double stime = omp_get_wtime();
    # pragma omp parallel for reduction(+:sum) schedule(runtime) private(x)
        for(int i = 0; i <= num_steps; i++)
        {
            x = (i+0.5)* step;
            sum += 4.0/(1.0+x*x);
            //printf("[Tread %d] i = %d, x = %f, local_sum = %f\n", id, i, x, local_sum);
        }
    double dtime = omp_get_wtime();
    //printf("[Thread %d] local_sum = %f, \n", id, local_sum);
    pi =  sum*step;
    printf("pi = %.16f, in elapsed time: %.8f\n", pi, dtime - stime);
    return 0;
}

