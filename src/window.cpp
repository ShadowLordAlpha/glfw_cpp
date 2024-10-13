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

    Window::Window() : ptr(nullptr) {}

    std::unique_ptr<GLFWwindow, Deleter> createWindow(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share)
    {
        auto windowPtr = glfwCreateWindow(width, height, title, monitor, share);
        if(!windowPtr)
        {
            throw std::runtime_error(getError());
        }
        return std::unique_ptr<GLFWwindow, Deleter>(windowPtr);
    }

    Window::Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share) : ptr(createWindow(width, height, title, monitor, share)) {}

    Window::Window(GLFWwindow* window) : ptr(window) {}

    Window::operator GLFWwindow*() const
    {
        if(ptr.get() == nullptr)
        {
            return nullptr;
        }
        return ptr.get();
    }

    Window::operator bool() const
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

    bool validateHintBoolean(WindowHint hint)
    {
        switch(hint)
        {
            case WindowHint::RESIZABLE:
            case WindowHint::VISIBLE:
            case WindowHint::DECORATED:
            case WindowHint::FOCUSED:
            case WindowHint::AUTO_ICONIFY:
            case WindowHint::FLOATING:
            case WindowHint::STEREO:
            case WindowHint::SRGB_CAPABLE:
            case WindowHint::DOUBLEBUFFER:
            case WindowHint::OPENGL_FORWARD_COMPAT:
            case WindowHint::OPENGL_DEBUG_CONTEXT:
                return true;
            default:
                return false;
        }
    }

    bool validateHintInt(WindowHint hint)
    {
        switch(hint)
        {
            case WindowHint::RED_BIT:
            case WindowHint::GREEN_BITS:
            case WindowHint::BLUE_BITS:
            case WindowHint::ALPHA_BITS:
            case WindowHint::DEPTH_BITS:
            case WindowHint::STENCIL_BITS:
            case WindowHint::ACCUM_RED_BITS:
            case WindowHint::ACCUM_GREEN_BITS:
            case WindowHint::ACCUM_BLUE_BITS:
            case WindowHint::ACCUM_ALPHA_BITS:
            case WindowHint::AUX_BUFFERS:
            case WindowHint::SAMPLES:
            case WindowHint::REFRESH_RATE:
            case WindowHint::CONTEXT_VERSION_MAJOR:
            case WindowHint::CONTEXT_VERSION_MINOR:
                return true;
            default:
                return false;
        }
    }

    bool validateHintEnum(WindowHint hint)
    {
        return !validateHintBoolean(hint); // literally everything but booleans are allowed
    }

    bool validateHintValue(WindowHint hint, int value)
    {
        switch(hint)
        {
            case WindowHint::RESIZABLE:
            case WindowHint::VISIBLE:
            case WindowHint::DECORATED:
            case WindowHint::FOCUSED:
            case WindowHint::AUTO_ICONIFY:
            case WindowHint::FLOATING:
            case WindowHint::STEREO:
            case WindowHint::SRGB_CAPABLE:
            case WindowHint::DOUBLEBUFFER:
            case WindowHint::OPENGL_FORWARD_COMPAT:
            case WindowHint::OPENGL_DEBUG_CONTEXT:
                return value == GLFW_TRUE || value == GLFW_FALSE;

            case WindowHint::RED_BIT:
            case WindowHint::GREEN_BITS:
            case WindowHint::BLUE_BITS:
            case WindowHint::ALPHA_BITS:
            case WindowHint::DEPTH_BITS:
            case WindowHint::STENCIL_BITS:
            case WindowHint::ACCUM_RED_BITS:
            case WindowHint::ACCUM_GREEN_BITS:
            case WindowHint::ACCUM_BLUE_BITS:
            case WindowHint::ACCUM_ALPHA_BITS:
            case WindowHint::AUX_BUFFERS:
            case WindowHint::SAMPLES:
            case WindowHint::REFRESH_RATE:
            case WindowHint::CONTEXT_VERSION_MAJOR:
            case WindowHint::CONTEXT_VERSION_MINOR:
                return value == GLFW_DONT_CARE || value >= 0 || value <= INT_MAX;

            case WindowHint::CLIENT_API:
                break;
            case WindowHint::CONTEXT_ROBUSTNESS:
                break;
            case WindowHint::CONTEXT_RELEASE_BEHAVIOR:
                break;
            case WindowHint::OPENGL_PROFILE:
                break;

            default:
                return false;
        }
    }

    void windowHint(WindowHint hint, bool value)
    {
        assert(validateHintBoolean(hint) && "Hint is not valid or does not take a boolean");
        windowHint(hint, value ? GLFW_TRUE : GLFW_FALSE);
    }

    void windowHint(WindowHint hint, WindowValue value)
    {
        assert(validateHintEnum(hint) && "Hint is not valid or does not take an enum value");
        windowHint(hint, static_cast<int>(value));
    }

    void windowHint(WindowHint hint, int value)
    {
        assert(validateHintValue(hint, value) && "Hint is not valid or provided value is invalid");
        windowHint(static_cast<int>(hint), value);
    }

    void windowHint(int hint, int value)
    {
        // No programmer checks here, not recommended for use
        glfwWindowHint(hint, value);
    }
}
