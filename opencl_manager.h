#pragma once

#include <CL/cl.hpp>
#include <iostream>

class OpenCLManager {
 private:
 public:
  cl::Platform platform;
  cl::Device device;
  cl::Context context;
  cl::CommandQueue command_queue;
  OpenCLManager();
  ~OpenCLManager();
  int InitializeContext();
  static void PrintClProgramBuildFailure(cl_int ret, cl_program program,
                                         cl_device_id device_id);
};