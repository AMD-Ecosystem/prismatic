# HIPShim.cmake - HIP build support for legacy FindCUDA-style CMakeLists
# Provides cuda_add_executable, cuda_add_library, cuda_add_cufft_to_target
# shim macros that compile .cu sources as HIP when USE_HIP is ON.

option(USE_HIP "Build with HIP for AMD GPUs" OFF)

if(USE_HIP)
    # enable_language(HIP) honors an explicit -DCMAKE_HIP_ARCHITECTURES, otherwise
    # auto-detects the host GPU(s), and errors on a no-GPU build host.
    enable_language(HIP)

    # Find hipFFT
    find_package(hipfft REQUIRED)

    # Add USE_HIP definition
    add_definitions(-DUSE_HIP)

    # Shadow cuda_runtime.h, cuComplex.h and cufft.h with HIP equivalents
    include_directories(BEFORE ${CMAKE_SOURCE_DIR}/hip_compat)

    # Shim: cuda_add_executable -> add_executable with HIP language
    macro(cuda_add_executable target_name)
        set(_sources ${ARGN})
        # Filter out OPTIONS keyword and its arguments
        set(_filtered_sources)
        set(_skip_next FALSE)
        foreach(_arg ${_sources})
            if(_skip_next)
                set(_skip_next FALSE)
            elseif(_arg STREQUAL "OPTIONS")
                set(_skip_next TRUE)
            else()
                list(APPEND _filtered_sources ${_arg})
            endif()
        endforeach()

        add_executable(${target_name} ${_filtered_sources})

        # Mark .cu and .cpp sources as HIP language
        foreach(_src ${_filtered_sources})
            if(_src MATCHES "\\.(cu|cpp)$")
                set_source_files_properties(${_src} PROPERTIES LANGUAGE HIP)
            endif()
        endforeach()

        target_link_libraries(${target_name} hip::host)
    endmacro()

    # Shim: cuda_add_library -> add_library with HIP language
    macro(cuda_add_library target_name)
        set(_sources ${ARGN})
        # Determine library type (SHARED, STATIC, etc.)
        set(_lib_type)
        set(_filtered_sources)
        foreach(_arg ${_sources})
            if(_arg STREQUAL "SHARED" OR _arg STREQUAL "STATIC" OR _arg STREQUAL "MODULE")
                set(_lib_type ${_arg})
            else()
                list(APPEND _filtered_sources ${_arg})
            endif()
        endforeach()

        if(_lib_type)
            add_library(${target_name} ${_lib_type} ${_filtered_sources})
        else()
            add_library(${target_name} ${_filtered_sources})
        endif()

        # Mark .cu and .cpp sources as HIP language
        foreach(_src ${_filtered_sources})
            if(_src MATCHES "\\.(cu|cpp)$")
                set_source_files_properties(${_src} PROPERTIES LANGUAGE HIP)
            endif()
        endforeach()

        target_link_libraries(${target_name} hip::host)
    endmacro()

    # Shim: cuda_add_cufft_to_target -> link hipFFT
    macro(cuda_add_cufft_to_target target_name)
        target_link_libraries(${target_name} hip::hipfft)
    endmacro()

else()
    # CUDA build: find CUDA and use the standard FindCUDA module
    # (CMakeLists.txt handles this via find_package(CUDA REQUIRED))
endif()
