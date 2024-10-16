# glfw_cpp
 
A side project to wrap glfw in C++ RAII as well as use the mostly new C++20 modules. May go somewhere, may not but im mostly using this for properly learning several things all at once.
___
UserPointers for raw GLFW objects is restricted and should not be used if planning to use callback or other specific types of functions throught this library, there is an object replacement but the library itself requires the use of these pointers to for proper implementation of different portions, primarily working with callbacks. As long as the method is used through this libraries object it will be fine.
Though this is mainly just for windows because of their callback needs...