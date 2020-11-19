
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<math.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 3

__global__ void code(char *A, int *B, char *C, int len)
{
	int i = threadIdx.x; //cols
	int j = blockIdx.x; //rows just to see if it changes the code
	int k = blockDim.x;
	int temp = 0;
	for (int b = 0; b < len; b++)
	{
		temp = 0;
		if (j < N)
		{
			for (int c = 0; c < k; c++)
				temp = temp + ((int)A[b*k + c] * B[j*k + c]);
			if (temp != (-52))
				C[b*k + j] = (char)temp;
			else
				C[b*k + j] = '\0';
		}

	}

}

int main()
{
	// Host variables and Keys Declaration
	char str[50000], encrypt[50000], decrypt[50000];
	fgets(str, 50000, stdin);
	float etime, dtime;
	cudaEvent_t estart, estop;
	int len = strlen(str);
	int ekey[N][N] = { {1,2,-1},{-2,0,1},{1,-1,0} };
	int dkey[N][N] = { {1,1,2},{1,1,1},{2,3,4} };

	// Calculating loops to process entire string	
	double a = (double)len / (double)N;
	int loop_count = ceil(a);

	// creating Events to calculate time
	cudaEventCreate(&estart);
	cudaEventCreate(&estop);

	// Encryption Process

		// Create Device Variables
	char *str1, *strop;
	int *key;

	// Allocate memory to Variables on Device
	cudaMalloc((char**)&str1, sizeof(char)*len);
	cudaMalloc((char**)&strop, sizeof(char)*len);
	cudaMalloc((int**)&key, sizeof(int)*N*N);

	// Copy data from Host to Device
	cudaMemcpy(str1, str, sizeof(char)*len, cudaMemcpyHostToDevice);
	cudaMemcpy(key, ekey, sizeof(int)*N*N, cudaMemcpyHostToDevice);

	// Start event timer for encryption
	cudaEventRecord(estart, 0);
	cudaEventSynchronize(estart);

	//Pass it on to function and get back the cyphr
	code << <N, N >> > (str1, key, strop, loop_count);
	cudaDeviceSynchronize();

	// Stop Event timmer by using another counter
	cudaEventRecord(estop, 0);
	cudaEventSynchronize(estop);
	cudaEventElapsedTime(&etime, estart, estop);

	cudaMemcpy(encrypt, strop, sizeof(char)*len, cudaMemcpyDeviceToHost);

	cudaFree(str1);
	cudaFree(strop);
	cudaFree(key);
	printf("\nEncryption : ");
	for (int i = 0; i < len; i++)
	{
		printf("%c", encrypt[i]);
	}
	printf("\n");

	// Decryption Process

		// Allocate memory to Variables on Device
	cudaMalloc((char**)&str1, sizeof(char)*len);
	cudaMalloc((char**)&strop, sizeof(char)*len);
	cudaMalloc((int**)&key, sizeof(int)*N*N);

	// Copy data from Host to Device
	cudaMemcpy(str1, encrypt, sizeof(char)*len, cudaMemcpyHostToDevice);
	cudaMemcpy(key, dkey, sizeof(int)*N*N, cudaMemcpyHostToDevice);

	code << <N, N >> > (str1, key, strop, loop_count);
	cudaDeviceSynchronize();

	cudaMemcpy(decrypt, strop, sizeof(char)*len, cudaMemcpyDeviceToHost);

	cudaFree(str1);
	cudaFree(strop);
	cudaFree(key);
	printf("\n\nDecryption : ");
	for (int i = 0; i < len; i++)
	{
		printf("%c", decrypt[i]);
	}
	printf("\n");

	printf("\n\nEncryption Time : %fms\n\n", etime);
	return 0;
}
