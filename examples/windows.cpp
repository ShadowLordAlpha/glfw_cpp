//========================================================================
// Simple multi-window example
// Copyright (c) Camilla Löwy <elmindreda@glfw.org>
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
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
//========================================================================

// This file has been modified by Josh "ShadowLordAlpha" to make use of GLFW_CPP and be in C++

#include <cstdio>
#include <cstdlib>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

import glfw;

int main()
{
    int xpos, ypos, height;

    glfw::Window windows[4];

    glfw::Library library;

    glfw::windowHint(glfw::WindowHint::DECORATED, false);

    glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), &xpos, &ypos, NULL, &height);

    for (int i = 0;  i < 4;  i++)
    {
        const int size = height / 5;
        const struct
        {
            float r, g, b;
        } colors[] =
        {
            { 0.95f, 0.32f, 0.11f },
            { 0.50f, 0.80f, 0.16f },
            {   0.f, 0.68f, 0.94f },
            { 0.98f, 0.74f, 0.04f }
        };

        // TODO: add GLFW 3.4 support, we are 3.1 atm
        if (i > 0)
            glfw::windowHint(GLFW_FOCUS_ON_SHOW, false);

        glfw::windowHint(GLFW_POSITION_X, xpos + size * (1 + (i & 1)));
        glfw::windowHint(GLFW_POSITION_Y, ypos + size * (1 + (i >> 1)));

        windows[i] = glfw::Window(size, size, "Multi-Window Example");

        glfwSetInputMode(windows[i], GLFW_STICKY_KEYS, GLFW_TRUE);

        windows[i].makeContextCurrent();
        gladLoadGL(glfw::getProcAddress);
        glClearColor(colors[i].r, colors[i].g, colors[i].b, 1.f);
    }

    for (;;)
    {
        for (int i = 0;  i < 4;  i++)
        {
            windows[i].makeContextCurrent();
            glClear(GL_COLOR_BUFFER_BIT);
            windows[i].swapBuffers();

            if (windows[i].shouldClose() ||
                glfwGetKey(windows[i], GLFW_KEY_ESCAPE))
            {
                return EXIT_SUCCESS;
            }
        }

        glfw::waitEvents();
    }
}
