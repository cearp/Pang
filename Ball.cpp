#include "stdafx.h"
#include "Ball.h"


sf::Vector2<float> Speed(0.5, 0.5);     

Ball::Ball(float radius, sf::Color color, const char *sound)
{
    ballObject.setRadius(radius);
    ballObject.setFillColor(color);
	paddleHit.loadFromFile(sound);
}

Ball::~Ball(){}//dtor


void Ball::initBallPos(sf::Vector2f pos)
{

    ballObject.setPosition(pos);
    ballSpeed = Speed;
}

void Ball::resetBallSpeed(int sign)
{
    ballSpeed = Speed;
    Speed.x = Speed.x * sign;
    Speed.y = Speed.y * sign;
}

void Ball::bounceX(float xDir)
{
	ballSpeed.x = ballSpeed.x*xDir;
	ballSpeed.x =- ballSpeed.x;
}
void Ball::bounceY(float yDir)
{
	ballSpeed.y = ballSpeed.y*yDir;
	ballSpeed.y =- ballSpeed.y;
}

void Ball::move(){   ballObject.move(ballSpeed.x,ballSpeed.y);}

void Ball::accelerate(Paddle player)
{
    ballSpeed.y = (ballObject.getGlobalBounds().top
                   + ballObject.getGlobalBounds().height/2
                   - player.getRect().top
                   - player.getRect().height/2)/100;
}

void Ball::Stop(){ballSpeed = sf::Vector2<float>(0.0f, 0.0f);}

void Ball::playHitSound(){soundPaddleHit.play();}

bool Ball::isColliding(sf::RectangleShape rectangle)
{
    if(ballObject.getGlobalBounds().intersects(rectangle.getGlobalBounds())) return true;
    return false;
}
bool Ball::isColliding(sf::FloatRect rect)
{
    if(ballObject.getGlobalBounds().intersects(rect)) return true;
    return false;
}

        
sf::Vector2f Ball::getBallPosition(){return ballObject.getPosition();}
        
float Ball::getBallRadius(){return ballObject.getRadius();}

void Ball::update(sf::RenderWindow &renderWindow){renderWindow.draw(ballObject);}



