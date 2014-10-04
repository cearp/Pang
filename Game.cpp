#include "stdafx.h"
#include "Game.h"
#include "SplashScreen.h"
#include "Ball.h"
#include "Paddle.h"


//Because these are static, the need to be initialized outside the class.
//Static variables need to instanced manually, and why not initialize it.
Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
//Colors
sf::Color white(255,255,255);
sf::Color grey(100,100,100);
sf::Color blue(255,100,100);
sf::Color red(100,100,255);
sf::Color kindablue(100,100,255);
sf::Color kindapink(255,100,100);
sf::Color kindagreen(100,255,100);
//Borders
sf::RectangleShape Game::TOP;
sf::RectangleShape Game::BOTTOM;
sf::RectangleShape Game::LEFT;
sf::RectangleShape Game::RIGHT;
sf::RectangleShape Game::LINE;
//resolution
unsigned int Game::SCREEN_HEIGHT = 400; 
unsigned int Game::SCREEN_LENGTH = 640;
float Ball::BALL_RADIUS;
sf::Color Ball::BALL_COLOR;
sf::Vector2f Ball::BALL_POS;
int Game::player1score;
int Game::player2score;
int padWidth = 20;
int padHeight = 50;
//paddle init
Paddle player1(padWidth,padHeight,kindagreen);//right
Paddle player2(padWidth,padHeight,kindapink);//left
Paddle player1rev(padWidth,padHeight,kindagreen);
Paddle player2rev(padWidth,padHeight,kindapink);
//ball stuff
Ball ball(10,white,"pong.wav");
bool ballMoving;//the ball is in play
bool ballGoal;//someone havs scored a point, ball needs to reset.
sf::Vector2f ballPos(Game::SCREEN_LENGTH / 2-5, Game::SCREEN_HEIGHT / 2);
//clock for paddles movment and speed.
sf::Clock Clock;
float tcur;
float tprev;
float timeDelta;

int random;
float Game::_angle;
float Game::_velocity;

void Game::Start(void)
{
		player1score = 0;
	player2score = 0;
	SetVariables();

	//We check that the game state is uninitialized so that we do not call it more than once.
	if(_gameState != Uninitialized)//Throwing an error would be proper
		return;

	_mainWindow.create(sf::VideoMode(SCREEN_LENGTH,SCREEN_HEIGHT,32),"Pang!");//Creates the resolutions, 32bpp color, and title.
	_gameState= Game::ShowingSplash;//Title screen

	while(!IsExiting())//While the game is in play mode, we run the gameloop.
	{
		GameLoop();//repeats as long as we're not in exit mode.
	}

	_mainWindow.close();//Closes the window when not in play mode.
}

bool Game::IsExiting()//Checks if the game state is in exit mode.
{
	if(_gameState == Game::Exiting) 
		return true;
	else 
		return false;
}


void Game::SetVariables()
{
	random = 1;
	timeDelta=tprev=tcur=0.0f;
	//Initialize paddle positions 
	player1.initPadPos(sf::Vector2f(SCREEN_LENGTH-50,SCREEN_HEIGHT/2-padHeight/2));
	player2.initPadPos(sf::Vector2f(30,SCREEN_HEIGHT/2-padHeight/2));
	player1rev.initPadPos(sf::Vector2f(SCREEN_LENGTH-50,SCREEN_HEIGHT/2-padHeight/2));
	player2rev.initPadPos(sf::Vector2f(30,SCREEN_HEIGHT/2-padHeight/2));
	//Ball stuff
	ballMoving = true;
	ballGoal = false;
	Ball::BALL_RADIUS = 5.0f;
	Ball::BALL_COLOR = white;
	ball.initBallPos(ballPos);
	//Border size
	TOP.setSize(sf::Vector2f(SCREEN_LENGTH,10));
	BOTTOM.setSize(sf::Vector2f(SCREEN_LENGTH,10));
	LEFT.setSize(sf::Vector2f(10, SCREEN_LENGTH));
	RIGHT.setSize(sf::Vector2f(10, SCREEN_HEIGHT));
	LINE.setSize(sf::Vector2f(10, SCREEN_HEIGHT));
	//Border color
	TOP.setFillColor(white);
	BOTTOM.setFillColor(white);
	LEFT.setFillColor(white);
	RIGHT.setFillColor(white);
	LINE.setFillColor(grey);
	//Border position
	TOP.setPosition(sf::Vector2f(0,-10));
	BOTTOM.setPosition(sf::Vector2f(0,SCREEN_HEIGHT));
	LEFT.setPosition(sf::Vector2f(-10,0));
	RIGHT.setPosition(sf::Vector2f(SCREEN_LENGTH,0));
	LINE.setPosition(sf::Vector2f(SCREEN_LENGTH / 2, 0));
}

void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);
	_gameState = Game::Playing;
}
void Game::playerUpdate()
{
	_mainWindow.clear(sf::Color(0,0,0));//Clears the stuff drawn to the screen.
	//draws the borders slightly out of frame.
	_mainWindow.draw(LINE);
	_mainWindow.draw(TOP);
	_mainWindow.draw(BOTTOM);
	_mainWindow.draw(LEFT);
	_mainWindow.draw(RIGHT);

	player1.update(_mainWindow);//update to the screen
	player2.update(_mainWindow);
	player1rev.update(_mainWindow);//update to the screen
	player2rev.update(_mainWindow);

}

void Game::Draw()
{
	//SFML is a polling based system, This is why we call pollEvent. 
	//If there is an event, it returns true, and is set equall to currentEvent.
	if(player1score > 9)
	{
		cout<<"Player 1 Wins!!! "<<endl;
		_gameState = GameOver;
	}
		if(player2score > 9)
	{
		cout<<"Player 2 Wins!!! "<<endl;
		_gameState = GameOver;
	}
	sf::Event event;
	while(ballMoving && !ballGoal){
		//cout<<"ball moving"<<endl;
		_mainWindow.clear(sf::Color(0,0,0));//Clears the stuff drawn to the screen.
		ball.move();
		playerUpdate();
		ball.update(_mainWindow);
		collisions();//check collisions with the ball.
		//		playerUpdate();
		_mainWindow.display();


		while(_mainWindow.pollEvent(event))
		{


			movement();//Update the movement of the paddles
			playerUpdate();
			ball.update(_mainWindow);
			_mainWindow.display();
			switch(event.type)
			{
			case sf::Event::Closed:
				_gameState = Game::Exiting;
				break;

			}

		}
	}

}

void Game::score()
{
	sf::Font textFont;
	textFont.loadFromFile("Fonts/BankGothic.ttf");
	//int score1,score;
	//Game::player1score =score1;
	sf::Text Score("0 0", textFont, 50);
	Score.setColor(sf::Color(100,100,100));
	Score.setPosition(sf::Vector2f(SCREEN_LENGTH / 2 - 68, 20)) ;
}

void Game::collisions()//Just a place to put all the collision checking 
{
	//float speed = 24;//((player1score + player2score)+1)/2;
	_angle = rand()%360;//random angle

	if(ball.isColliding(player1.getRect()))//right
	{
		ball.playHitSound();
		ball.bounceX(1);
		ball.bounceY(1);
		ball.accelerate(player1);
	}
	if(ball.isColliding(player2.getRect()))//left
	{
		ball.playHitSound();
		ball.bounceX(1);
		ball.bounceY(1);
		ball.accelerate(player1);
	}
	//Reverse moving paddles
	if(ball.isColliding(player1rev.getRect()))
	{
		ball.playHitSound();
		ball.bounceX(1);
		ball.bounceY(1);
		ball.accelerate(player1rev);
	}
	if(ball.isColliding(player2rev.getRect()))
	{
		ball.playHitSound();
		ball.bounceX(1);
		ball.bounceY(1);
		ball.accelerate(player1rev);
	}
	if(ball.isColliding(TOP.getGlobalBounds()))//Hits the top 
	{
		ball.playHitSound();
		ball.bounceX(-1);
		ball.bounceY(1);
	}
	if(ball.isColliding(BOTTOM.getGlobalBounds()))//Hits bottom
	{
		ball.playHitSound();
		ball.bounceX(-1);
		ball.bounceY(1);
	}
	if(ball.isColliding(LEFT.getGlobalBounds()))//Check if player1 scores
	{
		player1score++;
		ballMoving = false;
		ballGoal = true;
		ball.initBallPos(ballPos);
		ball.resetBallSpeed(random * (-1));
		SetVariables();
		cout<<"Player1 Score: "<<player1score<<"Player2 Score: "<<player2score<<endl;
	}
	if(ball.isColliding(RIGHT.getGlobalBounds()))//Check if player2 scores
	{
		player2score++;
		ballMoving = false;
		ballGoal = true;
		ball.initBallPos(ballPos);
		ball.resetBallSpeed(random * (-1));
		SetVariables();
		cout<<"Player1 Score: "<<player1score<<"  Player2 Score: "<<player2score<<endl;
	}
	//cout<<"Player1 Score: "<<player1score<<"Player2 Score: "<<player2score<<endl;
}
void Game::movement()//players movement with keyboard
{
	//User clock used for getting the elapsed time for the update of movement.
	//tcur = Clock.getElapsedTime().asSeconds();
	//timeDelta = tcur - tprev; 
	//tprev = tcur;
	timeDelta = 0.123;
	//Player 1 controlls 'UP' & 'DOWN'
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		if(player1.getPaddlePosition().y  > 0)
			player1.up(timeDelta);
		if(player1rev.getPaddlePosition().y  < SCREEN_HEIGHT-padHeight)
			player1rev.down(timeDelta);
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		if(player1.getPaddlePosition().y  < SCREEN_HEIGHT-padHeight)
			player1.down(timeDelta);
		if(player1rev.getPaddlePosition().y  > 0)
			player1rev.up(timeDelta);
	}

	//Player 2  controlls 'w' & 's'
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
		if(player2.getPaddlePosition().y  > 0)
			player2.up(timeDelta);
		if(player2rev.getPaddlePosition().y  < SCREEN_HEIGHT-padHeight)
			player2rev.down(timeDelta);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		if(player2.getPaddlePosition().y  < SCREEN_HEIGHT-padHeight)
			player2.down(timeDelta);
		if(player2rev.getPaddlePosition().y  > 0)
			player2rev.up(timeDelta);
	}
	//cout<<player1.getPaddlePosition().y<<","<<player1.getPaddlePosition().x<<endl;
	//cout<<player2.getPaddlePosition().y<<","<<player2.getPaddlePosition().x<<endl;
	//cout<<timeDelta<<endl;

}

void Game::GameLoop()
{
	switch(_gameState)
	{
	case Game::ShowingSplash:
		{
			ShowSplashScreen();
			break;
		}
	case Game::Playing:
		{
			Draw();

			break;
		}
	case Game::GameOver:
		{
			cout<<"Play AGAIN!"<<endl;
			Game::Start();
		}
	}
}


