#include "PointImageObject.h"
#include "Config.h"
#include "Utility.h"
#include "main.h"
#include "Rasterizer.h"

#include <algorithm>
#include <iostream>
#include <fstream>

static UINT32 count_lines(const char *f_name);

PointImageObject::PointImageObject()
{
    reset();
}

PointImageObject::PointImageObject(std::string file)
{
    n_points = count_lines(file.c_str());
    load_file(file.c_str());
    reset();
}

PointImageObject::~PointImageObject()
{
    free(vertices);
    free(normals);
}

UINT32 count_lines(const char *f_name)
{
    FILE* fs;
    UINT32 lines;
    GLdouble tmp;
    lines = 0;

    if (fopen_s(&fs, f_name, "r") == 0)
        while (fscanf_s(fs, "%lf %lf %lf %lf %lf %lf", &tmp, &tmp, &tmp, &tmp, &tmp, &tmp) != EOF)
            lines++; 
    return lines;
}

BOOLEAN PointImageObject::load_file(const char *f_name)
{
    FILE* fs;
    UINT32 counter;
    GLdouble px, py, pz;
    GLdouble nx, ny, nz;
    GLdouble length;
    vertices = (GLdouble*)malloc(sizeof(GLdouble)* n_points * 3);
    normals = (GLdouble*)malloc(sizeof(GLdouble)* n_points * 3);
    x_min = y_min = z_min = 10e30;
    x_max = y_max = z_max = -10e30;
    counter = 0;

    if (fopen_s(&fs, f_name, "r") == 0)
    {
        for (UINT32 i = 0; i < n_points; ++i)
        {
            fscanf_s(fs, "%lf %lf %lf %lf %lf %lf", &px, &py, &pz, &nx, &ny, &nz);
            x_min = std::min(x_min, px);
            y_min = std::min(y_min, py);
            z_min = std::min(z_min, pz);
            x_max = std::max(x_max, px);
            y_max = std::max(y_max, py);
            z_max = std::max(z_max, pz);
            vertices[counter] = px;
            vertices[counter + 1] = py;
            vertices[counter + 2] = pz;
            length = sqrt(nx * nx + ny * ny + nz * nz);
            normals[counter] = nx / length;
            normals[counter + 1] = ny / length;
            normals[counter + 2] = nz / length;
            counter += 3;
        }
        return TRUE;
    }
    return FALSE;
}

void PointImageObject::render()
{
    double angle;

    Object::render();
    
    angle = min_fov(y_max - y_min, 20.0);
    
    API_setProjectionMatrix(angle);

    for (UINT32 i = 0; i < n_points; ++i)
    {
        API_Normal(normals[i * 3], normals[i * 3 + 1], normals[i * 3 + 2]);
        API_drawPoint(vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2]);
    }
}

void PointImageObject::reset()
{
    Object::reset();
    /*scale = 2.0 * 20 * tan(degree2rad(15.0 / 2)) / (y_max - y_min + (z_max + z_min) * tan(degree2rad(15.0 / 2.0)));*/
    camera = Camera(Vector4(0, 0, 20.0), Vector4(0, 0, -1), Vector4(0, 1, 0));
    position[0] = -scale * (x_min + x_max) / 2;
    position[1] = -scale * (y_min + y_max) / 2;
    position[2] = -scale * (z_min + z_max) / 2;
    updateMatrix();
    obj_type = Object::ObjectType::PointCloud;
}