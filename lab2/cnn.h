#ifndef CNN_H_
#define CNN_H_

#include <stdexcept>
#include <string>

#define CL_HPP_CL_1_2_DEFAULT_BUILD
#define CL_HPP_TARGET_OPENCL_VERSION 120
#define CL_HPP_MINIMUM_OPENCL_VERSION 120
#include <CL/cl2.hpp>

const int kNum = 256;
const int kKernel = 5;
const int kImSize = 224;
const int kInImSize = 228;
const int kOutImSize = 112;

#define CASE(err) case err: return #err;
inline const char* ToString(cl_int err) {
  switch(err) {
    CASE(CL_SUCCESS);
    CASE(CL_DEVICE_NOT_FOUND);
    CASE(CL_DEVICE_NOT_AVAILABLE);
    CASE(CL_COMPILER_NOT_AVAILABLE);
    CASE(CL_MEM_OBJECT_ALLOCATION_FAILURE);
    CASE(CL_OUT_OF_RESOURCES);
    CASE(CL_OUT_OF_HOST_MEMORY);
    CASE(CL_PROFILING_INFO_NOT_AVAILABLE);
    CASE(CL_MEM_COPY_OVERLAP);
    CASE(CL_IMAGE_FORMAT_MISMATCH);
    CASE(CL_IMAGE_FORMAT_NOT_SUPPORTED);
    CASE(CL_BUILD_PROGRAM_FAILURE);
    CASE(CL_MAP_FAILURE);
    CASE(CL_MISALIGNED_SUB_BUFFER_OFFSET);
    CASE(CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST);
    CASE(CL_COMPILE_PROGRAM_FAILURE);
    CASE(CL_LINKER_NOT_AVAILABLE);
    CASE(CL_LINK_PROGRAM_FAILURE);
    CASE(CL_DEVICE_PARTITION_FAILED);
    CASE(CL_KERNEL_ARG_INFO_NOT_AVAILABLE);

    CASE(CL_INVALID_VALUE);
    CASE(CL_INVALID_DEVICE_TYPE);
    CASE(CL_INVALID_PLATFORM);
    CASE(CL_INVALID_DEVICE);
    CASE(CL_INVALID_CONTEXT);
    CASE(CL_INVALID_QUEUE_PROPERTIES);
    CASE(CL_INVALID_COMMAND_QUEUE);
    CASE(CL_INVALID_HOST_PTR);
    CASE(CL_INVALID_MEM_OBJECT);
    CASE(CL_INVALID_IMAGE_FORMAT_DESCRIPTOR);
    CASE(CL_INVALID_IMAGE_SIZE);
    CASE(CL_INVALID_SAMPLER);
    CASE(CL_INVALID_BINARY);
    CASE(CL_INVALID_BUILD_OPTIONS);
    CASE(CL_INVALID_PROGRAM);
    CASE(CL_INVALID_PROGRAM_EXECUTABLE);
    CASE(CL_INVALID_KERNEL_NAME);
    CASE(CL_INVALID_KERNEL_DEFINITION);
    CASE(CL_INVALID_KERNEL);
    CASE(CL_INVALID_ARG_INDEX);
    CASE(CL_INVALID_ARG_VALUE);
    CASE(CL_INVALID_ARG_SIZE);
    CASE(CL_INVALID_KERNEL_ARGS);
    CASE(CL_INVALID_WORK_DIMENSION);
    CASE(CL_INVALID_WORK_GROUP_SIZE);
    CASE(CL_INVALID_WORK_ITEM_SIZE);
    CASE(CL_INVALID_GLOBAL_OFFSET);
    CASE(CL_INVALID_EVENT_WAIT_LIST);
    CASE(CL_INVALID_EVENT);
    CASE(CL_INVALID_OPERATION);
    CASE(CL_INVALID_GL_OBJECT);
    CASE(CL_INVALID_BUFFER_SIZE);
    CASE(CL_INVALID_MIP_LEVEL);
    CASE(CL_INVALID_GLOBAL_WORK_SIZE);
    CASE(CL_INVALID_PROPERTY);
    CASE(CL_INVALID_IMAGE_DESCRIPTOR);
    CASE(CL_INVALID_COMPILER_OPTIONS);
    CASE(CL_INVALID_LINKER_OPTIONS);
    CASE(CL_INVALID_DEVICE_PARTITION_COUNT);
    CASE(CL_INVALID_PIPE_SIZE);
    CASE(CL_INVALID_DEVICE_QUEUE);

    default: return "CL_UNKNOWN_ERROR";
  }
}
#undef CASE

#define CL_CHECK(err) ClCheck((err), __FILE__, __LINE__);
inline void ClCheck(cl_int err, const char* file, int line) {
  if (err != CL_SUCCESS) {
    throw std::runtime_error(
        std::string(file) + ":" + std::to_string(line) + ": " + ToString(err));
  }
}

// Utility function declarations.
void LoadData(const std::string& data_dir,
              float input[kNum][kInImSize][kInImSize],
              float weight[kNum][kNum][kKernel][kKernel], float bias[kNum]);
int Verify(const std::string& data_dir,
           const float output[kNum][kOutImSize][kOutImSize]);
void CnnKernel(
    const float input[kNum][kInImSize][kInImSize],
    const float weight[kNum][kNum][kKernel][kKernel],
    const float bias[kNum], float output[kNum][kOutImSize][kOutImSize]);

void CnnSequential(
    const float input[kNum][kInImSize][kInImSize],
    const float weight[kNum][kNum][kKernel][kKernel], const float bias[kNum],
    float output[kNum][kOutImSize][kOutImSize]);
#endif
