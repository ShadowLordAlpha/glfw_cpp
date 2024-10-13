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

namespace glfw
{
    struct Deleter
    {
        void operator()(GLFWwindow* ptr);
    };
}

export namespace glfw
{
    class Window
    {
    public:
        Window(int width, int height, const char* title);
        explicit Window(GLFWwindow* window);

        operator GLFWwindow*() const; // NOLINT(*-explicit-constructor)

        void makeContextCurrent();
        [[nodiscard]] bool shouldClose() const;
        void swapBuffers();

    private:
        std::unique_ptr<GLFWwindow, Deleter> ptr;
    };

    enum class WindowHint
    {
        RESIZABLE = GLFW_RESIZABLE,
        VISIBLE = GLFW_VISIBLE,
        DECORATED = GLFW_DECORATED,
        FOCUSED = GLFW_FOCUSED,
        AUTO_ICONIFY = GLFW_AUTO_ICONIFY,
        FLOATING = GLFW_FLOATING,
        RED_BIT = GLFW_RED_BITS,
        GREEN_BITS = GLFW_GREEN_BITS,
        BLUE_BITS = GLFW_BLUE_BITS,
        ALPHA_BITS = GLFW_ALPHA_BITS,
        DEPTH_BITS = GLFW_DEPTH_BITS,
        STENCIL_BITS = GLFW_STENCIL_BITS,
        ACCUM_RED_BITS = GLFW_ACCUM_RED_BITS,
        ACCUM_GREEN_BITS = GLFW_ACCUM_GREEN_BITS,
        ACCUM_BLUE_BITS = GLFW_ACCUM_BLUE_BITS,
        ACCUM_ALPHA_BITS = GLFW_ACCUM_ALPHA_BITS,
        AUX_BUFFERS = GLFW_AUX_BUFFERS,
        SAMPLES = GLFW_SAMPLES,
        REFRESH_RATE = GLFW_REFRESH_RATE,
        STEREO = GLFW_STEREO,
        SRGB_CAPABLE = GLFW_SRGB_CAPABLE,
        DOUBLEBUFFER = GLFW_DOUBLEBUFFER,
        CLIENT_API = GLFW_CLIENT_API,
        CONTEXT_VERSION_MAJOR = GLFW_CONTEXT_VERSION_MAJOR,
        CONTEXT_VERSION_MINOR = GLFW_CONTEXT_VERSION_MINOR,
        CONTEXT_ROBUSTNESS = GLFW_CONTEXT_ROBUSTNESS,
        CONTEXT_RELEASE_BEHAVIOR = GLFW_CONTEXT_RELEASE_BEHAVIOR,
        OPENGL_FORWARD_COMPAT = GLFW_OPENGL_FORWARD_COMPAT,
        OPENGL_DEBUG_CONTEXT = GLFW_OPENGL_DEBUG_CONTEXT,
        OPENGL_PROFILE = GLFW_OPENGL_PROFILE,
    };

    enum class WindowValue
    {
        DONT_CARE = GLFW_DONT_CARE,
        OPENGL_API = GLFW_OPENGL_API,
        OPENGL_ES_API = GLFW_OPENGL_ES_API,
        NO_ROBUSTNESS = GLFW_NO_ROBUSTNESS,
        NO_RESET_NOTIFICATION = GLFW_NO_RESET_NOTIFICATION,
        LOSE_CONTEXT_ON_RESET = GLFW_LOSE_CONTEXT_ON_RESET,
        ANY_RELEASE_BEHAVIOR = GLFW_ANY_RELEASE_BEHAVIOR,
        RELEASE_BEHAVIOR_FLUSH = GLFW_RELEASE_BEHAVIOR_FLUSH,
        RELEASE_BEHAVIOR_NONE = GLFW_RELEASE_BEHAVIOR_NONE,
        OPENGL_ANY_PROFILE = GLFW_OPENGL_ANY_PROFILE,
        OPENGL_COMPAT_PROFILE = GLFW_OPENGL_COMPAT_PROFILE,
        OPENGL_CORE_PROFILE = GLFW_OPENGL_CORE_PROFILE,
    };

    inline void windowHint(WindowHint hint, bool value);
    inline void windowHint(WindowHint hint, WindowValue value);
    inline void windowHint(WindowHint hint, int value);
    inline void windowHint(int hint, int value);
}
