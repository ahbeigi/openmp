/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: ali
 *
 * Created on January 7, 2017, 11:50 AM
 */

#include <cstdlib>
#include <stdio.h>
#include "headers.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    printf("Serial version of pi:\n");
    pi_serial(0, 0);
    
    printf("Using parallel for:\n");
    pi_par_for(0, 0);
    
    return 0;
}

