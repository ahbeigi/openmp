/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pi_par_synced.cpp
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
 * Using atomic section to get rid of array for gathering temporary results
 */
int pi_par_synced(int argc, char** argv) {
    double num_steps = 1000000;
    long double step = 1.0/num_steps;
    int numt = 4;
    double pi = 0;
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
	#pragma omp critical
        	pi +=  local_sum*step;
    }
    printf("Parallel section took %f miliseconds\n", (omp_get_wtime() - stime)*1000);
    printf("pi = %f\n", pi);
    return 0;
}

