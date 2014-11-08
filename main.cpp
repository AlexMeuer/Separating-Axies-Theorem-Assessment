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
#include <thread>

//#include "Circle.h"
//#include "BouncingThing.h"
#include "Triangle.h"
#include "Square.h"
#include "CollisionDetection.h"

using namespace std;

//-------------------------------------------
//
//	See Readme.md for details, known issues, etc.
//
// ------------------------------------------

//float euclideanDistance(Vector2f const &A, Vector2f const &B)
//{
//	return sqrt( pow( (B.x - A.x) + (B.y - A.y), 2) );
//}

//double vectorDotProduct(const Vector2f &A, const Vector2f &B) {
//	return (A.x * B.x) + (A.y * B.y);
//}
//
//Vector2f vectorNormalize(const Vector2f &V) {
//	float magnitude = sqrt((V.x * V.x) + (V.y * V.y));
//
//	return V / magnitude;
//}

void HandleCollision(BouncingThing * itr, BouncingThing * itr2) {
	//check if they collide...
	pair<bool, Vector2f> pair = CollisionDetection::CheckCollisionSAT(*itr, *itr2);

	if( pair.first) {
		//...do something if they collide
		itr->setPosition(itr->getPosition() + (pair.second / 2.0f));	//move them apart so they're not intersecting
		itr2->setPosition(itr2->getPosition() - (pair.second / 2.0f));	//(using the minimum translation vector)

		if( pair.second != Vector2f(0,0) ) {

		//get the components of the velocity vectors which are parallel to the collision
		float magnitude = sqrtf((pair.second.x * pair.second.x) + (pair.second.y * pair.second.y));
		Vector2f normMTV(pair.second / magnitude);

		//dot product
		float aci = (itr->getVelocity().x * normMTV.x) + (itr->getVelocity().y * normMTV.y);
		float bci = (itr2->getVelocity().x * normMTV.x) + (itr2->getVelocity().y * normMTV.y);

		itr->setVelocity(itr->getVelocity() + (bci - aci) * normMTV);
		itr2->setVelocity(itr2->getVelocity() + (aci - bci) * normMTV);
		}
	}

	//add IDs to appropriate lists so that we don't check for collision again.
	itr->setCollisionTested(itr2->getID());
	itr2->setCollisionTested(itr->getID());
}

void CollisionWindow( bool optimize ) {

	// Create the window
	RenderWindow window(sf::VideoMode(800, 600, 32), "SAT ASSESMENT | Optimized: " + to_string(optimize));
	//window.setFramerateLimit(60);

	//load a font
	sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\GARA.TTF");
 
	//create a formatted text string
	sf::Text text;
	text.setFont(font);
	text.setStyle(sf::Text::Underlined| sf::Text::Italic | sf::Text::Bold);
	text.setPosition(5,5);
	text.setCharacterSize(20);

	//calculate frame rate
	sf::Clock clock = Clock();
	float framerate = 0;
	unsigned long refreshes = 0;

	vector<BouncingThing> bouncingThings;
	const int maxThings = 20;
	bouncingThings.reserve(maxThings);

	int id = 0;

	for ( int i = 0; i < maxThings; i++ ) {
		//create a triangle or square with ranomized parameters
		if ( i % 2 )
			bouncingThings.push_back(Triangle(Vector2f(rand() % window.getSize().x, rand() % window.getSize().y), rand() % 10 + 25, id++));
		else
			bouncingThings.push_back(Square(Vector2f(rand() % window.getSize().x, rand() % window.getSize().y), rand() % 10 + 25, id++));
	}

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
 
		//draw frame items
		window.draw(text);

		for(std::vector<BouncingThing>::iterator itr = bouncingThings.begin();
			itr != bouncingThings.end();
			itr++)
		{
			//collision detection
			for(std::vector<BouncingThing>::iterator itr2 = bouncingThings.begin();
				itr2 != bouncingThings.end();
				itr2++)
			{
				if(itr != itr2)	//don't let it check against itself!
				{
					if ( optimize ) {

						//If these two object were already tested against each other...
						if ( itr->wasCollisionTested(itr2->getID())
								|| itr2->wasCollisionTested(itr->getID()) )
						{
								continue;	//...we've already checked these for collision, skip 'em
						}

					}// end if ( optimize ) {

					if ( optimize ) {

						//check if their bounding circles intersect
						if(itr->intersectsBoundingCircle(*itr2))
						{
							//i know the codes messy. i butchered it last second so that I could show a side-by-side comparison
							HandleCollision(&*itr, &*itr2);
						}

					}
					else {
						HandleCollision(&*itr, &*itr);
					}// end if ( optimize ) {

				}//if(itr!=itr2)
			}//itr2 loop

			//update and draw each thing
			itr->Update(window);
			itr->Draw(window);
		}//itr loop

		//calculate framerate
		refreshes++;
		framerate += 1.f / clock.getElapsedTime().asSeconds();
		text.setString("Framerate: " + to_string(framerate / refreshes));
		clock.restart();

		// Finally, display rendered frame on screen
		window.display();

	} //loop back for next frame
}
 
 
////////////////////////////////////////////////////////////
///Entry point of application
////////////////////////////////////////////////////////////
 
int main()
{
	srand(time(NULL));	//seed the random gen

	// TL;DR
	// -----
	// I made two windows (each has the code that is below),
	// and each one runs on it's own thread.
	// Reason: side-by-side comparison

	//Threads
	thread optimized = thread(CollisionWindow, true);
	thread non_optimized = thread(CollisionWindow, false);

	cout << "There are two windows!\nDrag the top one to reveal." << endl;

	optimized.join();
	non_optimized.join();

	return EXIT_SUCCESS;

	//Original code:

	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "SFML First Program");
	window.setFramerateLimit(60);

	//load a font
	sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\GARA.TTF");
 
	//create a formatted text string
	sf::Text text;
	text.setFont(font);
	text.setStyle(sf::Text::Underlined| sf::Text::Italic | sf::Text::Bold);
	text.setPosition(5,5);
	text.setCharacterSize(20);

	//calculate frame rate
	sf::Clock clock = Clock();
	float framerate = 0;
	unsigned long refreshes = 0;

	//create a circle
	//*sf::CircleShape circle(50);
	//circle.setPosition(300,200);*/
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
		//bouncingThings.push_back(BouncingThing(Vector2f(rand() % window.getSize().x, rand() % window.getSize().y), 30, rand() % 5 + 3, id++));
		//bouncingThings.push_back(BouncingThing(Vector2f(rand() % window.getSize().x, rand() % window.getSize().y), rand() % 15 + 15, 100, id++));
		
		//create a triangle or square with ranomized parameters
		if ( i % 2 )
			bouncingThings.push_back(Triangle(Vector2f(rand() % window.getSize().x, rand() % window.getSize().y), rand() % 10 + 25, id++));
		else
			bouncingThings.push_back(Square(Vector2f(rand() % window.getSize().x, rand() % window.getSize().y), rand() % 10 + 25, id++));
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

		for(std::vector<BouncingThing>::iterator itr = bouncingThings.begin();
			itr != bouncingThings.end();
			itr++)
		{
			//collision detection
			for(std::vector<BouncingThing>::iterator itr2 = bouncingThings.begin();
				itr2 != bouncingThings.end();
				itr2++)
			{
				if(itr != itr2)	//don't let it check against itself!
				{
					//If these two object were already tested against each other...
					if ( itr->wasCollisionTested(itr2->getID())
							|| itr2->wasCollisionTested(itr->getID()) )
					{
							continue;	//...we've already checked these for collision, skip 'em
					}

					//check if their bounding circles intersect
					if(itr->intersectsBoundingCircle(*itr2))
					{
						//check whether we've already tested collision between itr and itr2
						//bool alreadyChecked = false;

						//Collision doesnt seem to work if I uncomment this. Objects pass through each other.
						//if ( itr->wasCollisionTested(itr2->getID())
						//	|| itr2->wasCollisionTested(itr->getID()) )
						//{
						//	//alreadyChecked = true;
						//	continue;	//we've already checked these for collision, skip 'em
						//}
						//if we've already done collision check, don't check again.
						/*if ( alreadyChecked )
							continue;*/

						//check if they collide...
						pair<bool, Vector2f> pair = CollisionDetection::CheckCollisionSAT(*itr, *itr2);

						if( pair.first) {
							//...do something if they collide
							itr->setPosition(itr->getPosition() + (pair.second / 2.0f));	//move them apart so they're not intersecting
							itr2->setPosition(itr2->getPosition() - (pair.second / 2.0f));	//(using the minimum translation vector)

							/*Vector2f swap = itr->getVelocity();
							itr->setVelocity(itr2->getVelocity());
							itr2->setVelocity(swap);*/

							if( pair.second != Vector2f(0,0) ) {

							//get the components of the velocity vectors which are parallel to the collision
							float magnitude = sqrtf((pair.second.x * pair.second.x) + (pair.second.y * pair.second.y));
							Vector2f normMTV(pair.second / magnitude);

							//dot product
							float aci = (itr->getVelocity().x * normMTV.x) + (itr->getVelocity().y * normMTV.y);
							float bci = (itr2->getVelocity().x * normMTV.x) + (itr2->getVelocity().y * normMTV.y);

							itr->setVelocity(itr->getVelocity() + (bci - aci) * normMTV);
							itr2->setVelocity(itr2->getVelocity() + (aci - bci) * normMTV);
							}
						}

						//add IDs to appropriate lists so that we don't check for collision again.
						itr->setCollisionTested(itr2->getID());
						itr2->setCollisionTested(itr->getID());
					}//if(distance)
				}//if(itr!=itr2)
			}//itr2 loop

			//update and draw each thing
			itr->Update(window);
			itr->Draw(window);
		}//itr loop

		//tryHard.Update(window);
		//tryHard.Draw(window);

		//calculate framerate
		refreshes++;
		framerate += 1.f / clock.getElapsedTime().asSeconds();
		text.setString("Framerate: " + to_string(framerate / refreshes));
		clock.restart();

		// Finally, display rendered frame on screen
		window.display();

	} //loop back for next frame
	return EXIT_SUCCESS;
}