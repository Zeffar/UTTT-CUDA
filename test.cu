#include <iostream>
#include <math.h>
#include <chrono>

// Kernel function to add the elements of two arrays
__global__
void add(long n, float *x, float *y)
{
  long index = blockIdx.x * blockDim.x + threadIdx.x;
  if (index < n)
    y[index] = x[index] + y[index];
}

int main(void)
{


  long N = 1<<30;
  float *x, *y;

  // Allocate Unified Memory – accessible from CPU or GPU
  cudaMallocManaged(&x, N*sizeof(float));
  cudaMallocManaged(&y, N*sizeof(float));

  // initialize x and y arrays on the host
  for (int i = 0; i < N; i++) {
    x[i] = 1.0f;
    y[i] = 2.0f;
  }

  cudaEvent_t start, stop;
  float elapsedTime;
  for(int i=0; i<10; ++i){
    cudaEventCreate(&start);
    cudaEventRecord(start,0);

    // Run kernel on 1M elements on the GPU
    int blockSize = 1024;
    long numBlocks = (N + blockSize - 1) / blockSize;
    add<<<numBlocks, blockSize>>>(N, x, y);

    cudaEventCreate(&stop);
    cudaEventRecord(stop,0);
    cudaEventSynchronize(stop);

    cudaEventElapsedTime(&elapsedTime, start,stop);
    printf("Elapsed time : %f ms\n" ,elapsedTime);

    cudaEventDestroy(start);
    cudaEventDestroy(stop);
    // Wait for GPU to finish before accessing on host
    cudaDeviceSynchronize();

    // Check for errors (all values should be 3.0f)
    // float maxError = 0.0f;
    // for (int i = 0; i < N; i++)
    //   maxError = fmax(maxError, fabs(y[i]-3.0f));
    // std::cout << "Max error: " << maxError << std::endl;

  }
  // Free memory
  cudaFree(x);
  cudaFree(y);


  
  return 0;
}