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
#include <GLFW/glfw3.h>

export module glfw:library;

import :type;

export namespace glfw
{

    inline void initHint(int hint, int value);
    inline void initAllocator(const Allocator *allocator);
    // inline void glfwInitVulkanLoader(PFN_vkGetInstanceProcAddr loader) // TODO
    [[nodiscard]] constexpr Version getCompileTimeVersion();
    [[nodiscard]] inline Version getVersion();
    [[nodiscard]] inline const char* getVersionString();
    [[nodiscard]] inline const std::string getError(); // TODO: check what returns when there is no error
    inline ErrorFun setErrorCallback(ErrorFun fun);
    inline int getPlatform();
    bool platformSupported(int platform); // TODO: type checked method
    inline void pollEvents();
    inline void waitEvents();
    inline void waitEventsTimeout(double timeout);
    inline void postEmptyEvent();
    inline bool rawMouseMotionSupport();
    inline const char* getKeyName(int key, int scancode); // TODO: type checked method
    inline int getKeyScancode(int key); // TODO: type checked method?
    [[nodiscard]] inline double getTime();
    inline void setTime(double time);
    [[nodiscard]] inline uint64_t getTimerValue();
    [[nodiscard]] inline uint64_t getTimerFrequency();
    inline void swapInterval(int interval);
    [[nodiscard]] inline bool extensionSupported(const char* extension);
    inline GLFWglproc getProcAddress(const char* procname);
    inline bool vulkanSupported();
    inline const char** getRequiredInstanceExtensions(uint32_t* count);
    // inline GLFWvkproc getInstanceProcAddress (VkInstance instance, const char *procname); // TODO:
    // bool getPhysicalDevicePresentationSupport(VkInstance instance, VkPhysicalDevice device, uint32_t queuefamily);
    // VkResult createWindowSurface(VkInstance instance, GLFWwindow *window, const VkAllocationCallbacks *allocator, VkSurfaceKHR *surface); // TODO: should this be part of Window instead?

    class Library
    {
    public:
        Library();
        ~Library();

        // Disable copy and assignment to ensure proper resource handling
        Library(const Library&) = delete;
        Library& operator=(const Library&) = delete;
    };
}
