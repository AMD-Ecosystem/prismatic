// CUDA-to-HIP compatibility header for Prismatic
// On HIP builds, aliases the CUDA spellings used throughout the codebase
// to their HIP equivalents. On CUDA builds, this header is a no-op.

#pragma once

#if defined(USE_HIP) || defined(__HIP_PLATFORM_AMD__)

#include <hip/hip_runtime.h>
#include <hip/hip_complex.h>
#include <hipfft/hipfft.h>

// CUDA runtime -> HIP runtime
#define cudaMalloc              hipMalloc
#define cudaMallocHost          hipHostMalloc
#define cudaMallocManaged       hipMallocManaged
#define cudaFree                hipFree
#define cudaFreeHost            hipHostFree
#define cudaMemcpy              hipMemcpy
#define cudaMemcpyAsync         hipMemcpyAsync
#define cudaMemcpy2DAsync       hipMemcpy2DAsync
#define cudaMemset              hipMemset
#define cudaMemcpyHostToDevice  hipMemcpyHostToDevice
#define cudaMemcpyDeviceToHost  hipMemcpyDeviceToHost
#define cudaMemcpyDeviceToDevice hipMemcpyDeviceToDevice

#define cudaStream_t            hipStream_t
#define cudaStreamCreate        hipStreamCreate
#define cudaStreamDestroy       hipStreamDestroy
#define cudaStreamSynchronize   hipStreamSynchronize
#define cudaDeviceSynchronize   hipDeviceSynchronize

#define cudaSetDevice           hipSetDevice
#define cudaGetDevice           hipGetDevice
#define cudaGetDeviceCount      hipGetDeviceCount
#define cudaDeviceReset         hipDeviceReset
#define cudaMemGetInfo          hipMemGetInfo

#define cudaError_t             hipError_t
#define cudaSuccess             hipSuccess
#define cudaGetErrorString      hipGetErrorString
#define cudaGetLastError        hipGetLastError

// Device properties
#define cudaDeviceProp          hipDeviceProp_t
#define cudaGetDeviceProperties hipGetDeviceProperties

// cuComplex -> hipComplex
#define cuFloatComplex          hipFloatComplex
#define cuDoubleComplex         hipDoubleComplex
#define cuCrealf                hipCrealf
#define cuCimagf                hipCimagf
#define cuCreal                 hipCreal
#define cuCimag                 hipCimag
#define cuCaddf                 hipCaddf
#define cuCadd                  hipCadd
#define cuCsubf                 hipCsubf
#define cuCsub                  hipCsub
#define cuCmulf                 hipCmulf
#define cuCmul                  hipCmul
#define cuCdivf                 hipCdivf
#define cuCdiv                  hipCdiv
#define cuConjf                 hipConjf
#define cuConj                  hipConj
#define cuCabsf                 hipCabsf
#define cuCabs                  hipCabs
#define make_cuFloatComplex     make_hipFloatComplex
#define make_cuDoubleComplex    make_hipDoubleComplex

// cuFFT -> hipFFT
#define cufftHandle             hipfftHandle
#define cufftPlan2d             hipfftPlan2d
#define cufftPlanMany           hipfftPlanMany
#define cufftSetStream          hipfftSetStream
#define cufftExecC2C            hipfftExecC2C
#define cufftExecZ2Z            hipfftExecZ2Z
#define cufftDestroy            hipfftDestroy
#define CUFFT_C2C               HIPFFT_C2C
#define CUFFT_Z2Z               HIPFFT_Z2Z
#define CUFFT_FORWARD           HIPFFT_FORWARD
#define CUFFT_INVERSE           HIPFFT_BACKWARD
#define CUFFT_SUCCESS           HIPFFT_SUCCESS

#else
// CUDA build: include the native headers
#include <cuda_runtime.h>
#include <cuComplex.h>
#include <cufft.h>
#endif
