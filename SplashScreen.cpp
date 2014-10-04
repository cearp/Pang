#include "stdafx.h"
#include "SplashScreen.h"

//Main implementation file for the title screen.
void SplashScreen::Show(sf::RenderWindow & renderWindow)
{
	sf::Texture SplashImage;//create a texture and load it in.
	//checks if the image exist and loads it in, otherwise it returns.
	if(!SplashImage.loadFromFile("SplashScreen.png"))
		return;

	sf::Sprite sprite;
	sprite.setTexture(SplashImage);//Converts the texture to a sprite so we can use it.
	renderWindow.draw(sprite);//Draws the title screen to to the window. 
	renderWindow.display();//Displays it to the screen.
	//Don't need to set coordinates, same resolution as the screen.

	sf::Event event;//We use this event to look for any input from the user (mouse click/button pressed/exit)

	while(true)//loops until it can return.
	{
		while(renderWindow.pollEvent(event))//This loop draws the splash  screen until it polls an event.
		{
			if(event.type == sf::Event::Closed) renderWindow.close();
			if(event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed)	
			{
				cout<<"Welcome To Pang, A Pong Clone!"<<endl;
				return;//ends the loop.
			}
		}
	}
}