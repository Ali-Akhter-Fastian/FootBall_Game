#ifndef sprite_h
#define sprite_h

#include "raylib.h"
#include <iostream>
#include <iostream>
#include <string>
using namespace std;
class Sprite
{
protected:
    string type;           // team type
    Texture2D spriteImage; // Image of the sprite
    Vector2 position;      // Position of the sprite
    int speed;             // Speed of the sprite
    Vector2 direction;     // Direction of the sprite
public:
    Sprite()
    {
        position = {0.0, 0.0};
        speed = 0;
    }
    virtual Vector2 getDirection();
    virtual Vector2 getPosition();
    int getSpeed();
    virtual void setDirection(Vector2 newDirection);
    virtual Texture2D getSpriteImage();
    virtual void setSpeed(int);
    virtual void updatePosition(Vector2);
    virtual void draw();
    virtual void setPosition(Vector2);
    virtual void update(int, int) = 0; // pure virtual function
};

#endif