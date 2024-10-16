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
#include <string>
#include <glfw/glfw3.h>

#include "../external/glfw/src/internal.h"

export module glfw:monitor;

import :type;

export namespace glfw
{
    class Monitor;

    [[nodiscard]] inline std::vector<Monitor> getMonitors();
    [[nodiscard]] inline Monitor getPrimaryMonitor();
    inline MonitorFunction* setMonitorCallback(MonitorFunction* callback = nullptr); // TODO: properly figure this out...

    class Monitor
    {
    public:
        Monitor();
        Monitor(GLFWmonitor* ptr); // NOLINT(*-explicit-constructor)

        operator GLFWmonitor*() const; // NOLINT(*-explicit-constructor)
        [[nodiscard]] GLFWmonitor* get() const;

        [[nodiscard]] Position<int> getPos() const;
        [[nodiscard]] WorkArea getWorkarea() const;
        [[nodiscard]] Size getPhysicalSize() const;
        [[nodiscard]] Scale getContentScale() const;
        [[nodiscard]] const std::string& getName() const;
        [[nodiscard]] std::vector<VideoMode> getVideoModes() const;
        [[nodiscard]] const VideoMode* getVideoMode() const;
        void setGamma(float gamma) const;
        [[nodiscard]] const GammaRamp* getGammaRamp() const;
        void setGammaRamp(const GammaRamp* ramp) const;
        void setUserPointer(void* pointer) const;
        [[nodiscard]] void* getUserPointer() const;

    private:
        GLFWmonitor* ptr;
    };
}
