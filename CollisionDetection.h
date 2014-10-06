#ifndef COLLISION_DETECT_H
#define COLLISION_DETECT_H

//#define NO_COLLISION

//#include "SFML\Graphics.hpp"
#include "BouncingThing.h"

class CollisionDetection
{
private:
	//private constructors so that we never instantiate this class
	CollisionDetection();
	CollisionDetection(const CollisionDetection &);

	//calculate whether two projected lines overlap and returns the distance of overlap if they do
	static std::pair<bool, double> CollisionDetection::checkOverlap(const Vector2f &A, const Vector2f &B);

public:
	~CollisionDetection();

	//check for collision using Separating Axis Theorem
	//returns true if they collide and the Minimum Translation Vector if they do
	static std::pair<bool, Vector2f> CheckCollisionSAT(const BouncingThing & A, const BouncingThing & B);
};
#endif

