#include "stdafx.h"

#ifndef _PADDLE_H_
#define _PADDLE_H_

class Paddle
{
    public:
		
        // parameterized ctor to initialize as per user's input
		Paddle(int width, int height, sf::Color color);

        // reset paddle position
        void initPadPos(sf::Vector2f pos);

        // set paddle position
        void setPadPos(sf::Vector2f pos);

        sf::FloatRect getRect();
        
        void up(float dt);// move the paddle up
        void down(float dt);

        bool isColliding(sf::RectangleShape rectangle);// detect collision

        sf::Vector2f getPaddlePosition();
        sf::Vector2f getPaddleSize();

		void setPaddleSpeed(int x){paddleSpeed = x;}

        void update(sf::RenderWindow &renderWindow);//draw paddle to screen

        
        ~Paddle();// dctor

	private:
        sf::RectangleShape paddleObject;//Game paddle object
		int paddleSpeed;
};
#endif
