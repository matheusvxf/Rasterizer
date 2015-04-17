#include "Ball.h"
#include "Utility.h"

#include <iostream>
#include <GL/glut.h>

static Vector4 gravity(0, -9.8, 0);

Ball::Ball()
{
    obj_type = Object::ObjectType::Ball;
    reset();
}

Ball::~Ball()
{
}

void Ball::update()
{
    applyForce(gravity * mass);
    Object::update();
}

void Ball::render()
{
    Object::render();

    glBegin(GL_QUADS);
    glEnable(GL_LIGHTING);
    glColor3d(1.0, 0.5, .5);
    glutSolidSphere(radius, 1024, 1024);
    glEnd();
}

void Ball::collide(const Vector4& point)
{
    Vector4 force;
    position = point;
    force = -(velocity).normalize() * 100;
    applyForce(force);
}

void Ball::collide(const Wall& wall){
	Vector4 force;
	double proj_pos = (position - wall.center).dot(wall.normal);
    double proj_vel = velocity.dot(wall.normal);
    position -= wall.normal * proj_pos;
	velocity -= wall.normal * proj_vel * 2 * 0.9;
}

void Ball::reset()
{
    Object::reset();
    radius = 2;
    mass = 5;
    friction = 0.1;
    force = Vector4(rand_int(-5000, 5000), rand_int(-5000, 5000), rand_int(-5000, 5000));
}