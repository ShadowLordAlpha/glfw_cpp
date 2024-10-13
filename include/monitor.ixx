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

#include <vector>
#include <glfw/glfw3.h>

export module glfw:monitor;

import :type;

export namespace glfw
{
    class Monitor;

    [[nodiscard]] std::vector<Monitor> getMonitors();
    [[nodiscard]] Monitor getPrimaryMonitor();
    MonitorFunction setMonitorCallback(MonitorFunction callback = nullptr); // TODO: properly figure this out...

    class Monitor
    {
    public:
        Monitor();
        Monitor(GLFWmonitor* monitor); // NOLINT(*-explicit-constructor)

        operator GLFWmonitor*() const; // NOLINT(*-explicit-constructor)
        operator bool() const; // NOLINT(*-explicit-constructor)

        [[nodiscard]] Position<int> getPos() const;
        [[nodiscard]] WorkArea getWorkarea() const;
        [[nodiscard]] Size getPhysicalSize() const;
        [[nodiscard]] Scale getContentScale() const;
        [[nodiscard]] const char* getName() const;
        void setUserPointer(void* pointer);
        [[nodiscard]] void* getUserPointer() const;
        [[nodiscard]] std::vector<VideoMode> getVideoModes();
        [[nodiscard]] VideoMode getVideoMode() const;
        void setGamma(float gamma);
        [[nodiscard]] GammaRamp getGammaRamp() const;
        void setGammaRamp(GammaRamp ramp);

    private:
        GLFWmonitor* ptr;
    };
}
