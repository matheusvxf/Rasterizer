#include "TestObject.h"
#include "main.h"

TestObject::TestObject()
{
    camera = Camera(Vector4(0, 0, 5), Vector4(0, 0, -1), Vector4(0, 1, 0));
}

TestObject::~TestObject()
{
}

void TestObject::render()
{
    Object::render();
}