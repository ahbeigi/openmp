/* Reduction of an array with sum operation */

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[])
{
	long i, size = atoi(argv[1]);
	double arr[size], sum = 0.0;
	printf("size: %d\n", size);
	printf("step = %E\n", 1/(double)size);
	for(i=0; i<size; i++){
		arr[i] = (double)i/(double)size;
		// printf("%f ",arr[i]);
	}
	printf("\n");
#pragma omp parallel num_threads(4)
{
	int offset = size/omp_get_num_threads();
	int tid = omp_get_thread_num();
	printf("thread number %d starts from %d to %d \n", tid, tid*offset, offset*(tid+1)-1);

	#pragma omp for reduction(+:sum)
	for(i=0; i<size; i++){
		sum += arr[i];
		// printf("thread %d has sum = %f\n", tid, sum);
	}
}
	printf("outside of omp , sum = %E\n", sum);
	return 0;

}
