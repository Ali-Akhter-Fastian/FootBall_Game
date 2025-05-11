#include "goalie.h"
#include "raylib.h"
#include "player.h"
#include <iostream>
#include <string>

using namespace std;

int Goalie::setMinHeight(int minHeight)
{
    this->minHeight = minHeight;
    return minHeight;
}
int Goalie::setMaxHeight(int maxHeight)
{
    this->maxHeight = maxHeight;
    return maxHeight;
}
void Goalie::update(Ball *ball, int horizontalLimit, int verticalLimit)
{
    if (direction.y == 1)
    {
        position.y += speed;
    }
    else if (direction.y == -1)
    {
        position.y -= speed;
    }
    if (position.y < minHeight)
    {
        position.y = minHeight;
        direction.y = 1;
    }
    else if (position.y > maxHeight)
    {
        position.y = maxHeight;
        direction.y = -1;
    }
    if (CheckCollisionRecs({position.x, position.y, float(spriteImage.width), float(spriteImage.height)}, {ball->getPosition().x, ball->getPosition().y, float(ball->getSpriteImage().width), float(ball->getSpriteImage().height)}))
    {
        ball->setDirection({-(ball->getDirection().x), direction.y});
        ball->setSpeed(ball->getSpeed() + 5);
    }
}

int Goalie::getMinHeight()
{
    return minHeight;
}

int Goalie::getMaxHeight()
{
    return maxHeight;
}