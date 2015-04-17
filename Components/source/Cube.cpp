#include "Cube.h"
#include "Matrix4.h"
#include "main.h"

#include <GL/glut.h>
#include <iostream>
#include <sstream>

using namespace std;

Cube::Cube()
{
    halfEdgeSize = 5;
    obj_type = Object::ObjectType::Cube;
}

void Cube::update()
{
    rotateY(0.1);
    Object::update();
}

void Cube::render()
{
    Object::render();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMultMatrixd(this->getGLrotateX());
    glMultMatrixd(this->getMatrix().getPointer());
    glMultMatrixd(this->getGLrotateY());
    glMultMatrixd(this->getGLrotateZ());

    // Draw all six faces of the cube:
    glBegin(GL_QUADS);
    glColor3f(0.0, 1.0, 0.0);		// This makes the cube green; the parameters are for red, green and blue. 
    // To change the color of the other faces you will need to repeat this call before each face is drawn.
    // Draw front face:
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-halfEdgeSize, halfEdgeSize, halfEdgeSize);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(halfEdgeSize, halfEdgeSize, halfEdgeSize);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(halfEdgeSize, -halfEdgeSize, halfEdgeSize);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-halfEdgeSize, -halfEdgeSize, halfEdgeSize);

    // Draw left side:
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-halfEdgeSize, halfEdgeSize, halfEdgeSize);
    glVertex3f(-halfEdgeSize, halfEdgeSize, -halfEdgeSize);
    glVertex3f(-halfEdgeSize, -halfEdgeSize, -halfEdgeSize);
    glVertex3f(-halfEdgeSize, -halfEdgeSize, halfEdgeSize);

    // Draw right side:
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(halfEdgeSize, halfEdgeSize, halfEdgeSize);
    glVertex3f(halfEdgeSize, halfEdgeSize, -halfEdgeSize);
    glVertex3f(halfEdgeSize, -halfEdgeSize, -halfEdgeSize);
    glVertex3f(halfEdgeSize, -halfEdgeSize, halfEdgeSize);

    // Draw back face:
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(-halfEdgeSize, halfEdgeSize, -halfEdgeSize);
    glVertex3f(halfEdgeSize, halfEdgeSize, -halfEdgeSize);
    glVertex3f(halfEdgeSize, -halfEdgeSize, -halfEdgeSize);
    glVertex3f(-halfEdgeSize, -halfEdgeSize, -halfEdgeSize);

    // Draw top side:
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-halfEdgeSize, halfEdgeSize, halfEdgeSize);
    glVertex3f(halfEdgeSize, halfEdgeSize, halfEdgeSize);
    glVertex3f(halfEdgeSize, halfEdgeSize, -halfEdgeSize);
    glVertex3f(-halfEdgeSize, halfEdgeSize, -halfEdgeSize);

    // Draw bottom side:
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(-halfEdgeSize, -halfEdgeSize, -halfEdgeSize);
    glVertex3f(halfEdgeSize, -halfEdgeSize, -halfEdgeSize);
    glVertex3f(halfEdgeSize, -halfEdgeSize, halfEdgeSize);
    glVertex3f(-halfEdgeSize, -halfEdgeSize, halfEdgeSize);
    glEnd();
}