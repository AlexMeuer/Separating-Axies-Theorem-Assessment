#include "CollisionDetection.h"


CollisionDetection::CollisionDetection()
{
}


CollisionDetection::~CollisionDetection()
{
}

//Returns true if they overlap and the overlap distance if they do
std::pair<bool, double> CollisionDetection::checkOverlap(const Vector2f &A, const Vector2f &B) {

	if ( A.x >= B.x && A.x <= B.y )
		return std::make_pair(true, B.y - A.x);

	else if ( A.y >= B.x && A.y <= B.y )
		return std::make_pair(true, A.y - B.x);

	return std::make_pair(false, 0);
}


double dotProduct(const Vector2f &A, const Vector2f &B) {
	return (A.x * B.x) + (A.y * B.y);
}

Vector2f vectorNormalize(const Vector2f &V) {
	float magnitude = sqrt((V.x * V.x) + (V.y * V.y));

	return V / magnitude;
}


std::pair<bool, Vector2f> CollisionDetection::CheckCollisionSAT(const BouncingThing & A, const BouncingThing & B)
{
	double overlap = DBL_MAX;	//maximum value for type double
	Vector2f smallest;
	std::vector<Vector2f> axies1 = A.getAxies();
	std::vector<Vector2f> axies2 = B.getAxies();
	Vector2f p1, p2;

	//iterate through axies1
	for (std::vector<Vector2f>::iterator itr = axies1.begin();
		itr != axies1.end();
		itr++)
	{
		Vector2f axis = *itr;

		//project both shapes onto the axis
		p1 = A.projectOntoAxis(axis);
		p2 = B.projectOntoAxis(axis);

		std::pair<bool, double> result = checkOverlap(p1, p2);

		if ( result.first ) {
			// check for minimum
			if (result.second < overlap) {
				// then set this one as the smallest
				overlap = result.second;
				smallest = axis;
			}
		}
		else {
			return std::make_pair(false, Vector2f());
		}
	}

	//iterate through axies2
	for (std::vector<Vector2f>::iterator itr = axies2.begin();
		itr != axies2.end();
		itr++)
	{
		Vector2f axis = *itr;

		//project both shapes onto the axis
		p1 = A.projectOntoAxis(axis);
		p2 = B.projectOntoAxis(axis);

		std::pair<bool, double> result = checkOverlap(p1, p2);

		if ( result.first ) {
			// check for minimum
			if (result.second < overlap) {
				// then set this one as the smallest
				overlap = result.second;
				smallest = axis;
			}
		}
		else {
			return std::make_pair(false, Vector2f());	//NO COLLISION
		}
	}

	//MTV is the Minimum Translation Vector.
	//we multiply the smallest colliding axis (normalized) by the overlap to get
	//a vector that will separate the shapes with smallest magnitude.
	smallest = vectorNormalize(smallest);

	//if already moving away from each other
	if( (dotProduct(A.getVelocity(), smallest) < 0)
		&&
		(dotProduct(B.getVelocity(), smallest) < 0) )
		return std::make_pair(true, Vector2f(0,0));

	Vector2f mtv = Vector2f(smallest * (float)overlap);

	return std::make_pair(true, mtv);	//YES COLLISION
}
