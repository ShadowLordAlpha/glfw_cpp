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

module glfw;

namespace glfw
{
    std::vector<Monitor> getMonitors()
    {
        int count;
        auto nMonitors = glfwGetMonitors(&count);

        std::vector<Monitor> monitors;
        monitors.reserve(count);
        for(int i = 0; i < count; ++i)
        {
            monitors.emplace_back(nMonitors[i]);
        }

        return monitors;
    }

    Monitor getPrimaryMonitor()
    {
        auto glfwMonitor = glfwGetPrimaryMonitor();
        return glfwMonitor;
    }

    MonitorFunction* setMonitorCallback(MonitorFunction* callback)
    {
        static MonitorFunction monitorCallback = *callback;
        if(callback == nullptr)
        {
            glfwSetMonitorCallback(nullptr);
        }
        else
        {
            glfwSetMonitorCallback([](GLFWmonitor* monitor, int event)
            {
                monitorCallback(monitor, static_cast<MonitorEvent>(event));
            });
        }
        return callback;
    }

    Monitor::Monitor() : Monitor(nullptr) {}

    Monitor::Monitor(GLFWmonitor* ptr) : ptr(ptr) {}

    Monitor::operator GLFWmonitor*() const
    {
        return get();
    }

    GLFWmonitor* Monitor::get() const
    {
        return ptr;
    }

    Position<int> Monitor::getPos() const
    {
        int x, y;
        glfwGetMonitorPos(ptr, &x, &y);
        return {x, y};
    }

    WorkArea Monitor::getWorkarea() const
    {
        int x, y, width, height;
        glfwGetMonitorWorkarea(ptr, &x, &y, &width, &height);
        return {x, y, width, height};
    }

    Size Monitor::getPhysicalSize() const
    {
        int width, height;
        glfwGetMonitorPhysicalSize(ptr, &width, &height);
        return {width, height};
    }

    Scale Monitor::getContentScale() const
    {
        float x, y;
        glfwGetMonitorContentScale(ptr, &x, &y);
        return {x, y};
    }

    const std::string& Monitor::getName() const
    {
        return glfwGetMonitorName(ptr);
    }

    void Monitor::setUserPointer(void* pointer) const
    {
        glfwSetMonitorUserPointer(ptr, pointer);
    }

    void* Monitor::getUserPointer() const
    {
        return glfwGetMonitorUserPointer(ptr);
    }

    std::vector<VideoMode> Monitor::getVideoModes() const
    {
        int count;
        const GLFWvidmode* nModes = glfwGetVideoModes(ptr, &count);

        std::vector modes(nModes, nModes + count);
        return modes;
    }

    const VideoMode* Monitor::getVideoMode() const
    {
        return glfwGetVideoMode(ptr);
    }

    void Monitor::setGamma(float gamma) const
    {
        glfwSetGamma(ptr, gamma);
    }

    const GammaRamp* Monitor::getGammaRamp() const
    {
        return glfwGetGammaRamp(ptr);
    }

    void Monitor::setGammaRamp(const GammaRamp* ramp) const
    {
        glfwSetGammaRamp(ptr, ramp);
    }
}
