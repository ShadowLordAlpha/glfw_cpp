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

#include <functional>
#include <GLFW/glfw3.h>

export module glfw:type;

export namespace glfw
{
    class Window;
    class Joystick;
    class Monitor;

    enum class ConnectionEvent
    {
        CONNECTED = GLFW_CONNECTED,
        DISCONNECTED = GLFW_DISCONNECTED,
    };

    enum class MouseButton
    {
        _1 = GLFW_MOUSE_BUTTON_1,
        _2 = GLFW_MOUSE_BUTTON_2,
        _3 = GLFW_MOUSE_BUTTON_3,
        _4 = GLFW_MOUSE_BUTTON_4,
        _5 = GLFW_MOUSE_BUTTON_5,
        _6 = GLFW_MOUSE_BUTTON_6,
        _7 = GLFW_MOUSE_BUTTON_7,
        _8 = GLFW_MOUSE_BUTTON_8,

        LEFT = GLFW_MOUSE_BUTTON_LEFT,
        RIGHT = GLFW_MOUSE_BUTTON_RIGHT,
        MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE,
        LAST = GLFW_MOUSE_BUTTON_LAST,
    };

    enum class Key
    {
        /* The unknown Key */
        UNKNOWN = GLFW_KEY_UNKNOWN,

        /* Printable Keys */
        SPACE = GLFW_KEY_SPACE,
        APOSTROPHE = GLFW_KEY_APOSTROPHE, /* ' */
        COMMA = GLFW_KEY_COMMA, /* , */
        MINUS = GLFW_KEY_MINUS, /* - */
        PERIOD = GLFW_KEY_PERIOD, /* . */
        SLASH = GLFW_KEY_SLASH, /* / */
        SEMICOLON = GLFW_KEY_SEMICOLON, /* ; */
        EQUAL = GLFW_KEY_EQUAL, /* = */
        LEFT_BRACKET = GLFW_KEY_LEFT_BRACKET, /* [ */
        BACKSLASH = GLFW_KEY_BACKSLASH, /* \ */
        RIGHT_BRACKET = GLFW_KEY_RIGHT_BRACKET, /* ] */
        GRAVE_ACCENT = GLFW_KEY_GRAVE_ACCENT, /* ` */
        WORLD_1 = GLFW_KEY_WORLD_1, /* non-US #1 */
        WORLD_2 = GLFW_KEY_WORLD_2, /* non-US #2 */

        _0 = GLFW_KEY_0,
        _1 = GLFW_KEY_1,
        _2 = GLFW_KEY_2,
        _3 = GLFW_KEY_3,
        _4 = GLFW_KEY_4,
        _5 = GLFW_KEY_5,
        _6 = GLFW_KEY_6,
        _7 = GLFW_KEY_7,
        _8 = GLFW_KEY_8,
        _9 = GLFW_KEY_9,

        KP_0 = GLFW_KEY_KP_0,
        KP_1 = GLFW_KEY_KP_1,
        KP_2 = GLFW_KEY_KP_2,
        KP_3 = GLFW_KEY_KP_3,
        KP_4 = GLFW_KEY_KP_4,
        KP_5 = GLFW_KEY_KP_5,
        KP_6 = GLFW_KEY_KP_6,
        KP_7 = GLFW_KEY_KP_7,
        KP_8 = GLFW_KEY_KP_8,
        KP_9 = GLFW_KEY_KP_9,
        KP_DECIMAL = GLFW_KEY_KP_DECIMAL,
        KP_DIVIDE = GLFW_KEY_KP_DIVIDE,
        KP_MULTIPLY = GLFW_KEY_KP_MULTIPLY,
        KP_SUBTRACT = GLFW_KEY_KP_SUBTRACT,
        KP_ADD = GLFW_KEY_KP_ADD,
        KP_ENTER = GLFW_KEY_KP_ENTER,
        KP_EQUAL = GLFW_KEY_KP_EQUAL,

        A = GLFW_KEY_A,
        B = GLFW_KEY_B,
        C = GLFW_KEY_C,
        D = GLFW_KEY_D,
        E = GLFW_KEY_E,
        F = GLFW_KEY_F,
        G = GLFW_KEY_G,
        H = GLFW_KEY_H,
        I = GLFW_KEY_I,
        J = GLFW_KEY_J,
        K = GLFW_KEY_K,
        L = GLFW_KEY_L,
        M = GLFW_KEY_M,
        N = GLFW_KEY_N,
        O = GLFW_KEY_O,
        P = GLFW_KEY_P,
        Q = GLFW_KEY_Q,
        R = GLFW_KEY_R,
        S = GLFW_KEY_S,
        T = GLFW_KEY_T,
        U = GLFW_KEY_U,
        V = GLFW_KEY_V,
        W = GLFW_KEY_W,
        X = GLFW_KEY_X,
        Y = GLFW_KEY_Y,
        Z = GLFW_KEY_Z,


        /* Function Keys */
        ESCAPE = GLFW_KEY_ESCAPE,
        ENTER = GLFW_KEY_ENTER,
        TAB = GLFW_KEY_TAB,
        BACKSPACE = GLFW_KEY_BACKSPACE,
        INSERT = GLFW_KEY_INSERT,
        DELETE = GLFW_KEY_DELETE,
        RIGHT = GLFW_KEY_RIGHT,
        LEFT = GLFW_KEY_LEFT,
        DOWN = GLFW_KEY_DOWN,
        UP = GLFW_KEY_UP,
        PAGE_UP = GLFW_KEY_PAGE_UP,
        PAGE_DOWN = GLFW_KEY_PAGE_DOWN,
        HOME = GLFW_KEY_HOME,
        END = GLFW_KEY_END,
        CAPS_LOCK = GLFW_KEY_CAPS_LOCK,
        SCROLL_LOCK = GLFW_KEY_SCROLL_LOCK,
        NUM_LOCK = GLFW_KEY_NUM_LOCK,
        PRINT_SCREEN = GLFW_KEY_PRINT_SCREEN,
        PAUSE = GLFW_KEY_PAUSE,
        F1 = GLFW_KEY_F1,
        F2 = GLFW_KEY_F2,
        F3 = GLFW_KEY_F3,
        F4 = GLFW_KEY_F4,
        F5 = GLFW_KEY_F5,
        F6 = GLFW_KEY_F6,
        F7 = GLFW_KEY_F7,
        F8 = GLFW_KEY_F8,
        F9 = GLFW_KEY_F9,
        F10 = GLFW_KEY_F10,
        F11 = GLFW_KEY_F11,
        F12 = GLFW_KEY_F12,
        F13 = GLFW_KEY_F13,
        F14 = GLFW_KEY_F14,
        F15 = GLFW_KEY_F15,
        F16 = GLFW_KEY_F16,
        F17 = GLFW_KEY_F17,
        F18 = GLFW_KEY_F18,
        F19 = GLFW_KEY_F19,
        F20 = GLFW_KEY_F20,
        F21 = GLFW_KEY_F21,
        F22 = GLFW_KEY_F22,
        F23 = GLFW_KEY_F23,
        F24 = GLFW_KEY_F24,
        F25 = GLFW_KEY_F25,

        LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
        LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL,
        LEFT_ALT = GLFW_KEY_LEFT_ALT,
        LEFT_SUPER = GLFW_KEY_LEFT_SUPER,
        RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,
        RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL,
        RIGHT_ALT = GLFW_KEY_RIGHT_ALT,
        RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER,
        MENU = GLFW_KEY_MENU,

        LAST = GLFW_KEY_LAST
    };

    using Allocator = GLFWallocator;
    using GamepadState = GLFWgamepadstate;
    using JoystickFunction = std::function<void(Joystick, ConnectionEvent)>;;


    enum class KeyAction
    {
        RELEASE = GLFW_RELEASE,
        PRESS = GLFW_PRESS,
        REPEAT = GLFW_REPEAT,
    };

    // TODO: test if we can use our value instead
    using MonitorFunction = std::function<void(Monitor, ConnectionEvent)>;

    // Redefine structs to be within our namespace
    using ErrorFun = GLFWerrorfun;
    using glProc = GLFWglproc;
    using Image = GLFWimage;
    using VideoMode = GLFWvidmode;
    using GammaRamp = GLFWgammaramp;

    template<typename type>
    struct Position
    {
        type x, y;
    };

    struct Size
    {
        int width, height;
    };

    struct Scale
            // This "could" be a Position<float> but that would kinda break type checking and the two are not the same
    {
        float x, y;
    };

    using WindowPosFunction = std::function<void(Window &window, Position<int> pos)>;
    using WindowSizeFunction = std::function<void(Window &window, Size size)>;
    using WindowCloseFunction = std::function<void(Window &window)>;
    using WindowRefreshFunction = std::function<void(Window &window)>;
    using WindowFocusFunction = std::function<void(Window &window, bool focused)>;
    using WindowIconifyFunction = std::function<void(Window &window, bool iconified)>;
    using WindowMaximizeFunction = std::function<void(Window &window, bool maximized)>;
    using FrameBufferSizeFunction = std::function<void(Window &window, Size size)>;
    using WindowContentScaleFunction = std::function<void(Window &window, Scale scale)>;

    using KeyFunction = std::function<void(Window &window, Key key, int scancode, KeyAction action, int mods)>;
    using CharFunction = std::function<void(Window &window, unsigned int codepoint)>;
    using CharModsFunction = std::function<void(Window &window, unsigned int codepoint, int mods)>;
    using MouseButtonFunction = std::function<void(Window &window, MouseButton button, KeyAction action, int mods)>;
    using CursorPosFunction = std::function<void(Window &window, Position<double> pos)>;
    using CursorEnterFunction = std::function<void(Window &window, bool entered)>;
    using ScrollFunction = std::function<void(Window &window, Position<double> offset)>;
    using DropFunction = std::function<void(Window &window, int path_count, const char *paths[])>;

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

    struct FrameSize
    {
        int left, top, right, bottom;
    };


    enum JoystickType
    {
        JOYSTICK_1 = GLFW_JOYSTICK_1,
        JOYSTICK_2 = GLFW_JOYSTICK_2,
        JOYSTICK_3 = GLFW_JOYSTICK_3,
        JOYSTICK_4 = GLFW_JOYSTICK_4,
        JOYSTICK_5 = GLFW_JOYSTICK_5,
        JOYSTICK_6 = GLFW_JOYSTICK_6,
        JOYSTICK_7 = GLFW_JOYSTICK_7,
        JOYSTICK_8 = GLFW_JOYSTICK_8,
        JOYSTICK_9 = GLFW_JOYSTICK_9,
        JOYSTICK_10 = GLFW_JOYSTICK_10,
        JOYSTICK_11 = GLFW_JOYSTICK_11,
        JOYSTICK_12 = GLFW_JOYSTICK_12,
        JOYSTICK_13 = GLFW_JOYSTICK_13,
        JOYSTICK_14 = GLFW_JOYSTICK_14,
        JOYSTICK_15 = GLFW_JOYSTICK_15,
        JOYSTICK_16 = GLFW_JOYSTICK_16,
    };

    enum class InputValue
    {
        CURSOR_NORMAL = GLFW_CURSOR_NORMAL,
        CURSOR_HIDDEN = GLFW_CURSOR_HIDDEN,
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
