/*****************************************************************************
 * Wave Simulation in OpenGL
 * (C) 2002 Jakob Thomsen
 * http://home.in.tum.de/~thomsen
 * Modified for GLFW by Sylvain Hellegouarch - sh@programmationworld.com
 * Modified for variable frame rate by Marcus Geelnard
 * 2003-Jan-31: Minor cleanups and speedups / MG
 * 2010-10-24: Formatting and cleanup - Camilla Löwy
 * 2024-10-13: Modified for GLFW_CPP - Josh "ShadowLordAlpha"
 *****************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <numbers>

#include <glad/gl.h>
#define GLFW_INCLUDE_NONE

#include <linmath.h>

import glfw;

// Maximum delta T to allow for differential calculations
#define MAX_DELTA_T 0.01

// Animation speed (10.0 looks good)
#define ANIMATION_SPEED 10.0

GLfloat alpha = 210.f, beta = -70.f;
GLfloat zoom = 2.f;

double cursorX;
double cursorY;

struct Vertex
{
    GLfloat x, y, z;
    GLfloat r, g, b;
};

#define GRIDW 50
#define GRIDH 50
#define VERTEXNUM (GRIDW*GRIDH)

#define QUADW (GRIDW - 1)
#define QUADH (GRIDH - 1)
#define QUADNUM (QUADW*QUADH)

GLuint quad[4 * QUADNUM];
struct Vertex vertex[VERTEXNUM];

/* The grid will look like this:
 *
 *      3   4   5
 *      *---*---*
 *      |   |   |
 *      | 0 | 1 |
 *      |   |   |
 *      *---*---*
 *      0   1   2
 */

//========================================================================
// Initialize grid geometry
//========================================================================

void init_vertices()
{
    int x, y, p;

    // Place the vertices in a grid
    for (y = 0;  y < GRIDH;  y++)
    {
        for (x = 0;  x < GRIDW;  x++)
        {
            p = y * GRIDW + x;

            vertex[p].x = (GLfloat) (x - GRIDW / 2) / (GLfloat) (GRIDW / 2);
            vertex[p].y = (GLfloat) (y - GRIDH / 2) / (GLfloat) (GRIDH / 2);
            vertex[p].z = 0;

            if ((x % 4 < 2) ^ (y % 4 < 2))
                vertex[p].r = 0.0;
            else
                vertex[p].r = 1.0;

            vertex[p].g = (GLfloat) y / (GLfloat) GRIDH;
            vertex[p].b = 1.f - ((GLfloat) x / (GLfloat) GRIDW + (GLfloat) y / (GLfloat) GRIDH) / 2.f;
        }
    }

    for (y = 0;  y < QUADH;  y++)
    {
        for (x = 0;  x < QUADW;  x++)
        {
            p = 4 * (y * QUADW + x);

            quad[p + 0] = y       * GRIDW + x;     // Some point
            quad[p + 1] = y       * GRIDW + x + 1; // Neighbor at the right side
            quad[p + 2] = (y + 1) * GRIDW + x + 1; // Upper right neighbor
            quad[p + 3] = (y + 1) * GRIDW + x;     // Upper neighbor
        }
    }
}

double dt;
double p[GRIDW][GRIDH];
double vx[GRIDW][GRIDH], vy[GRIDW][GRIDH];
double ax[GRIDW][GRIDH], ay[GRIDW][GRIDH];

//========================================================================
// Initialize grid
//========================================================================

void init_grid()
{
    int x, y;
    double dx, dy, d;

    for (y = 0; y < GRIDH;  y++)
    {
        for (x = 0; x < GRIDW;  x++)
        {
            dx = (double) (x - GRIDW / 2);
            dy = (double) (y - GRIDH / 2);
            d = sqrt(dx * dx + dy * dy);
            if (d < 0.1 * (double) (GRIDW / 2))
            {
                d = d * 10.0;
                p[x][y] = -cos(d * (std::numbers::pi / (double)(GRIDW * 4))) * 100.0;
            }
            else
                p[x][y] = 0.0;

            vx[x][y] = 0.0;
            vy[x][y] = 0.0;
        }
    }
}


//========================================================================
// Draw scene
//========================================================================

void draw_scene(glfw::Window& window)
{
    // Clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // We don't want to modify the projection matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Move back
    glTranslatef(0.0, 0.0, -zoom);
    // Rotate the view
    glRotatef(beta, 1.0, 0.0, 0.0);
    glRotatef(alpha, 0.0, 0.0, 1.0);

    glDrawElements(GL_QUADS, 4 * QUADNUM, GL_UNSIGNED_INT, quad);

    window.swapBuffers();
}


//========================================================================
// Initialize Miscellaneous OpenGL state
//========================================================================

void init_opengl()
{
    // Use Gouraud (smooth) shading
    glShadeModel(GL_SMOOTH);

    // Switch on the z-buffer
    glEnable(GL_DEPTH_TEST);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(struct Vertex), vertex);
    glColorPointer(3, GL_FLOAT, sizeof(struct Vertex), &vertex[0].r); // Pointer to the first color

    glPointSize(2.0);

    // Background color is black
    glClearColor(0, 0, 0, 0);
}


//========================================================================
// Modify the height of each vertex according to the pressure
//========================================================================

void adjust_grid()
{
    int pos;
    int x, y;

    for (y = 0; y < GRIDH;  y++)
    {
        for (x = 0;  x < GRIDW;  x++)
        {
            pos = y * GRIDW + x;
            vertex[pos].z = (float) (p[x][y] * (1.0 / 50.0));
        }
    }
}


//========================================================================
// Calculate wave propagation
//========================================================================

void calc_grid()
{
    int x, y, x2, y2;
    double time_step = dt * ANIMATION_SPEED;

    // Compute accelerations
    for (x = 0;  x < GRIDW;  x++)
    {
        x2 = (x + 1) % GRIDW;
        for(y = 0; y < GRIDH; y++)
            ax[x][y] = p[x][y] - p[x2][y];
    }

    for (y = 0;  y < GRIDH;  y++)
    {
        y2 = (y + 1) % GRIDH;
        for(x = 0; x < GRIDW; x++)
            ay[x][y] = p[x][y] - p[x][y2];
    }

    // Compute speeds
    for (x = 0;  x < GRIDW;  x++)
    {
        for (y = 0;  y < GRIDH;  y++)
        {
            vx[x][y] = vx[x][y] + ax[x][y] * time_step;
            vy[x][y] = vy[x][y] + ay[x][y] * time_step;
        }
    }

    // Compute pressure
    for (x = 1;  x < GRIDW;  x++)
    {
        x2 = x - 1;
        for (y = 1;  y < GRIDH;  y++)
        {
            y2 = y - 1;
            p[x][y] = p[x][y] + (vx[x2][y] - vx[x][y] + vy[x][y2] - vy[x][y]) * time_step;
        }
    }
}


//========================================================================
// Print errors
//========================================================================

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}


//========================================================================
// Handle key strokes
//========================================================================

void key_callback(glfw::Window& window, glfw::Key key, int scancode, glfw::KeyAction action, int mods)
{
    if (action != glfw::KeyAction::PRESS)
        return;

    switch (key)
    {
        case glfw::Key::ESCAPE:
            window.setShouldClose(true);
            break;
        case glfw::Key::SPACE:
            init_grid();
            break;
        case glfw::Key::LEFT:
            alpha += 5;
            break;
        case glfw::Key::RIGHT:
            alpha -= 5;
            break;
        case glfw::Key::UP:
            beta -= 5;
            break;
        case glfw::Key::DOWN:
            beta += 5;
            break;
        case glfw::Key::PAGE_UP:
            zoom -= 0.25f;
            if (zoom < 0.f)
                zoom = 0.f;
            break;
        case glfw::Key::PAGE_DOWN:
            zoom += 0.25f;
            break;
        default:
            break;
    }
}


//========================================================================
// Callback function for mouse button events
//========================================================================

void mouse_button_callback(glfw::Window& window, glfw::MouseButton button, glfw::KeyAction action, int mods)
{
    if (button != glfw::MouseButton::LEFT)
        return;

    if (action == glfw::KeyAction::PRESS)
    {
        window.setInputMode(glfw::InputMode::CURSOR, glfw::InputValue::CURSOR_DISABLED);
        auto [x, y] = window.getCursorPos();
        cursorX = x;
        cursorY = y;
    }
    else
        window.setInputMode(glfw::InputMode::CURSOR, glfw::InputValue::CURSOR_NORMAL);
}


//========================================================================
// Callback function for cursor motion events
//========================================================================

void cursor_position_callback(glfw::Window& window, glfw::Position<double> pos)
{
    if (window.getInputMode(glfw::InputMode::CURSOR) == static_cast<int>(glfw::InputValue::CURSOR_DISABLED))
    {
        alpha += (GLfloat) (pos.x - cursorX) / 10.f;
        beta += (GLfloat) (pos.y - cursorY) / 10.f;

        cursorX = pos.x;
        cursorY = pos.y;
    }
}


//========================================================================
// Callback function for scroll events
//========================================================================

void scroll_callback(glfw::Window& window, glfw::Position<double> pos)
{
    zoom += (float) pos.y / 4.f;
    if (zoom < 0)
        zoom = 0;
}


//========================================================================
// Callback function for framebuffer resize events
//========================================================================

void framebuffer_size_callback(glfw::Window& window, glfw::Size size)
{
    float ratio = 1.f;
    mat4x4 projection;

    if (size.height > 0)
        ratio = static_cast<float>(size.width) / static_cast<float>(size.height);

    // Setup viewport
    glViewport(0, 0, size.width, size.height);

    // Change to the projection matrix and set our viewing volume
    glMatrixMode(GL_PROJECTION);
    mat4x4_perspective(projection,
                       60.f * static_cast<float>(std::numbers::pi) / 180.f,
                       ratio,
                       1.f, 1024.f);
    glLoadMatrixf((const GLfloat*) projection);
}


//========================================================================
// main
//========================================================================

int main()
{
    glfw::Window window;
    double t, dt_total, t_old;

    glfw::setErrorCallback(error_callback);

    glfw::Library library;

    window = {640, 480, "Wave Simulation"};

    window.setKeyCallback(key_callback);
    window.setFramebufferSizeCallback(framebuffer_size_callback);
    window.setMouseButtonCallback(mouse_button_callback);
    window.setCursorPosCallback(cursor_position_callback);
    window.setScrollCallback(scroll_callback);

    window.makeContextCurrent();
    gladLoadGL(glfw::getProcAddress);
    glfw::swapInterval(1);

    auto [width, height] = window.getFramebufferSize();
    framebuffer_size_callback(window, {width, height});

    // Initialize OpenGL
    init_opengl();

    // Initialize simulation
    init_vertices();
    init_grid();
    adjust_grid();

    // Initialize timer
    t_old = glfw::getTime() - 0.01;

    while (!window.shouldClose())
    {
        t = glfw::getTime();
        dt_total = t - t_old;
        t_old = t;

        // Safety - iterate if dt_total is too large
        while (dt_total > 0.f)
        {
            // Select iteration time step
            dt = dt_total > MAX_DELTA_T ? MAX_DELTA_T : dt_total;
            dt_total -= dt;

            // Calculate wave propagation
            calc_grid();
        }

        // Compute height of each vertex
        adjust_grid();

        // Draw wave grid to OpenGL display
        draw_scene(window);

        glfw::pollEvents();
    }

    return EXIT_SUCCESS;
}
