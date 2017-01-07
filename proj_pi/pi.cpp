/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: ali
 *
 * Created on January 4, 2017, 6:41 PM
 */

#include <cstdlib>
#include <stdio.h>
#include <omp.h>

using namespace std;

/*
 * Parallel version of calculating the pi.
 */
int main(int argc, char** argv) {
    double num_steps = 1000000;
    long double step = 1.0/num_steps;
    int numt = 4;
    double pi = 0, tmp_pi[numt];
    omp_set_num_threads(numt);
    int chunk = num_steps/numt;
    printf("chunk = %d, numt = %d, step = %f\n", chunk, numt, step);
    double stime = omp_get_wtime();
#pragma omp parallel    
    {
        float x, local_sum = 0.0;
        int i, id = omp_get_thread_num();
        //printf("Entering thread %d...\n", id);
        for(i=id*chunk;i < (id+1)*chunk ; i++)
        {
            x = (i+0.5)* step;
            local_sum += 4.0/(1.0+x*x);
            //printf("[Tread %d] i = %d, x = %f, local_sum = %f\n", id, i, x, local_sum);
        }
        //printf("[Thread %d] local_sum = %f, \n", id, local_sum);
        tmp_pi[id] =  local_sum*step;
    }
    printf("Parallel section consumed time in milisecond: %f\n", (omp_get_wtime() - stime)*1000);
    for(int j=0;j<numt;j++)
	    pi += tmp_pi[j];
    printf("pi = %f", pi);
    return 0;
}

