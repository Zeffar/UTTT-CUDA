#include <iostream>
#include <math.h>
#include <chrono>
// Kernel function to add the elements of two arrays
void add(long n, float *x, float *y)
{
  for (long i = 0; i < n; i++)
      y[i] = x[i] + y[i];
}

int main(void)
{


  long N = 1<<30; // 1M elements

  float *x = new float[N];
  float *y = new float[N];

  // initialize x and y arrays on the host
  for (long i = 0; i < N; i++) {
    x[i] = 1.0f;
    y[i] = 2.0f;
  }

  std::chrono::time_point<std::chrono::system_clock> start, end;
 
  start = std::chrono::system_clock::now();
  // Run kernel on 1M elements on the CPU
  add(N, x, y);

  end = std::chrono::system_clock::now();
 
  std::chrono::duration<double> elapsed_seconds = end - start;
  std::time_t end_time = std::chrono::system_clock::to_time_t(end);

  std::cout << "elapsed time: " << elapsed_seconds.count()*1000 << "ms\n";
  // Check for errors (all values should be 3.0f)
  float maxError = 0.0f;
  for (int i = 0; i < N; i++)
    maxError = fmax(maxError, fabs(y[i]-3.0f));
  std::cout << "Max error: " << maxError << std::endl;

  // Free memory
  delete [] x;
  delete [] y;

  return 0;
}