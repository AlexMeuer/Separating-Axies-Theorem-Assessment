////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
//#include "stdafx.h"
#ifdef _DEBUG
#pragma comment(lib,"sfml-graphics-d.lib")
#pragma comment(lib,"sfml-audio-d.lib")
#pragma comment(lib,"sfml-system-d.lib")
#pragma comment(lib,"sfml-window-d.lib")
#pragma comment(lib,"sfml-network-d.lib")
#else
#pragma comment(lib,"sfml-graphics.lib")
#pragma comment(lib,"sfml-audio.lib")
#pragma comment(lib,"sfml-system.lib")
#pragma comment(lib,"sfml-window.lib")
#pragma comment(lib,"sfml-network.lib")
#endif
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include <iostream>
#include <vector>

//#include "Circle.h"
//#include "Triangle.h"
#include "BouncingThing.h"
#include "CollisionDetection.h"

using namespace std;

float distance(Vector2f const &A, Vector2f const &B)
{
	return sqrt( pow( (B.x - A.x) + (B.y - A.y), 2) );
}
 
 
////////////////////////////////////////////////////////////
///Entrypoint of application
////////////////////////////////////////////////////////////
 
int main()
{
	srand(time(NULL));	//seed the random gen

	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "SFML First Program");
	window.setFramerateLimit(150);

	//load a font
	sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\GARA.TTF");
 
	//create a formatted text string
	sf::Text text;
	text.setFont(font);
	text.setString("Assessment 1");
	text.setStyle(sf::Text::Underlined| sf::Text::Italic | sf::Text::Bold);
	text.setPosition(5,5);
	text.setCharacterSize(20);

	//calculate framerate
	sf::Clock clock;
	clock.restart();
	float framerate;

	//create a circle
	/*sf::CircleShape circle(50);
	circle.setPosition(300,200);*/
	//Circle circle(window);
	//std::vector<Circle> circles = std::vector<Circle>();
	//const int max_circles = 20;
	//for(int i = 0; i < max_circles; i++)
	//{
	//	circles.push_back(Circle(window));
	//}

	//Triangle tri = Triangle(Vector2f(rand() % window.getSize().x, rand() % window.getSize().y), 30);
	//BouncingThing leeroy = BouncingThing(Vector2f(rand() % window.getSize().x, rand() % window.getSize().y), 30, 3);
	//BouncingThing jenkins = BouncingThing(Vector2f(rand() % window.getSize().x, rand() % window.getSize().y), 30, 4);

	vector<BouncingThing> bouncingThings;
	const int maxThings = 20;
	bouncingThings.reserve(maxThings);

	int id = 0;

	for ( int i = 0; i < maxThings; i++ ) {
		//create a bouncing thing with randomized parameters
		bouncingThings.push_back(BouncingThing(Vector2f(rand() % window.getSize().x, rand() % window.getSize().y), 30, rand() % 5 + 3, id++));
	}
	//vector<Vector2f> myVec;
	//myVec.push_back(Vector2f(15,15));
	//myVec.push_back(Vector2f(10,10));
	//myVec.push_back(Vector2f(20,30));
	//Triangle tryHard = Triangle(myVec);

	// Start game loop
	while (window.isOpen())
	{
		// Process events
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			// Close window : exit
			if (Event.type == sf::Event::Closed)
			window.close();
			// Escape key : exit
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
			window.close();
		}
		//prepare frame
		window.clear();

		//calculate framerate
		framerate = 1.f / clock.getElapsedTime().asSeconds();
		clock.restart();
 
		//draw frame items
		window.draw(text);
 
		//circle.Update(window);
		//circle.Draw(window);
		//for(std::vector<Circle>::iterator itr = circles.begin();
		//	itr != circles.end();
		//	itr++)
		//{
		//	itr->Update(window);
		//	itr->Draw(window);

		//	for(std::vector<Circle>::iterator itr2 = circles.begin();
		//		itr2 != circles.end();
		//		itr2++)
		//	{
		//		if(itr != itr2)
		//		{
		//			if( Circle::CheckCollision(*itr, *itr2) )
		//			{
		//				//swap opposite velocities (assumes circles have same mass)
		//				Vector2f swap = itr2->getVelocity();
		//				itr2->setVelocity(itr->getVelocity());
		//				itr->setVelocity(swap);
		//			}
		//		}
		//	}
		//}

		//tri.Update(window);
		//tri.Draw(window);
		
		//leeroy.Update(window);
		//leeroy.Draw(window);
		//jenkins.Update(window);
		//jenkins.Draw(window);

		//vector to keep track of which objects we've tested;
		vector<pair<BouncingThing*, BouncingThing*>> testedPairs;
		vector<pair<BouncingThing*, BouncingThing*>>::iterator testedItr;

		for(std::vector<BouncingThing>::iterator itr = bouncingThings.begin();
			itr != bouncingThings.end();
			itr++)
		{
			//collision detectiong
			for(std::vector<BouncingThing>::iterator itr2 = bouncingThings.begin();
				itr2 != bouncingThings.end();
				itr2++)
			{
				if(itr != itr2)	//don't let it check against itself!
				{
					if ( distance(itr->getPosition(), itr2->getPosition())
						< itr->getRadius() + itr2->getRadius() )
					{
						//check whether we've already tested collision between itr and itr2
						bool alreadyChecked = false;
						//for( testedItr = testedPairs.begin(); testedItr != testedPairs.end(); testedItr++ )
						//{
						//	//this will never happen
						//	/*if ( itr->getID() == testedItr->first->getID()
						//		&& itr2->getID() == testedItr->second->getID() ) {
						//		alreadyChecked = true;
						//		break;
						//	}*/

						//	if ( itr2->getID() == testedItr->first->getID()
						//		&& itr->getID() == testedItr->second->getID() ) {
						//		alreadyChecked = true;
						//		break;
						//	}
						//}

						//if we've already done collision check, don't check again.
						if ( alreadyChecked )
							continue;

						//check if they collide...
						pair<bool, Vector2f> pair = CollisionDetection::CheckCollisionSAT(*itr, *itr2);

						if( pair.first ) {
							//...do something if they collide
							itr->setPosition(itr->getPosition() + (pair.second / 2.0f));	//move them apart so they're not intersecting
							itr2->setPosition(itr2->getPosition() + (pair.second / -2.0f));	//(using the minimum translation vector)

							Vector2f swap = itr->getVelocity();
							itr->setVelocity(itr2->getVelocity());
							itr2->setVelocity(swap);
						}

						testedPairs.push_back(make_pair(&*itr, &*itr2));
					}//if(distance)
				}//if(itr!=itr2)
			}//itr2 loop

			//update and draw each thing
			itr->Update(window);
			itr->Draw(window);
		}//itr loop

		//tryHard.Update(window);
		//tryHard.Draw(window);



		// Finally, display rendered frame on screen
		window.display();

	} //loop back for next frame
	return EXIT_SUCCESS;
}