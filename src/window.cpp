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
#include <functional>
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

    bool Window::shouldClose() const
    {
        return glfwWindowShouldClose(ptr.get());
    }

    void Window::setShouldClose(bool value)
    {
        glfwSetWindowShouldClose(ptr.get(), value);
    }

    const char* Window::getTitle() const
    {
        return glfwGetWindowTitle(ptr.get());
    }

    void Window::setTitle(const char* title) const
    {
        glfwSetWindowTitle(ptr.get(), title);
    }

    void Window::setIcon(const std::vector<Image>& images) // TODO: implement once Image is implemented, does it need to be optional?
    {
        glfwSetWindowIcon(ptr.get(), images.size(), images.data());
    }

    Position<int> Window::getPos() const
    {
        int x, y;
        glfwGetWindowPos(ptr.get(), &x, &y);
        return {x, y};
    }

    void Window::setPos(Position<int> pos)
    {
        glfwSetWindowPos(ptr.get(), pos.x, pos.y);
    }

    Size Window::getSize() const
    {
        int width, height;
        glfwGetWindowSize(ptr.get(), &width, &height);
        return {width, height};
    }

    void Window::setSizeLimits(Size min, Size max)
    {
        glfwSetWindowSizeLimits(ptr.get(), min.width, min.height, max.width, max.height);
    }

    void Window::setAspectRatio(int numer, int denom)
    {
        glfwSetWindowAspectRatio(ptr.get(), numer, denom);
    }

    void Window::setSize(Size size)
    {
        glfwSetWindowSize(ptr.get(), size.width, size.height);
    }

    Size Window::getFramebufferSize() const
    {
        int width, height;
        glfwGetFramebufferSize(ptr.get(), &width, &height);
        return {width, height};
    }

    FrameSize Window::getFrameSize()
    {
        int left, right, top, bottom;
        glfwGetWindowFrameSize(ptr.get(), &left, &top, &right, &bottom);
        return {left, top, right, bottom};
    }

    Scale Window::getContentScale()
    {
        float width, height;
        glfwGetWindowContentScale(ptr.get(), &width, &height);
        return {width, height};
    }

    float Window::getOpacity() const
    {
        return glfwGetWindowOpacity(ptr.get());
    }

    void Window::setOpacity(float opacity)
    {
        glfwSetWindowOpacity(ptr.get(), opacity);
    }

    void Window::iconify()
    {
        glfwIconifyWindow(ptr.get());
    }

    void Window::restore()
    {
        glfwRestoreWindow(ptr.get());
    }

    void Window::maximize()
    {
        glfwMaximizeWindow(ptr.get());
    }

    void Window::show()
    {
        glfwShowWindow(ptr.get());
    }

    void Window::hide()
    {
        glfwHideWindow(ptr.get());
    }

    void Window::focus()
    {
        glfwFocusWindow(ptr.get());
    }

    void Window::requestAttention()
    {
        glfwRequestWindowAttention(ptr.get());
    }

    Monitor Window::getMonitor()
    {
        return glfwGetWindowMonitor(ptr.get());
    }

    void Window::setMonitor(Monitor monitor, Position<int> pos, Size size, int refreshRate)
    {
        glfwSetWindowMonitor(ptr.get(), monitor, pos.x, pos.y, size.width, size.height, refreshRate);
    }

    int Window::getAttrib(int attrib) const // TODO: enum values?
    {
        return glfwGetWindowAttrib(ptr.get(), attrib);
    }

    void Window::setAttrib(int attrib, int value) // TODO: enum values?
    {
        glfwSetWindowAttrib(ptr.get(), attrib, value);
    }

    void Window::setUserPointer(void* pointer)
    {
        glfwSetWindowUserPointer(ptr.get(), pointer);
    }

    void* Window::getUserPointer() const
    {
        return glfwGetWindowUserPointer(ptr.get());
    }

        // TODO
        /*
        WindowPosFunction setWindowPosCallback(WindowPosFunction callback);
        GLFWwindowposfun glfwSetWindowPosCallback(GLFWwindowposfun callback);
        GLFWwindowsizefun glfwSetWindowSizeCallback(GLFWwindowsizefun callback);
        GLFWwindowclosefun glfwSetWindowCloseCallback(GLFWwindowclosefun callback);
        GLFWwindowrefreshfun glfwSetWindowRefreshCallback(GLFWwindowrefreshfun callback);
        GLFWwindowfocusfun glfwSetWindowFocusCallback(GLFWwindowfocusfun callback);
        GLFWwindowiconifyfun glfwSetWindowIconifyCallback(GLFWwindowiconifyfun callback);
        GLFWwindowmaximizefun glfwSetWindowMaximizeCallback(GLFWwindowmaximizefun callback);
        GLFWframebuffersizefun glfwSetFramebufferSizeCallback(GLFWframebuffersizefun callback);
        GLFWwindowcontentscalefun glfwSetWindowContentScaleCallback(GLFWwindowcontentscalefun callback);
         */
    int Window::getInputMode(InputMode mode) // Type checked/convince overload
    {
        return getInputMode(static_cast<int>(mode));
    }
    int Window::getInputMode(int mode)
    {
        return glfwGetInputMode(ptr.get(), mode);
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
        glfwSetInputMode(ptr.get(), mode, value);
    }

    int Window::getKey(int key) const
    {
        return glfwGetKey(ptr.get(), key);
    }

    int Window::getMouseButton(int button) const // TODO: type checked method
    {
        return glfwGetMouseButton(ptr.get(), button);
    }

    Position<double> Window::getCursorPos() const
    {
        double x, y;
        glfwGetCursorPos(ptr.get(), &x, &y);
        return {x, y};
    }

    void Window::setCursorPos(Position<double> pos)
    {
        glfwSetCursorPos(ptr.get(), pos.x, pos.y);
    }

    void Window::setCursor(Cursor* cursor)
    {
        glfwSetCursor(ptr.get(), *cursor);
    }

    /*
        GLFWkeyfun glfwSetKeyCallback(GLFWkeyfun callback);
        GLFWcharfun glfwSetCharCallback(GLFWcharfun callback);
        GLFWcharmodsfun glfwSetCharModsCallback(GLFWcharmodsfun callback);
        GLFWmousebuttonfun glfwSetMouseButtonCallback(GLFWmousebuttonfun callback);
        GLFWcursorposfun glfwSetCursorPosCallback(GLFWcursorposfun callback);
        GLFWcursorenterfun glfwSetCursorEnterCallback(GLFWcursorenterfun callback);
        GLFWscrollfun glfwSetScrollCallback(GLFWscrollfun callback);
        GLFWdropfun glfwSetDropCallback(GLFWdropfun callback);
        */
    void Window::setClipboardString(const char* string)
    {
        glfwSetClipboardString(ptr.get(), string);
    }

    const char* Window::getClipboardString()
    {
        return glfwGetClipboardString(ptr.get());
    }

    void Window::makeContextCurrent()
    {
        glfwMakeContextCurrent(ptr.get());
    }

    void Window::swapBuffers()
    {
        glfwSwapBuffers(ptr.get());
    }
}
