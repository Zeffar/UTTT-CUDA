#include <cuda_runtime.h>
#include <iostream>

int main() {
    int deviceId;
    cudaGetDevice(&deviceId); // Get the current device ID

    cudaDeviceProp props;
    cudaGetDeviceProperties(&props, deviceId); // Get the device properties

    std::cout << "Max threads per multiprocessor: " << props.maxThreadsPerMultiProcessor << "\n";
    std::cout << "Number of multiprocessors: " << props.multiProcessorCount << "\n";
    std::cout << "Max threads per block: " << props.maxThreadsPerBlock << "\n";

    int maxThreads = props.maxThreadsPerMultiProcessor * props.multiProcessorCount;
std::cout << "Maximum threads that can be run concurrently: " << maxThreads << std::endl;
return 0;
}