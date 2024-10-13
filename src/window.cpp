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

#include <memory>
#include <cassert>
#include <stdexcept>

#include "GLFW/glfw3.h"

module glfw;

namespace glfw
{
    void Deleter::operator()(GLFWwindow* ptr)
    {
        glfwDestroyWindow(ptr);
    }

    Window::Window(int width, int height, const char* title)
    {
        auto windowPtr = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if(!windowPtr)
        {
            throw std::runtime_error("Failed to create a GLFW window.");
        }
        ptr = std::unique_ptr<GLFWwindow, Deleter>(windowPtr);
    }

    Window::Window(GLFWwindow* window)
    {
        ptr = std::unique_ptr<GLFWwindow, Deleter>(window);
    }

    Window::operator GLFWwindow*() const
    {
        return ptr.get();
    }

    void Window::makeContextCurrent()
    {
        glfwMakeContextCurrent(*this);
    }

    bool Window::shouldClose() const
    {
        return glfwWindowShouldClose(*this);
    }

    void Window::swapBuffers()
    {
        glfwSwapBuffers(*this);
    }

    void windowHint(WindowHint hint, bool value)
    {
        assert(hint == WindowHint::RESIZABLE
            || hint == WindowHint::VISIBLE
            || hint == WindowHint::DECORATED
            || hint == WindowHint::FOCUSED
            || hint == WindowHint::AUTO_ICONIFY
            || hint == WindowHint::FLOATING
            || hint == WindowHint::STEREO
            || hint == WindowHint::SRGB_CAPABLE
            || hint == WindowHint::DOUBLEBUFFER
            || hint == WindowHint::OPENGL_FORWARD_COMPAT
            || hint == WindowHint::OPENGL_DEBUG_CONTEXT);

        windowHint(hint, value ? GLFW_TRUE : GLFW_FALSE);
    }

    void windowHint(WindowHint hint, WindowValue value)
    {
        windowHint(hint, static_cast<int>(value));
    }

    void windowHint(WindowHint hint, int value)
    {
        glfwWindowHint(static_cast<int>(hint), value);
    }
}
