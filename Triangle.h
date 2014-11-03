#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "BouncingThing.h"

using namespace sf;

class Triangle : public BouncingThing {
public:
	Triangle(Vector2f position, float radius, int id);
};
#endif