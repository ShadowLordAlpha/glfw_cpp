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

#include <string>
#include <stdexcept>
#include <GLFW/glfw3.h>

module glfw;

namespace glfw
{
    void initHint(int hint, int value) // TODO: type and enums
    {
        glfwInitHint(hint, value);
    }

    void initAllocator(const Allocator *allocator)
    {
        glfwInitAllocator(allocator);
    }

    // inline void glfwInitVulkanLoader(PFN_vkGetInstanceProcAddr loader) // TODO

    constexpr Version getCompileTimeVersion()
    {
        return {GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION};
    }

    Version getVersion()
    {
        Version version{};
        glfwGetVersion(&version.major, &version.minor, &version.revision);
        return version;
    }

    const char* getVersionString()
    {
        return glfwGetVersionString();
    }

    const std::string getError()
    {
        const char* description;
        glfwGetError(&description);
        return description;
    }

    ErrorFun setErrorCallback(ErrorFun fun)
    {
        // We could do our own error function with asserts but we want to stay as close to the glfw interface as
        //  possible currently.
        return glfwSetErrorCallback(fun);
    }

    int getPlatform()
    {
        return glfwGetPlatform();
    }

    bool platformSupported(int platform) // TODO: type checked method
    {
        return glfwPlatformSupported(platform) == GLFW_TRUE;
    }

    void pollEvents()
    {
        glfwPollEvents();
    }

    void waitEvents()
    {
        glfwWaitEvents();
    }

    void waitEventsTimeout(double timeout)
    {
        glfwWaitEventsTimeout(timeout);
    }

    void postEmptyEvent()
    {
        glfwPostEmptyEvent();
    }

    bool rawMouseMotionSupport()
    {
        return glfwRawMouseMotionSupported();
    }

    const char* getKeyName(int key, int scancode) // TODO: type checked method
    {
        return glfwGetKeyName(key, scancode);
    }

    int getKeyScancode(int key) // TODO: type checked method?
    {
        return glfwGetKeyScancode(key);
    }

    double getTime()
    {
        return glfwGetTime();
    }

    void setTime(double time)
    {
        glfwSetTime(time);
    }

    uint64_t getTimerValue()
    {
        return glfwGetTimerValue();
    }

    uint64_t getTimerFrequency()
    {
        return glfwGetTimerFrequency();
    }

    void swapInterval(int interval)
    {
        glfwSwapInterval(interval);
    }

    [[nodiscard]] inline bool extensionSupported(const char* extension);

    glProc getProcAddress(const char* procname)
    {
        return glfwGetProcAddress(procname);
    }

    bool vulkanSupported()
    {
        return glfwVulkanSupported();
    }

    const char** getRequiredInstanceExtensions(uint32_t* count)
    {
        return glfwGetRequiredInstanceExtensions(count);
    }

    // inline GLFWvkproc getInstanceProcAddress (VkInstance instance, const char *procname); // TODO:
    // bool getPhysicalDevicePresentationSupport(VkInstance instance, VkPhysicalDevice device, uint32_t queuefamily);
    // VkResult createWindowSurface(VkInstance instance, GLFWwindow *window, const VkAllocationCallbacks *allocator, VkSurfaceKHR *surface); // TODO: should this be part of Window instead?

    Library::Library()
    {
        if(!glfwInit())
        {
            throw std::runtime_error(getError());
        }
    }

    Library::~Library()
    {
        glfwTerminate();
    }
}
