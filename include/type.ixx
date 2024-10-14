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

export module glfw:type;
#include "GLFW/glfw3.h"

export namespace glfw
{

    // TODO: test if we can use our value instead
    //typedef (* MonitorFunction)(Monitor monitor, int event); // We want to use the Monitor object so we can't directly use GLFWmonitorfun
    using MonitorFunction = GLFWmonitorfun;

    // Redefine structs to be within our namespace
    using ErrorFun = GLFWerrorfun;
    using glProc = GLFWglproc;
    using Image = GLFWimage;
    using VideoMode = GLFWvidmode;
    using GammaRamp = GLFWgammaramp;

    struct Version
    {
        int major;
        int minor;
        int revision;
    };

    struct WorkArea
    {
        int x, y;
        int width, height;
    };

    template<typename type>
    struct Position
    {
        type x, y;
    };

    struct Size
    {
        int width, height;
    };

    struct Scale // This "could" be a Position<float> but that would kinda break type checking and the two are not the same
    {
        float x, y;
    };

    struct FrameSize
    {
        int left, top, right, bottom;
    };

    enum class InputValue
    {
        CURSOR_NORMAL = GLFW_CURSOR_NORMAL,
        CURSOR_HIDDEN = GLFW_CURSOR_HIDDEN ,
        CURSOR_DISABLED = GLFW_CURSOR_DISABLED,
        CURSOR_CAPTURED = GLFW_CURSOR_CAPTURED,
    };

    enum class InputMode
    {
        CURSOR = GLFW_CURSOR,
        STICKY_KEYS = GLFW_STICKY_KEYS,
        MOUSE_BUTTONS = GLFW_STICKY_MOUSE_BUTTONS,
        LOCK_KEY_MODS = GLFW_LOCK_KEY_MODS,
        RAW_MOUSE_MOTION = GLFW_RAW_MOUSE_MOTION,
    };

    enum class CursorShape
    {
        ARROW_CURSOR = GLFW_ARROW_CURSOR,
        IBEAM_CURSOR = GLFW_IBEAM_CURSOR,
        CROSSHAIR_CURSOR = GLFW_CROSSHAIR_CURSOR,
        POINTING_HAND_CURSOR = GLFW_POINTING_HAND_CURSOR,
        RESIZE_EW_CURSOR = GLFW_RESIZE_EW_CURSOR,
        RESIZE_NS_CURSOR = GLFW_RESIZE_NS_CURSOR,
        RESIZE_NWSE_CURSOR = GLFW_RESIZE_NWSE_CURSOR,
        RESIZE_NESW_CURSOR = GLFW_RESIZE_NESW_CURSOR,
        RESIZE_ALL_CURSOR = GLFW_RESIZE_ALL_CURSOR,
        NOT_ALLOWED_CURSOR = GLFW_NOT_ALLOWED_CURSOR,
    };

    enum class WindowHint
    {
        RESIZABLE = GLFW_RESIZABLE,
        VISIBLE = GLFW_VISIBLE,
        DECORATED = GLFW_DECORATED,
        FOCUSED = GLFW_FOCUSED,
        AUTO_ICONIFY = GLFW_AUTO_ICONIFY,
        FLOATING = GLFW_FLOATING,
        MAXIMIZED = GLFW_MAXIMIZED,
        CENTER_CURSOR = GLFW_CENTER_CURSOR,
        TRANSPARENT_FRAMEBUFFER = GLFW_TRANSPARENT_FRAMEBUFFER,
        FOCUS_ON_SHOW = GLFW_FOCUS_ON_SHOW,
        SCALE_TO_MONITOR = GLFW_SCALE_TO_MONITOR,
        SCALE_FRAMEBUFFER = GLFW_SCALE_FRAMEBUFFER,
        MOUSE_PASSTHROUGH = GLFW_MOUSE_PASSTHROUGH,
        POSITION_X = GLFW_POSITION_X,
        POSITION_Y = GLFW_POSITION_Y,
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
        CONTEXT_CREATION_API = GLFW_CONTEXT_CREATION_API,
        CONTEXT_VERSION_MAJOR = GLFW_CONTEXT_VERSION_MAJOR,
        CONTEXT_VERSION_MINOR = GLFW_CONTEXT_VERSION_MINOR,
        CONTEXT_ROBUSTNESS = GLFW_CONTEXT_ROBUSTNESS,
        CONTEXT_RELEASE_BEHAVIOR = GLFW_CONTEXT_RELEASE_BEHAVIOR,
        OPENGL_FORWARD_COMPAT = GLFW_OPENGL_FORWARD_COMPAT,
        OPENGL_DEBUG_CONTEXT = GLFW_OPENGL_DEBUG_CONTEXT,
        OPENGL_PROFILE = GLFW_OPENGL_PROFILE,

        WIN32_KEYBOARD_MENU = GLFW_WIN32_KEYBOARD_MENU,
        WIN32_SHOWDEFAULT = GLFW_WIN32_SHOWDEFAULT,
        COCOA_FRAME_NAME = GLFW_COCOA_FRAME_NAME,
        COCOA_GRAPHICS_SWITCHING = GLFW_COCOA_GRAPHICS_SWITCHING,
        WAYLAND_APP_ID = GLFW_WAYLAND_APP_ID,
        X11_CLASS_NAME = GLFW_X11_CLASS_NAME,
        X11_INSTANCE_NAME = GLFW_X11_INSTANCE_NAME,
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
}
