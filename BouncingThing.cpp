//#include "SFML\Graphics.hpp"
#include "BouncingThing.h"

#define _USE_MATH_DEFINES
#include <math.h>

static Vector2f getPointAtRadius(float radius, float angleDegrees) {
		// Convert from degrees to radians via multiplication by PI/180        
        float x = (float)(radius * cos(angleDegrees * M_PI / 180.0));
        float y = (float)(radius * sin(angleDegrees * M_PI / 180.0));

		return Vector2f(x,y);
}

// CONSTRUCTORS -----------------------------
BouncingThing::BouncingThing (Vector2f position, float radius, int numberOfPoints, int id) {
	m_centrePos = position;
	m_shape = ConvexShape(numberOfPoints);
	m_points.reserve(numberOfPoints);
	m_id = id;
	
	//The points will all lie on an imaginary circumference.
	//We will use this angle with the function getPointAtRadius(...) to calculate each point of our shape.
	float angle = 360 / (float)numberOfPoints;

	for (int i = 0; i < numberOfPoints; i++) {
		//Calculate where each point is and add it to our vector.
		//Note that each point is a displacement from the centre of the shape.
		m_points.push_back(getPointAtRadius(radius, angle *i+1));
		m_shape.setPoint(i, m_points[i]);
	}

	//randomize the velocities
	m_velocity = Vector2f(((rand() % 10) - 5) / 2.0f, ((rand() % 10) - 5) / 2.0f);
	m_angularVelocity = (rand() % 10) - 5;

	m_shape.setFillColor(Color(rand()%255, rand()%255, rand()%255));
}

BouncingThing::BouncingThing(int numberOfPoints) {
	m_shape = ConvexShape(numberOfPoints);
	m_points.reserve(numberOfPoints);

	//randomize the velocities
	m_velocity = Vector2f(((rand() % 10) - 5) / 2.0f, ((rand() % 10) - 5) / 2.0f);
	m_angularVelocity = (rand() % 10) - 5;

	m_shape.setFillColor(Color(rand()%255, rand()%255, rand()%255));
}

//---------------------------
void BouncingThing::Update(const RenderWindow &w) {
	Rotate();

	m_centrePos += m_velocity;
	m_shape.setPosition(m_centrePos);

	if(m_centrePos.x >= w.getSize().x || m_centrePos.x <= 0)
		m_velocity.x *= -1;
	if(m_centrePos.y >= w.getSize().y || m_centrePos.y <= 0)
		m_velocity.y *= -1;
}
void BouncingThing::Draw(RenderWindow &w) const {
	w.draw(m_shape);
}
void BouncingThing::Rotate() {
	Transform m_rotation;
	m_rotation.rotate(m_angularVelocity);

	for ( int i = 0; i < m_points.size(); i++ ) {

		//rotate each point
		m_points[i] = m_rotation * m_points[i];

		//and update the shape to match
		m_shape.setPoint(i, m_points[i]);
	}
}

// GET ----------------------
Vector2f BouncingThing::getVelocity() const {
	return m_velocity;
}
Vector2f BouncingThing::getPosition() const {
	return m_centrePos;
}

float BouncingThing::getRadius() const {
	return m_radius;
}

int BouncingThing::getNumberOfPoints() const {
	return m_points.size();
}

int BouncingThing::getID() const {
	return m_id;
}

// SET ----------------------
void BouncingThing::setVelocity(const Vector2f newVel) {
	m_velocity = newVel;
}
void BouncingThing::setPosition(const Vector2f newPos) {
	m_centrePos = newPos;
}

// COLLISION ----------------
std::vector<Vector2f> BouncingThing::getAxies() const {
	std::vector<Vector2f> axies;
	axies.reserve(m_points.size());

	//loop over the vertices
	for (int i = 0; i < m_points.size(); i++) {

	  //get the current vertex
		Vector2f p1 = m_points[i];

	  //get the next vertex
	  Vector2f p2 = m_points[i + 1 == m_points.size() ? 0 : i + 1];
	  //turnary operator used so that we don't go out of bounds

	  //subtract the two to get the edge vector
	  Vector2f edge = p1 - p2;

	  //get either perpendicular vector
	  Vector2f normal = Vector2f(-edge.y, edge.x);
	  axies.push_back(normal);
	}

	return axies;
}

double vectorDotProduct(const Vector2f &A, const Vector2f &B) {
	return (A.x * B.x) + (A.y * B.y);
}

Vector2f BouncingThing::projectOntoAxis(Vector2f axis) const {
	//normalize the axis
	float magnitude = sqrt((axis.x * axis.x) + (axis.y * axis.y));
	axis /= magnitude;

	//keep track of minimum and maximum points on the axis
	double min = vectorDotProduct(axis, m_points[0] + m_centrePos);
	double max = min;

	//loop through the points and find the min and max values for projection
	for (int i = 1; i < m_points.size(); i++) {
		double p = vectorDotProduct(axis, m_points[i] + m_centrePos);
		if (p < min) {
			min = p;
		}
		else if (p > max) {
			max = p;
		}
	}

	Vector2f proj = Vector2f(min, max);
	return proj;
}