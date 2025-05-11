#include "sprite.h"
#include "raylib.h"
#include <iostream>
#include <string>
using namespace std;

void Sprite::setDirection(Vector2 newDirection)
{
    direction = newDirection;
}
Vector2 Sprite::getPosition()
{
    return position;
}
void Sprite::setSpeed(int newSpeed)
{
    speed = newSpeed;
}
void Sprite::setPosition(Vector2 newPosition)
{
    position = newPosition;
}
void Sprite::updatePosition(Vector2 newPosition)
{
    position = newPosition;
}

Texture2D Sprite::getSpriteImage()
{
    return spriteImage;
}

Vector2 Sprite::getDirection()
{
    return direction;
}

void Sprite ::draw()
{
    DrawTexture(spriteImage, position.x, position.y, WHITE);
}

int Sprite::getSpeed()
{
    return speed;
}