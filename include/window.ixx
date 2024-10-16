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

#include <GLFW\glfw3.h>

export module glfw:window;

import :monitor;
import :cursor;
import :type;

namespace glfw
{
    struct Deleter
    {
        void operator()(GLFWwindow* ptr);
    };
}

export namespace glfw
{
    class Window;

    inline void defaultWindowHints();

    inline void windowHint(WindowHint hint, bool value); // Type checked/convince overload
    inline void windowHint(WindowHint hint, WindowValue value); // Type checked/convince overload
    inline void windowHint(WindowHint hint, int value); // Type checked/convince overload
    inline void windowHint(WindowHint hint, const char* value); // Type checked/convince overload

    inline void windowHint(int hint, const char* value);
    inline void windowHint(int hint, int value);

    inline Window getCurrentContext();

    class Window
    {
    public:
        Window();
        Window(int width, int height, const char* title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
        explicit Window(GLFWwindow* window);

        operator GLFWwindow*() const; // NOLINT(*-explicit-constructor)
        operator bool() const; // NOLINT(*-explicit-constructor)

        [[nodiscard]] bool shouldClose() const;
        void setShouldClose(bool value);
        [[nodiscard]] const char* getTitle() const;
        void setTitle(const char* title) const;
        void setIcon(const std::vector<Image>& images); // TODO: implement once Image is implemented, does it need to be optional?
        [[nodiscard]] Position<int> getPos() const;
        void setPos(Position<int> pos);
        [[nodiscard]] Size getSize() const;
        void setSizeLimits(Size min, Size max);
        void setAspectRatio(int numer, int denom);
        void setSize(Size size);
        [[nodiscard]] Size getFramebufferSize() const;
        [[nodiscard]] FrameSize getFrameSize();
        [[nodiscard]] Scale getContentScale();
        [[nodiscard]] float getOpacity() const;
        void setOpacity(float opacity);

        void iconify();
        void restore();
        void maximize();
        void show();
        void hide();
        void focus();
        void requestAttention();

        Monitor getMonitor();
        void setMonitor(Monitor monitor, Position<int> pos, Size size, int refreshRate);
        [[nodiscard]] int getAttrib(int attrib) const; // TODO: enum values?
        void setAttrib(int attrib, int value); // TODO: enum values?
        void setUserPointer(void* pointer);
        [[nodiscard]] void* getUserPointer() const;
        WindowPosFunction setWindowPosCallback(WindowPosFunction callback);
        // TODO
        /*
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
        int getInputMode(InputMode mode); // Type checked/convince overload
        int getInputMode(int mode);
        void setInputMode(InputMode mode, bool value); // Type checked/convince overload
        void setInputMode(InputMode mode, InputValue value); // Type checked/convince overload
        void setInputMode(int mode, int value);
        int getKey(int key) const; // TODO: type checked method
        int getMouseButton(int button) const; // TODO: type checked method
        Position<double> getCursorPos() const;
        void setCursorPos(Position<double> pos);
        void setCursor(Cursor* cursor = nullptr); // TODO: check if we can pass a glfw cursor to this method, if not we may need to use the other type as we don't want to force us holding the object
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
        void setClipboardString(const char* string);
        const char* getClipboardString();
        void makeContextCurrent();
        void swapBuffers();

        // TODO: should glfwCreateWindowSurface go in here? it kinda matches so possibly?
    private:
        std::unique_ptr<GLFWwindow, Deleter> ptr;
        void* user; // welp... bullshit needed for this now...
    };
}
