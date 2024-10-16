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

#include <stdexcept>
#include <GLFW/glfw3.h>

module glfw;

namespace glfw
{
    JoystickFunction* setJoystickCallback(JoystickFunction* callback)
    {
        static JoystickFunction* joystickCallback = callback;
        if(callback)
        {
            glfwSetJoystickCallback([](int jid, int event)
            {
                joystickCallback(jid, event);
            });
            return callback;
        }

        glfwSetJoystickCallback(nullptr);
        return callback;
    }

    void updateGamepadMappings(const char* string)
    {
        auto success = glfwUpdateGamepadMappings(string);
        if(!success)
        {
            throw std::runtime_error(getError());
        }
    }

    Joystick::Joystick() : Joystick(-1) {}

    Joystick::Joystick(JoystickType jid) : Joystick(static_cast<int>(jid)) {}

    Joystick::Joystick(int jid) : jid(jid) {}

    Joystick::operator int() const
    {
        return get();
    }

    int Joystick::get() const
    {
        return jid;
    }

    bool Joystick::present() const
    {
        return glfwJoystickPresent(jid);
    }

    const float* Joystick::getAxes(int *count) const
    {
        return glfwGetJoystickAxes(jid, count);
    }

    const unsigned char* Joystick::getButtons(int *count)
    {
        return glfwGetJoystickButtons(jid, count);
    }

    const unsigned char* Joystick::getHats(int *count)
    {
        return glfwGetJoystickHats(jid, count);
    }

    const char* Joystick::getName()
    {
        return glfwGetJoystickName(jid);
    }

    const char* Joystick::getGUID()
    {
        return glfwGetJoystickGUID(jid);
    }

    void Joystick::setUserPointer(void* pointer)
    {
        glfwSetJoystickUserPointer(jid, pointer);
    }

    void* Joystick::getUserPointer() const
    {
        return glfwGetJoystickUserPointer(jid);
    }

    bool Joystick::isGamepad()
    {
        return glfwJoystickIsGamepad(jid);
    }

    const char* Joystick::getGamepadName()
    {
        return glfwGetGamepadName(jid);
    }

    GamepadState Joystick::getGamepadState()
    {
        GamepadState state;
        auto success = glfwGetGamepadState(jid, &state);
        if(!success)
        {
            throw std::runtime_error(getError());
        }
        return state;
    }
}
