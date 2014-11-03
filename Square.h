#ifndef SQUARE_H
#define SQUARE_H

#include "BouncingThing.h"

using namespace sf;

class Square : public BouncingThing {
public:
	Square(Vector2f position, float radius, int id);
};
#endif