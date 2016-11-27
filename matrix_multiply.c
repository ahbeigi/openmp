/* This code accepts the size of matrixes from argv and generate two matrix. */
/* Then it multiply them in serial and parallel manner and return the time spent and results. */
/*** IT IS BUGGY! ***/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

float multiply_serial(int size, float a[size][size], float b[size][size]);
float multiply_parallel(int size, float a[size][size], float b[size][size]);

int main(int argc, char* argv[])
{
	int SIZE = atoi(argv[1]), i, j;
	float a[SIZE][SIZE], b[SIZE][SIZE];
	// Fill a and b with random float numbers:
	srand(time(NULL));
	for(i=0; i<SIZE; i++)
		for(j=0;j<SIZE;j++){
			a[i][j] = (float)(rand() % 10);
			b[i][j] = (float)(rand() % 10);
		}

	// print a and b:
	printf("a = \n");
	for(i=0; i<SIZE; i++){
		for(j=0;j<SIZE;j++)
			printf("%f ", a[i][j]);
		printf("\n");
	}
	printf("b = \n");
	for(i=0; i<SIZE; i++){
		for(j=0;j<SIZE;j++)
			printf("%f ", b[i][j]);
		printf("\n");
	}
	float s_time = multiply_serial(SIZE, a, b);
	float p_time = multiply_parallel(SIZE, a, b);
	printf("--- serial time: %f\n", s_time);
	printf("--- parallel time: %f\n", p_time);
	
	return 0;
}

float multiply_serial(int size, float a[size][size], float b[size][size])
{
	int i, j, k;
	float c[size][size], sum;
	// calculate the c:
	clock_t begin = clock();
	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			sum = 0;
			for(k=0; k<size; k++){
				sum += a[i][k] * b[k][j];
			}
			c[i][j] = sum;
		}
	}
	clock_t end = clock();
	//double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	double time_spent = (double)(end - begin);
	// print the result:
	printf("serial multiply function ran in %f clocks and c = \n", time_spent);
	for(i=0; i<size; i++){
		for(j=0;j<size;j++)
			printf("%f ", c[i][j]);
		printf("\n");
	}
	return time_spent;
}

float multiply_parallel(int size, float a[size][size], float b[size][size])
{
	float c[size][size], sum;
	int i, j, k;
	//memset(c, 0, sizeof(c[0][0]) * size * size);
	clock_t begin = clock();

#pragma omp parallel sections num_threads(2) shared(a, b, c) private(i)
{
	// calculate the c:
	#pragma omp section
	{
		for(i=0; i<size/2; i++){
			for(j=0; j<size; j++){
				sum = 0;
				for(k=0; k<size; k++){
					sum += a[i][k] * b[k][j];
				}
				c[i][j] = sum;
			}
		}
	} // omp section 1
	
	#pragma omp section
	{
		for(i=size/2; i<size; i++){
			for(j=0; j<size; j++){
				sum = 0;
				for(k=0; k<size; k++){
					sum += a[i][k] * b[k][j];
				}
				c[i][j] = sum;
			}
		}

	} // omp section 2
} // omp parallel

	clock_t end = clock();
	double time_spent = (double)(end - begin);
	printf("parallel multiply function ran in %f clocks and c = \n", time_spent);
	for(i=0; i<size; i++){
		for(j=0;j<size;j++)
			printf("%f ", c[i][j]);
		printf("\n");
	}
	return time_spent;
}



