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

    Window* getCurrentContext()
    {
        auto window = glfwGetCurrentContext();
        return static_cast<Window *>(glfwGetWindowUserPointer(window));
    }

    // Window methods below

    Window::Window() : Window(nullptr) {}

    GLFWwindow* createWindow(int width, int height, const char *title, Monitor* monitor, Window* share)
    {
        auto windowPtr = glfwCreateWindow(width, height, title, monitor->get(), share->get());
        if(!windowPtr)
        {
            throw std::runtime_error(getError());
        }
        return windowPtr;
    }

    Window::Window(int width, int height, const char* title, Monitor* monitor, Window* share) : Window(createWindow(width, height, title, monitor, share)) {}

    Window::Window(GLFWwindow* window) : ptr(window)
    {
        if(!ptr.get())
        {
            glfwSetWindowUserPointer(ptr.get(), this);
        }
    }

    GLFWwindow* Window::get() const
    {
        assert(ptr.get() != nullptr);
        return ptr.get();
    }

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
        assert(ptr.get() != nullptr);
        return glfwWindowShouldClose(ptr.get());
    }

    void Window::setShouldClose(bool value)
    {
        assert(ptr.get() != nullptr);
        glfwSetWindowShouldClose(ptr.get(), value);
    }

    const char* Window::getTitle() const
    {
        assert(ptr.get() != nullptr);
        return glfwGetWindowTitle(ptr.get());
    }

    void Window::setTitle(const char* title) const
    {
        assert(ptr.get() != nullptr);
        glfwSetWindowTitle(ptr.get(), title);
    }

    void Window::setIcon(const std::vector<Image>& images) // TODO: implement once Image is implemented, does it need to be optional?
    {
        assert(ptr.get() != nullptr);
        glfwSetWindowIcon(ptr.get(), images.size(), images.data());
    }

    Position<int> Window::getPos() const
    {
        assert(ptr.get() != nullptr);
        int x, y;
        glfwGetWindowPos(ptr.get(), &x, &y);
        return {x, y};
    }

    void Window::setPos(Position<int> pos)
    {
        assert(ptr.get() != nullptr);
        glfwSetWindowPos(ptr.get(), pos.x, pos.y);
    }

    Size Window::getSize() const
    {
        assert(ptr.get() != nullptr);
        int width, height;
        glfwGetWindowSize(ptr.get(), &width, &height);
        return {width, height};
    }

    void Window::setSizeLimits(Size min, Size max)
    {
        assert(ptr.get() != nullptr);
        glfwSetWindowSizeLimits(ptr.get(), min.width, min.height, max.width, max.height);
    }

    void Window::setAspectRatio(int numer, int denom)
    {
        assert(ptr.get() != nullptr);
        glfwSetWindowAspectRatio(ptr.get(), numer, denom);
    }

    void Window::setSize(Size size)
    {
        assert(ptr.get() != nullptr);
        glfwSetWindowSize(ptr.get(), size.width, size.height);
    }

    Size Window::getFramebufferSize() const
    {
        assert(ptr.get() != nullptr);
        int width, height;
        glfwGetFramebufferSize(ptr.get(), &width, &height);
        return {width, height};
    }

    FrameSize Window::getFrameSize()
    {
        assert(ptr.get() != nullptr);
        int left, right, top, bottom;
        glfwGetWindowFrameSize(ptr.get(), &left, &top, &right, &bottom);
        return {left, top, right, bottom};
    }

    Scale Window::getContentScale()
    {
        assert(ptr.get() != nullptr);
        float width, height;
        glfwGetWindowContentScale(ptr.get(), &width, &height);
        return {width, height};
    }

    float Window::getOpacity() const
    {
        assert(ptr.get() != nullptr);
        return glfwGetWindowOpacity(ptr.get());
    }

    void Window::setOpacity(float opacity)
    {
        assert(ptr.get() != nullptr);
        glfwSetWindowOpacity(ptr.get(), opacity);
    }

    void Window::iconify()
    {
        assert(ptr.get() != nullptr);
        glfwIconifyWindow(ptr.get());
    }

    void Window::restore()
    {
        assert(ptr.get() != nullptr);
        glfwRestoreWindow(ptr.get());
    }

    void Window::maximize()
    {
        assert(ptr.get() != nullptr);
        glfwMaximizeWindow(ptr.get());
    }

    void Window::show()
    {
        assert(ptr.get() != nullptr);
        glfwShowWindow(ptr.get());
    }

    void Window::hide()
    {
        assert(ptr.get() != nullptr);
        glfwHideWindow(ptr.get());
    }

    void Window::focus()
    {
        assert(ptr.get() != nullptr);
        glfwFocusWindow(ptr.get());
    }

    void Window::requestAttention()
    {
        assert(ptr.get() != nullptr);
        glfwRequestWindowAttention(ptr.get());
    }

    Monitor Window::getMonitor()
    {
        assert(ptr.get() != nullptr);
        return glfwGetWindowMonitor(ptr.get());
    }

    void Window::setMonitor(Monitor monitor, Position<int> pos, Size size, int refreshRate)
    {
        assert(ptr.get() != nullptr);
        glfwSetWindowMonitor(ptr.get(), monitor, pos.x, pos.y, size.width, size.height, refreshRate);
    }

    int Window::getAttrib(int attrib) const // TODO: enum values?
    {
        assert(ptr.get() != nullptr);
        return glfwGetWindowAttrib(ptr.get(), attrib);
    }

    void Window::setAttrib(int attrib, int value) // TODO: enum values?
    {
        assert(ptr.get() != nullptr);
        glfwSetWindowAttrib(ptr.get(), attrib, value);
    }

    void Window::setUserPointer(void* pointer)
    {
        assert(ptr.get() != nullptr);
        user = pointer;
    }

    void* Window::getUserPointer() const
    {
        assert(ptr.get() != nullptr);
        return user;
    }

    WindowPosFunction Window::setPosCallback(WindowPosFunction callback)
    {
        assert(ptr.get() != nullptr);
        windowPosFunction = callback;
        glfwSetWindowPosCallback(ptr.get(), [](GLFWwindow* ptr, int x, int y)
        {
            auto window = static_cast<Window*>(glfwGetWindowUserPointer(ptr));
            window->windowPosFunction(*window, {x, y});
        });
        return callback;
    }

    WindowSizeFunction Window::setSizeCallback(WindowSizeFunction callback)
    {
        assert(ptr.get() != nullptr);
        windowSizeFunction = callback;
        glfwSetWindowSizeCallback(ptr.get(), [](GLFWwindow* ptr, int w, int h)
        {
            auto window = static_cast<Window*>(glfwGetWindowUserPointer(ptr));
            window->windowSizeFunction(*window, {w, h});
        });
        return callback;
    }

    WindowCloseFunction Window::setCloseCallback(WindowCloseFunction callback)
    {
        assert(ptr.get() != nullptr);
        windowCloseFunction = callback;
        glfwSetWindowCloseCallback(ptr.get(), [](GLFWwindow* ptr)
        {
            auto window = static_cast<Window*>(glfwGetWindowUserPointer(ptr));
            window->windowCloseFunction(*window);
        });
        return callback;
    }

    WindowRefreshFunction Window::setRefreshCallback(WindowRefreshFunction callback)
    {
        assert(ptr.get() != nullptr);
        windowRefreshFunction = callback;
        glfwSetWindowRefreshCallback(ptr.get(), [](GLFWwindow* ptr)
        {
            auto window = static_cast<Window*>(glfwGetWindowUserPointer(ptr));
            window->windowRefreshFunction(*window);
        });
        return callback;
    }

    WindowFocusFunction Window::setFocusCallback(WindowFocusFunction callback)
    {
        assert(ptr.get() != nullptr);
        windowFocusFunction = callback;
        glfwSetWindowFocusCallback(ptr.get(), [](GLFWwindow* ptr, int f)
        {
            auto window = static_cast<Window*>(glfwGetWindowUserPointer(ptr));
            window->windowFocusFunction(*window, f == GLFW_TRUE);
        });
        return callback;
    }

    WindowIconifyFunction Window::setIconifyCallback(WindowIconifyFunction callback)
    {
        assert(ptr.get() != nullptr);
        windowIconifyFunction = callback;
        glfwSetWindowIconifyCallback(ptr.get(), [](GLFWwindow* ptr, int i)
        {
            auto window = static_cast<Window*>(glfwGetWindowUserPointer(ptr));
            window->windowIconifyFunction(*window, i == GLFW_TRUE);
        });
        return callback;
    }

    WindowMaximizeFunction Window::setMaximizeCallback(WindowMaximizeFunction callback)
    {
        assert(ptr.get() != nullptr);
        windowMaximizeFunction = callback;
        glfwSetWindowMaximizeCallback(ptr.get(), [](GLFWwindow* ptr, int m)
        {
            auto window = static_cast<Window*>(glfwGetWindowUserPointer(ptr));
            window->windowMaximizeFunction(*window, m == GLFW_TRUE);
        });
        return callback;
    }

    FrameBufferSizeFunction Window::setFramebufferSizeCallback(FrameBufferSizeFunction callback)
    {
        assert(ptr.get() != nullptr);
        windowFrameBufferSizeFunction = callback;
        glfwSetFramebufferSizeCallback(ptr.get(), [](GLFWwindow* ptr, int w, int h)
        {
            auto window = static_cast<Window*>(glfwGetWindowUserPointer(ptr));
            window->windowFrameBufferSizeFunction(*window, {w, h});
        });
        return callback;
    }

    WindowContentScaleFunction Window::setContentScaleCallback(WindowContentScaleFunction callback)
    {
        assert(ptr.get() != nullptr);
        windowContentScaleFunction = callback;
        glfwSetWindowContentScaleCallback(ptr.get(), [](GLFWwindow* ptr, float x, float y)
        {
            auto window = static_cast<Window*>(glfwGetWindowUserPointer(ptr));
            window->windowContentScaleFunction(*window, {x, y});
        });
        return callback;
    }

    int Window::getInputMode(InputMode mode) // Type checked/convince overload
    {
        assert(ptr.get() != nullptr);
        return getInputMode(static_cast<int>(mode));
    }
    int Window::getInputMode(int mode)
    {
        assert(ptr.get() != nullptr);
        return glfwGetInputMode(ptr.get(), mode);
    }

    void Window::setInputMode(InputMode mode, bool value)
    {
        assert(ptr.get() != nullptr);
        setInputMode(static_cast<int>(mode), value ? GLFW_TRUE: GLFW_FALSE);
    }

    void Window::setInputMode(InputMode mode, InputValue value)
    {
        assert(ptr.get() != nullptr);
        setInputMode(static_cast<int>(mode), static_cast<int>(value));
    }

    void Window::setInputMode(int mode, int value)
    {
        assert(ptr.get() != nullptr);
        glfwSetInputMode(ptr.get(), mode, value);
    }

    int Window::getKey(int key) const
    {
        assert(ptr.get() != nullptr);
        return glfwGetKey(ptr.get(), key);
    }

    int Window::getMouseButton(int button) const // TODO: type checked method
    {
        assert(ptr.get() != nullptr);
        return glfwGetMouseButton(ptr.get(), button);
    }

    Position<double> Window::getCursorPos() const
    {
        assert(ptr.get() != nullptr);
        double x, y;
        glfwGetCursorPos(ptr.get(), &x, &y);
        return {x, y};
    }

    void Window::setCursorPos(Position<double> pos)
    {
        assert(ptr.get() != nullptr);
        glfwSetCursorPos(ptr.get(), pos.x, pos.y);
    }

    void Window::setCursor(Cursor* cursor)
    {
        assert(ptr.get() != nullptr);
        glfwSetCursor(ptr.get(), *cursor);
    }

    KeyFunction Window::setKeyCallback(KeyFunction callback)
    {
        assert(ptr.get() != nullptr);
        keyFunction = callback;
        glfwSetKeyCallback(ptr.get(), [](GLFWwindow* ptr, int key, int scancode, int action, int mods)
        {
            auto window = static_cast<Window*>(glfwGetWindowUserPointer(ptr));
            window->keyFunction(*window, key, scancode, action, mods);
        });
        return callback;
    }

    CharFunction Window::setCharCallback(CharFunction callback)
    {
        assert(ptr.get() != nullptr);
        charFunction = callback;
        glfwSetCharCallback(ptr.get(), [](GLFWwindow* ptr, unsigned int codepoint)
        {
            auto window = static_cast<Window*>(glfwGetWindowUserPointer(ptr));
            window->charFunction(*window, codepoint);
        });
        return callback;
    }

    CharModsFunction Window::setCharModsCallback(CharModsFunction callback)
    {
        assert(ptr.get() != nullptr);
        charModsFunction = callback;
        glfwSetCharModsCallback(ptr.get(), [](GLFWwindow* ptr, unsigned int codepoint, int mods)
        {
            auto window = static_cast<Window*>(glfwGetWindowUserPointer(ptr));
            window->charModsFunction(*window, codepoint, mods);
        });
        return callback;
    }

    MouseButtonFunction Window::setMouseButtonCallback(MouseButtonFunction callback)
    {
        assert(ptr.get() != nullptr);
        mouseButtonFunction = callback;
        glfwSetMouseButtonCallback(ptr.get(), [](GLFWwindow* ptr, int button, int action, int mods)
        {
            auto window = static_cast<Window*>(glfwGetWindowUserPointer(ptr));
            window->mouseButtonFunction(*window, button, action, mods);
        });
        return callback;
    }

    CursorPosFunction Window::setCursorPosCallback(CursorPosFunction callback)
    {
        assert(ptr.get() != nullptr);
        cursorPosFunction = callback;
        glfwSetCursorPosCallback(ptr.get(), [](GLFWwindow* ptr, double xpos, double ypos)
        {
            auto window = static_cast<Window*>(glfwGetWindowUserPointer(ptr));
            window->cursorPosFunction(*window, {xpos, ypos});
        });
        return callback;
    }

    CursorEnterFunction Window::setCursorEnterCallback(CursorEnterFunction callback)
    {
        assert(ptr.get() != nullptr);
        cursorEnterFunction = callback;
        glfwSetCursorEnterCallback(ptr.get(), [](GLFWwindow* ptr, int e)
        {
            auto window = static_cast<Window*>(glfwGetWindowUserPointer(ptr));
            window->cursorEnterFunction(*window, e == GLFW_TRUE);
        });
        return callback;
    }

    ScrollFunction Window::setScrollCallback(ScrollFunction callback)
    {
        assert(ptr.get() != nullptr);
        scrollFunction = callback;
        glfwSetScrollCallback(ptr.get(), [](GLFWwindow* ptr, double xoffset, double yoffset)
        {
            auto window = static_cast<Window*>(glfwGetWindowUserPointer(ptr));
            window->scrollFunction(*window, {xoffset, yoffset});
        });
        return callback;
    }

    DropFunction Window::setDropCallback(DropFunction callback)
    {
        assert(ptr.get() != nullptr);
        dropFunction = callback;
        glfwSetDropCallback(ptr.get(), [](GLFWwindow* ptr, int path_count, const char* paths[])
        {
            auto window = static_cast<Window*>(glfwGetWindowUserPointer(ptr));
            window->dropFunction(*window, path_count, paths);
        });
        return callback;
    }

    void Window::setClipboardString(const char* string)
    {
        assert(ptr.get() != nullptr);
        glfwSetClipboardString(ptr.get(), string);
    }

    const char* Window::getClipboardString()
    {
        assert(ptr.get() != nullptr);
        return glfwGetClipboardString(ptr.get());
    }

    void Window::makeContextCurrent()
    {
        assert(ptr.get() != nullptr);
        glfwMakeContextCurrent(ptr.get());
    }

    void Window::swapBuffers()
    {
        assert(ptr.get() != nullptr);
        glfwSwapBuffers(ptr.get());
    }
}
