#ifndef BOUNCING_THING_H
#define BOUNCING_THING_H

#include "SFML\Graphics.hpp"
#include <vector>

using namespace sf;

class BouncingThing {
protected:
	Vector2f m_centrePos, m_velocity;
	float m_angularVelocity, m_radius;

	std::vector<Vector2f> m_points;
	ConvexShape m_shape;

	int m_id;
	std::vector<int> checkedIDs;	//used in collision optimization (to make any pair of objects is tested for collision at most once per frame)

	BouncingThing(int numberOfPoints);	//for derived classes only

public:
	// CONSTRUCTORS -----------------------------
	BouncingThing (Vector2f position, float radius, int numberOfPoints, int id);

	//---------------------------
	void Update(const RenderWindow &w);
	void Draw(RenderWindow &w) const;
	void Rotate();

	// GET ----------------------
	Vector2f getVelocity() const;
	Vector2f getPosition() const;
	float getRadius() const;
	int getNumberOfPoints() const;
	int getID() const;

	// SET ----------------------
	void setVelocity(const Vector2f newVel);
	void setPosition(const Vector2f newPos);

	// COLLISION ----------------
	//static Vector2f CheckCollisionSAT(const BouncingThing &A, const BouncingThing &B);
	std::vector<Vector2f> getAxies() const;	//get the axies for SAT
	Vector2f projectOntoAxis(Vector2f axis) const;
	bool wasCollisionTested(int id);
	void setCollisionTested(int id);
	bool intersectsBoundingCircle(BouncingThing const &A);
};
#endif