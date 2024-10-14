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

#include "GLFW/glfw3.h"

export module glfw:joystick;

export namespace glfw
{
    class Joystick;

    using GamepadState = GLFWgamepadstate;
    using JoystickFunction = GLFWjoystickfun;
    // typedef void (* JoystickFunction)(Joystick jid, int event);

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

    JoystickFunction setJoystickCallback(JoystickFunction callback = nullptr);
    inline void updateGamepadMappings(const char* string);

    class Joystick
    {
    public:
        Joystick();
        Joystick(JoystickType jid); // NOLINT(*-explicit-constructor)
        Joystick(int jid); // NOLINT(*-explicit-constructor)

        operator int() const; // NOLINT(*-explicit-constructor)
        operator bool() const; // NOLINT(*-explicit-constructor)

        [[nodiscard]] bool present() const;
        const float* getAxes(int *count) const; // TODO: sub object again?
        const unsigned char* getButtons(int *count); // TODO: convert to vector
        const unsigned char* getHats(int *count); // TODO: convert to vector
        const char* getName();
        const char* getGUID();
        void setUserPointer(void* pointer);
        [[nodiscard]] void* getUserPointer() const;
        bool isGamepad();
        const char* getGamepadName();
        GamepadState getGamepadState();

    private:
        int jid;
    };
}
