#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[])
{
        int i;
	int size = atoi(argv[1]);
        double arr[size], sum = 0.0;
        printf("size: %d\n", size);
	printf("step = %f\n", 1/(double)size);
        for(i=0; i<size; i++){
                arr[i] = (double)i/(double)size;
		// printf("%f ", arr[i]);
        }
	for(i=0; i<size; i++)
		sum += arr[i];

	printf("sum = %f\n",sum);
}
