// zLib License
//
// Copyright (c) 2024 Josh "ShadowLordAlpha"
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

module;

#include <stdexcept>
#include <GLFW/glfw3.h>

module glfw;

namespace glfw
{
    Library::Library()
    {
        if(!glfwInit())
        {
            throw std::runtime_error("Failed to initialize GLFW");
        }
    }

    Library::~Library()
    {
        glfwTerminate();
    }

    void setErrorCallback(ErrorFun fun)
    {
        // We could do our own error function with asserts but we want to stay as close to the glfw interface as
        //  possible currently.
        glfwSetErrorCallback(fun);
    }

    double getTime()
    {
        return glfwGetTime();
    }

    void pollEvents()
    {
        glfwPollEvents();
    }

    glProc getProcAddress(const char* procname)
    {
        return glfwGetProcAddress(procname);
    }
}
