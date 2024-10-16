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

export module glfw:joystick;

import :type;

export namespace glfw
{
    JoystickFunction* setJoystickCallback(JoystickFunction* callback = nullptr);
    inline void updateGamepadMappings(const char* string);

    class Joystick
    {
    public:
        Joystick();
        Joystick(JoystickType jid); // NOLINT(*-explicit-constructor)
        Joystick(int jid); // NOLINT(*-explicit-constructor)

        operator int() const;
        [[nodiscard]] int get() const;

        [[nodiscard]] bool present() const;
        const float* getAxes(int *count) const; // TODO: sub object again?
        const unsigned char* getButtons(int *count); // TODO: convert to vector
        const unsigned char* getHats(int *count); // TODO: convert to vector
        const char* getName();
        const char* getGUID();
        bool isGamepad();
        const char* getGamepadName();
        GamepadState getGamepadState();
        void setUserPointer(void* pointer);
        [[nodiscard]] void* getUserPointer() const;

    private:
        int jid;
    };
}
