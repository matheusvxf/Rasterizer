#ifdef _WIN32
  #include <windows.h>
#endif

#include <iostream>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include "Color.h"
#include "Cube.h"
#include "Ball.h"
#include "House.h"
#include "Dragon.h"
#include "Bunny.h"
#include "Keyboard.h"
#include "ViewPortMatrix.h"
#include "ProjectionMatrix.h"
#include "Rasterizer.h"
#include "Matrix4.h"
#include "Light.h"
#include "main.h"
#include "Utility.h"

static int window_width = 512, window_height = 512;
static float* pixels = new float[window_width * window_height * 3];
static float* z_buffer = new float[window_width * window_height];
static ViewPortMatrix D(window_width, window_height);
static Camera C;
static Color color(1, 1, 1);
static double FOV = 1.0;
static double rasterize_near = 1.0;
static double rasterize_far = 1000.0;
static ProjectionMatrix P(60.0, window_width / window_height, rasterize_near, rasterize_far);
static UINT32 n_transf = 0;
static Matrix4* transf_array = new Matrix4[32];
static UINT32 n_light_sources = 0;
static Light* light_sources = new Light[8];
static ShadeType shade_type = tShadeType::diffuse | tShadeType::ambient;
static Vector4 normal(0, 0, 0, 0);
static double z_min, z_max;
static double* point = (double*)malloc(sizeof(double) * 200000 * 12);
static UINT32 n_points = 0;

static Color calc_shading(const Vector4& p, const Color& color, const Vector4 normal);
static void reshapeCallback(int window_width, int window_height);
static void displayCallback();
static Vector4 modelView(const Vector4& p);
static void drawPoint(int x, int y, const Color& c, double z, const Vector4& n, const Vector4& p);
static UINT32 point_size(double z);

namespace Globals
{
    Cube cube;
    Ball ball;
    House house;
    Bunny bunny;
    Dragon dragon;
    Object* curr_obj = &bunny;
    World world;
    Camera camera;
    bool shading_flag = false;
    bool z_buffer_flag = false;
    bool point_size_flag = false;
    bool circuler_point_flag = false;
    bool point_fake_diffuse_light_flag = false;
};


using namespace std;

void API_setCamera(const Camera& camera)
{
    C = camera;
}

void API_Normal(double x, double y, double z)
{
    normal[0] = x;
    normal[1] = y;
    normal[2] = z;
    normal[3] = 0;
}

void API_setColor(const Color& c)
{
    color = c;
}

void API_setProjectionMatrix(double p_FOV, double p_near, double p_far)
{
    FOV = p_FOV;
    rasterize_near = p_near;
    rasterize_far = p_far;
    reshapeCallback(window_width, window_height);
}

void API_setProjectionMatrix(double p_FOV)
{
    FOV = p_FOV;
    P.setProjectionMatrix(FOV, (float)window_width / (float)window_height, rasterize_near, rasterize_far);
}

void API_drawPoint(GLdouble x, GLdouble y, GLdouble z)
{
    Vector4 p(x, y, z, 1.0);
    Vector4 n;
    Color shading_color = color;

    p = modelView(p);
    n = modelView(normal);

    if (Globals::shading_flag)
        shading_color = calc_shading(p, color, n);

    p = C.getMatrix() * p;

    point[n_points + 9] = p[0];
    point[n_points + 10] = p[1];
    point[n_points + 11] = p[2];

    n = C.getMatrix() * n;
    n.normalize();
    p = P * p;
    p.dehomogenize();
    p = D * p;
    x = p[0];
    y = p[1];
    z = p[2];

    point[n_points] = p[0];
    point[n_points + 1] = p[1];
    point[n_points + 2] = p[2];
    point[n_points + 3] = shading_color.r;
    point[n_points + 4] = shading_color.g;
    point[n_points + 5] = shading_color.b;
    point[n_points + 6] = n[0];
    point[n_points + 7] = n[1];
    point[n_points + 8] = n[2];

    n_points += 12;
    z_min = min(z_min, z);
    z_max = max(z_max, z);
}

// Draw a point into the frame buffer
void drawPoint(int x, int y, const Color& c, double z, const Vector4& n, const Vector4& p)
{
    UINT32 offset = y*window_width * 3 + x * 3;
    UINT32 z_offset;
    INT32 p_size = 1;
    INT32 radius = 0;
    Color m_color;

    Vector4 center, p_prime, norm;
    double theta, phi;

    double angle;
    Vector4 sphere_normal;
    Matrix4 rot;
    bool flag = true;
    UINT32 count = 0;

    center = p - n;

    if (Globals::point_size_flag)
    {
        p_size = point_size(z);
        radius = p_size / 2;
    }

    for (INT32 line = y - radius; line <= y + radius; ++line)
    {
        for (INT32 column = x - radius; column <= x + radius; ++column)
        {
            flag = true;
            m_color = c;
            if (Globals::circuler_point_flag)
            {
                if ((line - y) * (line - y) + (column - x) * (column - x) > radius * radius)
                {
                    flag = false;
                }
            }
            if (flag && 0 <= line && line < window_height && 0 <= column && column < window_width)
            {
                if (Globals::point_fake_diffuse_light_flag)
                {
                    theta = 90.0 - 90.0 / (double)radius * (column - x);
                    phi = 90.0 - 90.0 / (double)radius * (line - y);
                    theta = degree2rad(theta);
                    phi = degree2rad(phi);
                    p_prime[0] = radius * sin(phi) * cos(theta);
                    p_prime[1] = radius * sin(phi) * sin(theta);
                    p_prime[2] = radius * cos(theta);
                    p_prime[3] = 1;
                    norm = p_prime - center;
                    norm.normalize();
                    m_color = calc_shading(p_prime, c, norm);

                }
                offset = line * window_width * 3 + column * 3;
                if (Globals::z_buffer_flag)
                {
                    z_offset = line * window_width + column;
                    if (z < z_buffer[z_offset])
                    {
                        count++;
                        z_buffer[z_offset] = z;
                        pixels[offset] = m_color.r;
                        pixels[offset + 1] = m_color.g;
                        pixels[offset + 2] = m_color.b;
                    }
                }
                else
                {
                    pixels[offset] = m_color.r;
                    pixels[offset + 1] = m_color.g;
                    pixels[offset + 2] = m_color.b;
                }
            }
        }
    }
    count++;
}

UINT32 point_size(double z)
{
    return (z_max - z) / (z_max - z_min) * 16 + 4;
}

void API_loadIdentity()
{
    n_transf = 0; 
}

void API_multMatrix(const Matrix4& m)
{
    transf_array[n_transf] = m;
    n_transf++;
}

void API_addLightSource(const Light& l)
{
    light_sources[n_light_sources] = l;
    n_light_sources++;
}

Color calc_shading(const Vector4& d, const Color& kd, const Vector4 n)
{
    Color cd;
    Color c;
    Vector4 L;

    if (shade_type & tShadeType::diffuse)
    {
        for (UINT8 i = 0; i < n_light_sources; ++i)
        {
            cd = light_sources[i].getColor();
            L = d - light_sources[i].getPosition();
            L.normalize();
            c += cd * kd * (L.dot(n));
        }
    }
    return c;
}

Vector4 modelView(const Vector4& p)
{
    Vector4 r = p;

    for (INT32 i = n_transf - 1; i >= 0; --i)
    {   
        r = transf_array[i] * r;
    }
    return r;
}

// Clear frame buffer
void clearBuffer()
{
    Color clearColor(0.0, 0.0, 0.0);   // clear color: black
    z_min = 2;
    z_max = -2;
    n_points = 0;
    for (int i=0; i<window_width*window_height; ++i)
    {
        pixels[i*3]   = clearColor.r;
        pixels[i*3+1] = clearColor.g;
        pixels[i*3+2] = clearColor.b;
        z_buffer[i] = 1.0;
    }  
}

void rasterize()
{
    Color c;
    Vector4 n;
    Vector4 look_at(0, 0, 1, 0);
    Vector4 p(0, 0, 0, 1);
    INT32 x, y;
    double z;
    // Put your main rasterization loop here
    // It should go over the point model and call drawPoint for every point in it
    Globals::curr_obj->render();

    for (UINT32 i = 0; i < n_points; i += 12)
    {
        x = point[i];
        y = point[i + 1];
        z = point[i + 2];
        c.r = point[i + 3];
        c.g = point[i + 4];
        c.b = point[i + 5];
        n[0] = point[i + 6];
        n[1] = point[i + 7];
        n[2] = point[i + 8];
        p[0] = point[i + 9];
        p[1] = point[i + 10];
        p[2] = point[i + 11];

        if (0 <= x && x < window_width && 0 <= y && y < window_height && n.dot(look_at) >= 0)
            drawPoint(x, y, c, point[i + 2], normal, p);
    }
}

// Called whenever the window size changes
void reshapeCallback(int new_width, int new_height)
{
    window_width  = new_width;
    window_height = new_height;
    delete[] pixels;
    delete[] z_buffer;
    pixels = new float[window_width * window_height * 3];
    z_buffer = new float[window_width * window_height];
    D.setViewPortMatrix(new_width, new_height);
    P.setProjectionMatrix(FOV, (float)new_width / (float)new_height, rasterize_near, rasterize_far);
}

void displayCallback()
{
    clearBuffer();
    rasterize();

    // glDrawPixels writes a block of pixels to the framebuffer
    glDrawPixels(window_width, window_height, GL_RGB, GL_FLOAT, pixels);

    glutSwapBuffers();
}

void loopCallback()
{
    Globals::curr_obj->update();
    displayCallback();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowSize(window_width, window_height);
  glutCreateWindow("Rasterizer");

  API_addLightSource(Light(1.0, 1.0, .0, 0.8, 0.4, 0.2));

  glutReshapeFunc(reshapeCallback);
  glutDisplayFunc(displayCallback);
  glutIdleFunc(loopCallback);
  glutKeyboardFunc(Keyboard::keyPressCb);
  glutSpecialFunc(Keyboard::specialFuncCb);
  glutMainLoop();
}
