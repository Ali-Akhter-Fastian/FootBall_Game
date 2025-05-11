#include "player.h"
#include "raylib.h"
#include "sprite.h"
#include <iostream>
#include <string>

using namespace std;

void Player::update(int horizontalLimit, int verticalLimit)
{

    if (IsKeyDown(controlsKey[0]) && IsKeyDown(controlsKey[2]))
    {
        position.x -= speed / 1.5;
        position.y -= speed / 1.5;
        direction = {-1.0, -1.0}; // up left
    }
    else if (IsKeyDown(controlsKey[0]) && IsKeyDown(controlsKey[3]))
    {
        position.x += speed / 1.5;
        position.y -= speed / 1.5;
        direction = {1.0, -1.0}; // up right
    }
    else if (IsKeyDown(controlsKey[1]) && IsKeyDown(controlsKey[2]))
    {
        position.x -= speed / 1.5;
        position.y += speed / 1.5;
        direction = {-1.0, 1.0}; // down left
    }
    else if (IsKeyDown(controlsKey[1]) && IsKeyDown(controlsKey[3]))
    {
        position.x += speed / 1.5;
        position.y += speed / 1.5;
        direction = {1.0, 1.0}; // down right
    }
    else if (IsKeyDown(controlsKey[0]))
    {
        position.y -= speed;
        direction = {0.0, -1.0}; // up
    }
    else if (IsKeyDown(controlsKey[1]))
    {
        position.y += speed;
        direction = {0.0, 1.0}; // down
    }
    else if (IsKeyDown(controlsKey[2]))
    {
        position.x -= speed;
        direction = {-1.0, 0.0}; // left
    }
    else if (IsKeyDown(controlsKey[3]))
    {
        position.x += speed;
        direction = {1.0, 0.0}; // right
    }
    Image temp;
    if (type == "blue"){
        temp = LoadImage("images/playerBlue.png");
        if (temp.width == 0 || temp.height == 0) {
                throw runtime_error("Failed to load BluePlayer image: images/playerBlue.png");
            }
    }
    else{
        temp = LoadImage("images/playerRed.png");
        if (temp.width == 0 || temp.height == 0) {
                throw runtime_error("Failed to load BluePlayer image: images/playerBlue.png");
            }
    }
    if (direction.x == 0.0 && direction.y == 1.0)
    {
        ImageRotate(&temp, 90.0f);
    }
    if (direction.x == 0.0 && direction.y == -1.0)
    {
        ImageRotate(&temp, 270.0f);
    }
    if (direction.x == -1.0 && direction.y == 0.0)
    {
        ImageRotate(&temp, 180.0f);
    }
    if (direction.x == 1.0 && direction.y == 0.0)
    {
        ImageRotate(&temp, 0.0f);
    }
    if (direction.x == -1.0 && direction.y == -1.0)
    {
        ImageRotate(&temp, 225.0f);
    }
    if (direction.x == 1.0 && direction.y == -1.0)
    {
        ImageRotate(&temp, 315.0f);
    }
    if (direction.x == -1.0 && direction.y == 1.0)
    {
        ImageRotate(&temp, 135.0f);
    }
    if (direction.x == 1.0 && direction.y == 1.0)
    {
        ImageRotate(&temp, 45.0f);
    }
    if (position.x < horizontalLimit)
        position.x = horizontalLimit;
    if (position.x > GetScreenWidth() - spriteImage.width - horizontalLimit)
        position.x = GetScreenWidth() - spriteImage.width - horizontalLimit;
    if (position.y < verticalLimit)
        position.y = verticalLimit;
    if (position.y > GetScreenHeight() - spriteImage.height - verticalLimit)
        position.y = GetScreenHeight() - spriteImage.height - verticalLimit;
    // Unload the previous texture before loading a new one
    UnloadTexture(spriteImage);
    spriteImage = LoadTextureFromImage(temp);
     if (spriteImage.id == 0) {
            throw runtime_error("Failed to create texture from image");
    }
    UnloadImage(temp);
}