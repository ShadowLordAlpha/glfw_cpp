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

#pragma once

namespace glfw
{
    inline bool validateHintBoolean(WindowHint hint)
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
            case WindowHint::MAXIMIZED:
            case WindowHint::CENTER_CURSOR:
            case WindowHint::TRANSPARENT_FRAMEBUFFER:
            case WindowHint::FOCUS_ON_SHOW:
            case WindowHint::SCALE_TO_MONITOR:
            case WindowHint::SCALE_FRAMEBUFFER:
            case WindowHint::MOUSE_PASSTHROUGH:
            case WindowHint::WIN32_SHOWDEFAULT:
            case WindowHint::WIN32_KEYBOARD_MENU:
            case WindowHint::COCOA_GRAPHICS_SWITCHING:
                return true;
            default:
                return false;
        }
    }

    bool validateHintString(WindowHint hint)
    {
        switch(hint)
        {
            default:
                return false;
        }
    }

    inline bool validateHintInt(WindowHint hint)
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
            case WindowHint::POSITION_X:
            case WindowHint::POSITION_Y:
                return true;
            default:
                return false;
        }
    }

    inline bool validateHintEnum(WindowHint hint)
    {
        return !validateHintBoolean(hint) && !validateHintString(hint); // literally everything but booleans are allowed
    }

    inline bool validateHintValue(WindowHint hint, int value)
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

            case WindowHint::POSITION_X:
            case WindowHint::POSITION_Y:
                return value == GLFW_ANY_POSITION || value >= 0 || value <= INT_MAX;

            case WindowHint::CONTEXT_CREATION_API:
                return value == GLFW_NATIVE_CONTEXT_API || value == GLFW_EGL_CONTEXT_API || value == GLFW_OSMESA_CONTEXT_API;

            case WindowHint::CLIENT_API:
                return value == GLFW_OPENGL_API || value == GLFW_OPENGL_ES_API || value == GLFW_NO_API;

            case WindowHint::CONTEXT_ROBUSTNESS:
                return value == GLFW_NO_ROBUSTNESS || value == GLFW_NO_RESET_NOTIFICATION || value == GLFW_LOSE_CONTEXT_ON_RESET;

            case WindowHint::CONTEXT_RELEASE_BEHAVIOR:
                return value == GLFW_ANY_RELEASE_BEHAVIOR || value == GLFW_RELEASE_BEHAVIOR_FLUSH || value == GLFW_RELEASE_BEHAVIOR_NONE;

            case WindowHint::OPENGL_PROFILE:
                return value == GLFW_OPENGL_ANY_PROFILE || value == GLFW_OPENGL_COMPAT_PROFILE || value == GLFW_OPENGL_CORE_PROFILE;

            default:
                return false;
        }
    }
}
