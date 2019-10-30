#include "opencl_manager.h"

OpenCLManager::OpenCLManager() {}

OpenCLManager::~OpenCLManager() {}

int OpenCLManager::InitializeContext() {
  cl_int ret = 0;
  // Filter for a 2.0 platform and set it as the default
  std::vector<cl::Platform> platforms;
  cl::Platform::get(&platforms);

  for (int i = 0; i < platforms.size(); i++) {
    std::string vendor_name = platforms[i].getInfo<CL_PLATFORM_NAME>();
    platform = platforms[i];
    bool is_nvidia = vendor_name.find("NVIDIA") != std::string::npos;
    if (is_nvidia) {
      i = platforms.size();
    }
  }
  if (platform() == NULL) {
    platform = platforms[0];
  }
  std::vector<cl::Device> devices;
  ret = platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);
  device = devices[0];
  context = cl::Context(device);
  command_queue = cl::CommandQueue(context, device);

  // Print out the GPU and the platform being used
  std::cout << "[OpenCLManager] Using " << device.getInfo<CL_DEVICE_NAME>()
            << " on platform " << platform.getInfo<CL_PLATFORM_NAME>()
            << std::endl;
  return 0;
}

void OpenCLManager::PrintClProgramBuildFailure(cl_int ret, cl_program program,
                                               cl_device_id device_id) {
  if (ret == CL_BUILD_PROGRAM_FAILURE) {
    size_t log_size;
    clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, 0, NULL,
                          &log_size);

    // Allocate memory for the log
    char* log = new char[log_size];

    // Get the log
    clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, log_size,
                          log, NULL);

    // Print the log
    std::cerr << log << std::endl;
    delete[] log;
  }
}