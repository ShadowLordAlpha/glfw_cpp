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
//
// 2024-10-16: Modified for GLFW_CPP - Josh "ShadowLordAlpha"
//
#include <cstdio>
#include <cstdlib>

#include <glad/gl.h>
#define GLFW_INCLUDE_NONE

import glfw;

static void errorCallback(int error, const char* description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}

int main()
{
    glfw::setErrorCallback(errorCallback);
    glfw::Library library;

    glfw::windowHint(glfw::WindowHint::CONTEXT_VERSION_MAJOR, 3);
    glfw::windowHint(glfw::WindowHint::CONTEXT_VERSION_MINOR, 2);
    glfw::windowHint(glfw::WindowHint::OPENGL_PROFILE, glfw::WindowValue::OPENGL_CORE_PROFILE);

    glfw::Window wnd(640, 480, "glfw_cpp basic usage example");

    wnd.makeContextCurrent();
    int version = gladLoadGL(glfw::getProcAddress);
    if (version == 0) {
        return EXIT_FAILURE;
    }

    while(!wnd.shouldClose())
    {
        double time = glfw::getTime();
        glClearColor((sin(time) + 1.0) / 2.0, (cos(time) + 1.0) / 2.0, (-sin(time) + 1.0) / 2.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glfw::pollEvents();
        wnd.swapBuffers();
    }

    return EXIT_SUCCESS;
}
