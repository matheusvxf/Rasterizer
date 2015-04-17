#include "Object.h"
#include "Keyboard.h"
#include "Config.h"
#include "Utility.h"
#include "main.h"

#include <iostream>
#include "GL/GLU.h"

void Keyboard::keyPressCb(unsigned char key, INT32 x, INT32 y)
{
    static Vector4 move_left(5, 0, 0);
    static Vector4 move_right(5, 0, 0);
    static Vector4 move_up(0, 5, 0);
    static Vector4 move_down(0, -10, 0);
    static Vector4 move_in(0, 0, -10);
    static Vector4 move_out(0, 0, 10);
#if (DEBUG == TRUE)
    std::cout << "Press(" << key2str(key) << ")" << std::endl;
#endif
    switch (key)
    {
    case press::t:
        Globals::curr_obj->spinToggle();
        break;
    case press::x:
        Globals::curr_obj->applyForce(move_left);
        break;
    case press::X:
        Globals::curr_obj->applyForce(move_right);
        break;
    case press::y:
        Globals::curr_obj->applyForce(move_down);
        break;
    case press::Y:
        Globals::curr_obj->applyForce(move_up);
        break;
    case press::z:
        Globals::curr_obj->applyForce(move_in);
        break;
    case press::Z:
        Globals::curr_obj->applyForce(move_out);
        break;
    case press::r:
        Globals::curr_obj->reset();
        break;
    case press::o:
        Globals::curr_obj->rotateZ(5);
        break;
    case press::O:
        Globals::curr_obj->rotateZ(-5);
        break;
    case press::p:
        Globals::curr_obj->rotateX(5);
        break;
    case press::P:
        Globals::curr_obj->rotateX(-5);
        break;
    case press::l:
        Globals::curr_obj->rotateY(5);
        break;
    case press::L:
        Globals::curr_obj->rotateY(-5);
        break;
    case press::s:
        if (Globals::curr_obj->obj_type == Object::ObjectType::PointCloud)
            Globals::curr_obj->addScale(-0.01);
        else
            Globals::curr_obj->addScale(-1);
        break;
    case press::S:
        if (Globals::curr_obj->obj_type == Object::ObjectType::PointCloud)
            Globals::curr_obj->addScale(0.4);
        else
            Globals::curr_obj->addScale(1);
        break;
    case press::b:
        if (Globals::curr_obj->obj_type == Object::ObjectType::Cube)
        {
            Globals::curr_obj = (Object*)&Globals::house;
        }
        else if (Globals::curr_obj->obj_type == Object::ObjectType::House)
        {
            Globals::curr_obj = (Object*)&Globals::ball;
        }
        else if (Globals::curr_obj->obj_type == Object::ObjectType::Ball)
        {
            Globals::curr_obj = (Object*)&Globals::cube;
        }
        break;
    case press::h:
        Globals::curr_obj->applyForce(Vector4(rand_int(-300, 300), rand_int(0, 300), rand_int(-300, 300)));
        break;
    case press::k1:
        Globals::shading_flag = false;
        Globals::z_buffer_flag = false;
        Globals::point_size_flag = false;
        Globals::circuler_point_flag = false;
        Globals::point_fake_diffuse_light_flag = false;
        break;
    case press::k2:
        Globals::shading_flag = true;
        Globals::z_buffer_flag = false;
        Globals::point_size_flag = false;
        Globals::circuler_point_flag = false;
        Globals::point_fake_diffuse_light_flag = false;
        break;
    case press::k3:
        Globals::shading_flag = true;
        Globals::z_buffer_flag = true;
        Globals::point_size_flag = false;
        Globals::circuler_point_flag = false;
        Globals::point_fake_diffuse_light_flag = false;
        break;
    case press::k4:
        Globals::shading_flag = true;
        Globals::z_buffer_flag = true;
        Globals::point_size_flag = true;
        Globals::circuler_point_flag = false;
        Globals::point_fake_diffuse_light_flag = false;
        break;
    case press::k5:
        Globals::shading_flag = true;
        Globals::z_buffer_flag = true;
        Globals::point_size_flag = true;
        Globals::circuler_point_flag = true;
        Globals::point_fake_diffuse_light_flag = false;
        break;
    case press::k6:
        Globals::shading_flag = true;
        Globals::z_buffer_flag = true;
        Globals::point_size_flag = true;
        Globals::circuler_point_flag = true;
        Globals::point_fake_diffuse_light_flag = true;
        break;
    }
    Globals::curr_obj->print();
}

void Keyboard::specialFuncCb(int key, int x, int y){
#if (DEBUG == TRUE)
    std::cout << "Press(" << key2str(key) << ")" << std::endl;
#endif
    switch (key)
    {
    case GLUT_KEY_F1:
        Globals::curr_obj = (Object*)&Globals::bunny;
        break;
    case GLUT_KEY_F2:
        Globals::curr_obj = (Object*)&Globals::dragon;
        break;
    case GLUT_KEY_F3:
        Globals::curr_obj = (Object*)&Globals::house;
        Globals::house.setCamera(Vector4(-15, 5, 10), Vector4(-5, 0, 0), Vector4(0, 1, 0.5));
        break;
    case GLUT_KEY_F4:
        Globals::curr_obj = (Object*)&Globals::bunny;
        break;
    case GLUT_KEY_F5:
        Globals::curr_obj = (Object*)&Globals::dragon;
        break;
    }
}

std::string Keyboard::key2str(UINT8 key)
{
    switch (key)
    {
    case press::b: return "b";
    case press::h: return "h";
    case press::l: return "l";
    case press::L: return "L";
    case press::o: return "o";
    case press::O: return "O";
    case press::p: return "p";
    case press::P: return "P";
    case press::r: return "r";
    case press::s: return "s";
    case press::S: return "S";
    case press::t: return "t";
    case press::x: return "x";
    case press::X: return "X";
    case press::z: return "z";
    case press::Z: return "Z";
    case press::y: return "y";
    case press::Y: return "Y";
    case GLUT_KEY_F1: return "F1";
    case GLUT_KEY_F2: return "F2";
    case GLUT_KEY_F3: return "F3";
    case GLUT_KEY_F4: return "F4";
    case GLUT_KEY_F5: return "F5";
    case press::k1: return "1";
    case press::k2: return "2";
    case press::k3: return "3";
    case press::k4: return "4";
    case press::k5: return "5";
    case press::k6: return "6";
    default: return "Unknown key!";
    }
}