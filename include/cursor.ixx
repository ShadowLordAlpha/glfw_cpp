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
#include <GLFW\glfw3.h>

export module glfw:cursor;

import :type;

namespace glfw
{
    struct DeleterCursor
    {
        void operator()(GLFWcursor* ptr);
    };
}

export namespace glfw
{
    class Cursor
    {
    public:
        Cursor();
        explicit Cursor(CursorShape shape); // Type checked/convince overload
        explicit Cursor(int shape);
        explicit Cursor(const Image& image, Position<int> posHot = {0, 0});
        explicit Cursor(GLFWcursor* cursor);

        operator GLFWcursor*() const; // NOLINT(*-explicit-constructor)
        operator bool() const; // NOLINT(*-explicit-constructor)

    private:
        std::unique_ptr<GLFWcursor, DeleterCursor> ptr;
    };
}
