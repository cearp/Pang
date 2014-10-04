#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#ifndef _GAME_H_
#define _GAME_H_

//Main Game class. Creates a global interface using static variables.
class Game
{
public:
	Game(){};
	~Game(){};

	static void Start();//starts the game, called in main.
	//Shapes for borders
	static sf::RectangleShape TOP;
	static sf::RectangleShape BOTTOM;
	static sf::RectangleShape LEFT;
	static sf::RectangleShape RIGHT;
	//dividing line
	static sf::RectangleShape LINE;
	//Dimensions
	static unsigned int SCREEN_HEIGHT; 
	static unsigned int SCREEN_LENGTH;
	//score
	static int player1score, player2score;


private:
	static bool IsExiting();//Checks if the game is exitng
	static void GameLoop();//The main game loop, updates the screen.
	static void ShowSplashScreen();//What it says...
	static void Draw();
	static void SetVariables();
	static void collisions();
	static void movement();
	static void score();
	static void playerUpdate();

	enum GameState { Uninitialized, ShowingSplash, GameOver, Playing, Exiting };

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;

	static float _angle;
	static float _velocity;

};
#endif
