////#include "SFML\Graphics.hpp"
//#include "Triangle.h"
//
//Triangle::Triangle(std::vector<Vector2f> points) : BouncingThing(3) {
//	if(points.size() != 3) {
//		throw "A triangle may only have 3 points!";
//	}
//
//	//set the centre to the average of the three corners
//	m_centrePos = (points[0] + points[1] + points[2]) / 3.0f;
//
//	for(int i = 0; i < 3; i++)
//	{
//		//add points to member vector as points relative to the centre
//		m_points.push_back(points[i] - m_centrePos);
//	}
//}