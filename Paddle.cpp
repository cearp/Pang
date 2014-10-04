#include "stdafx.h"
#include "Paddle.h"

int PaddleSpeed = 140.0f;

Paddle::Paddle(int w, int h, sf::Color c)
{
    paddleObject.setSize(sf::Vector2f(w, h));
    paddleObject.setFillColor(c);
}

void Paddle::initPadPos(sf::Vector2f pos)
{
    paddleObject.setPosition(pos);
}

void Paddle::setPadPos(sf::Vector2f pos)
{
    paddleObject.setPosition(pos);
}

sf::FloatRect Paddle::getRect()
{
    return paddleObject.getGlobalBounds();
}

//moves the paddle up
void Paddle::up(float dt)
{

    paddleObject.move(0, -PaddleSpeed * dt);

}

//moves the paddle down
void Paddle::down(float dt)
{
    paddleObject.move(0, PaddleSpeed * dt);
}

bool Paddle::isColliding(sf::RectangleShape rectangle)
{
    if(paddleObject.getGlobalBounds().intersects(rectangle.getGlobalBounds()))
        return true;
    return false;
}
sf::Vector2f Paddle::getPaddlePosition()
{
    return paddleObject.getPosition();
}

sf::Vector2f Paddle::getPaddleSize()
{
    return paddleObject.getSize();
}

//Draws paddle to the screen

void Paddle::update(sf::RenderWindow &renderWindow)
{
    renderWindow.draw(paddleObject);
}


Paddle::~Paddle(){}//dtor