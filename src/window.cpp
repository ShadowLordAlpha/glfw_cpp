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
#include <GLFW/glfw3.h>

//#include "checks.h";

module glfw;

namespace glfw
{
    void Deleter::operator()(GLFWwindow* ptr)
    {
        glfwDestroyWindow(ptr);
    }

    void defaultWindowHints()
    {
        glfwDefaultWindowHints();
    }

    void windowHint(WindowHint hint, bool value)
    {
        //assert(validateHintBoolean(hint) && "Hint is not valid or does not take a boolean");
        windowHint(hint, value ? GLFW_TRUE : GLFW_FALSE);
    }

    void windowHint(WindowHint hint, WindowValue value)
    {
        //assert(validateHintEnum(hint) && "Hint is not valid or does not take an enum value");
        windowHint(hint, static_cast<int>(value));
    }

    void windowHint(WindowHint hint, int value)
    {
        //assert(validateHintValue(hint, value) && "Hint is not valid or provided value is invalid");
        windowHint(static_cast<int>(hint), value);
    }

    void windowHint(WindowHint hint, const char* value)
    {
        //assert(validateHintString(hint) && "Hint is not valid or does not take a string value");
        windowHint(static_cast<int>(hint), value);
    }

    void windowHint(int hint, const char* value)
    {
        glfwWindowHintString(hint, value);
    }

    void windowHint(int hint, int value)
    {
        // No programmer checks here, not recommended for use
        glfwWindowHint(hint, value);
    }

    // Window methods below

    Window::Window() : Window(nullptr) {}

    GLFWwindow* createWindow(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share)
    {
        auto windowPtr = glfwCreateWindow(width, height, title, monitor, share);
        if(!windowPtr)
        {
            throw std::runtime_error(getError());
        }
        return windowPtr;
    }

    Window::Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share) : ptr(createWindow(width, height, title, monitor, share)) {}

    Window::Window(GLFWwindow* window) : ptr(window) {}

    Window::operator GLFWwindow*() const
    {
        return ptr.get();
    }

    Window::operator bool() const
    {
        return ptr.get() != nullptr;
    }

    void Window::makeContextCurrent()
    {
        glfwMakeContextCurrent(ptr.get());
    }

    bool Window::shouldClose() const
    {
        return glfwWindowShouldClose(ptr.get());
    }

    void Window::swapBuffers()
    {
        glfwSwapBuffers(*this);
    }

    Size Window::getFramebufferSize() const
    {
        int width, height;
        glfwGetFramebufferSize(ptr.get(), &width, &height);
        return {width, height};
    }

    void Window::setInputMode(InputMode mode, bool value)
    {
        setInputMode(static_cast<int>(mode), value ? GLFW_TRUE: GLFW_FALSE);
    }

    void Window::setInputMode(InputMode mode, InputValue value)
    {
        setInputMode(static_cast<int>(mode), static_cast<int>(value));
    }

    void Window::setInputMode(int mode, int value)
    {
        glfwSetInputMode(*this, mode, value);
    }

    int Window::getKey(int key)
    {
        return glfwGetKey(*this, key);
    }
}
