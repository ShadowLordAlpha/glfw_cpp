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

#include <memory>
#include <stdexcept>
#include <GLFW\glfw3.h>

module glfw;

namespace glfw
{
    void DeleterCursor::operator()(GLFWcursor* ptr)
    {
        glfwDestroyCursor(ptr);
    }

    GLFWcursor* createStandardCursor(int shape)
    {
        auto cursor = glfwCreateStandardCursor(shape);
        if(!cursor)
        {
            throw std::runtime_error(getError());
        }
        return cursor;
    }

    GLFWcursor* createCursor(const Image& image, Position<int> posHot)
    {
        auto cursor = glfwCreateCursor(&image, posHot.x, posHot.y);
        if(!cursor)
        {
            throw std::runtime_error(getError());
        }
        return cursor;
    }

    Cursor::Cursor() : Cursor(nullptr) {}

    Cursor::Cursor(CursorShape shape) : Cursor(static_cast<int>(shape)) {}

    Cursor::Cursor(int shape) : ptr(createStandardCursor(shape)) {}

    Cursor::Cursor(const Image& image, Position<int> posHot) : ptr(createCursor(image, posHot)) {}

    Cursor::Cursor(GLFWcursor* cursor) : ptr(cursor) {}

    Cursor::operator GLFWcursor*() const
    {
        return ptr.get();
    }

    Cursor::operator bool() const
    {
        return ptr != nullptr;
    }
}
