# opencl-boilerplate
A small C++ class which wraps some of the OpenCL boilerplate.
### What does this do?
OpenCL is very flexible since it is designed to handle multiple platforms and devices simultaneously.
If you only have a single GPU, then you'll need to write a lot of boilerplate code for simple programs.
Instantiate the class and call `InitializeContext`
to automatically find an OpenCL platform, device, and context.


```c++
OpenCLManager cl_manager;
cl_manager.InitializeContext();

// Now you can access
cl_manager.platform;
cl_manager.device;
cl_manager.context;
cl_manager.command_queue;
```
