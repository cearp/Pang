#include "stdafx.h"
#include "Paddle.h"

#ifndef _BALL_H_
#define _BALL_H_

#pragma once
class Ball
{
public:
	Ball();
	~Ball();

	Ball(float radius, sf::Color color, const char *sound);//ball class

	void initBallPos(sf::Vector2f position);//reset ball position.
	void resetBallSpeed(int sign);// reset the speed of ball.

	void bounceX(float xDir);//reverse direction from collision.
	void bounceY(float yDir);

	// play collision sound
	void playHitSound();

	void move();//Move the ball.
	void accelerate(Paddle player);//Acceleration from collision
	void Stop();// stop moving the ball

	// detect collision
	bool isColliding(sf::RectangleShape rectangle);
	bool isColliding(sf::FloatRect rect);


	sf::Vector2f getBallPosition();// get ball position

	float getBallRadius();// get ball radius

	void update(sf::RenderWindow &WINDOW);//draw to the screen.

	static float BALL_RADIUS;
	static sf::Color BALL_COLOR;
	static sf::Vector2f BALL_POS;


private:
	sf::CircleShape ballObject;//ball game object.
	sf::Vector2<float> ballSpeed;//stores the ball's speed.
	sf::Sound soundPaddleHit;//stores audio
	sf::SoundBuffer paddleHit; //stores audio file
};
#endif
