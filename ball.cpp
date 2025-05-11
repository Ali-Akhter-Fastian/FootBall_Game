#include "ball.h"
#include "player.h"
#include <iostream>
#include "raylib.h"
using namespace std;

void Ball ::checkPlayerCollision(Player *player1, Player *player2)
{
    if (CheckCollisionRecs({position.x, position.y, float(spriteImage.width), float(spriteImage.height)}, {player1->getPosition().x, player1->getPosition().y, float(player1->getSpriteImage().width), float(player1->getSpriteImage().height)}))
    {
        player = player1;
    }
    else if (CheckCollisionRecs({position.x, position.y, float(spriteImage.width), float(spriteImage.height)}, {player2->getPosition().x, player2->getPosition().y, float(player2->getSpriteImage().width), float(player2->getSpriteImage().height)}))
    {
        player = player2;
    }
    else
        player = nullptr; // reset player if no collision
}

bool Ball ::isKicked()
{
    if (player != nullptr)
    {
        if (IsKeyDown(player->kickKey))
        {
            return true;
        }
    }
    return false;
}
void Ball::update(Player *player1, Player *player2, int horizontalLimit, int verticalLimit)
{
    checkPlayerCollision(player1, player2);

    if (isKicked())
    {
        PlaySound(kickSound); // Play kick sound
        if (player)
        {
            speed = player->kickPower;
        }
        player = nullptr; // Reset player after kick
    }

    if (player)
    {
        // Ball is attached to the player
        if (!isKicked())
        {
            // Place the ball in front of the player
            if (player->getDirection().x == 0 || player->getDirection().y == 0 || (player->getDirection().x == 1 && player->getDirection().y == 1))
            {
                position.x = player->getPosition().x + player->getDirection().x * 20 + 5; // Adjust offset as needed
                position.y = player->getPosition().y + player->getDirection().y * 20 + 5; // Adjust offset as needed
            }
            else
            {
                position.x = player->getPosition().x + player->getDirection().x * 10 + 5; // Adjust offset as needed
                position.y = player->getPosition().y + player->getDirection().y * 10 + 5; // Adjust offset as needed
            }
        }

        // Update direction based on player's direction
        direction = player->getDirection();
    }
    else
    {
        // Ball is not attached to any player
        speed -= groundResistance;
        if (speed < 0)
            speed = 0; // Prevent negative speed
    }

    // Update ball position based on direction and speed
    float diagonalSpeed = speed / 1.414f; // Approximation of 1/sqrt(2) for diagonal movement
    if (direction.x == 1 && direction.y == 0)
    {
        position.x += speed;
    }
    else if (direction.x == -1 && direction.y == 0)
    {
        position.x -= speed;
    }
    else if (direction.x == 0 && direction.y == 1)
    {
        position.y += speed;
    }
    else if (direction.x == 0 && direction.y == -1)
    {
        position.y -= speed;
    }
    else if (direction.x == -1 && direction.y == -1)
    {
        position.x -= diagonalSpeed;
        position.y -= diagonalSpeed;
    }
    else if (direction.x == -1 && direction.y == 1)
    {
        position.x -= diagonalSpeed;
        position.y += diagonalSpeed;
    }
    else if (direction.x == 1 && direction.y == -1)
    {
        position.x += diagonalSpeed;
        position.y -= diagonalSpeed;
    }
    else if (direction.x == 1 && direction.y == 1)
    {
        position.x += diagonalSpeed;
        position.y += diagonalSpeed;
    }

    // Ensure position stays within screen bounds
    if (position.x < horizontalLimit)
        position.x = horizontalLimit;
    if (position.x > GetScreenWidth() - spriteImage.width - horizontalLimit)
        position.x = GetScreenWidth() - spriteImage.width - horizontalLimit;
    if (position.y < verticalLimit)
        position.y = verticalLimit;
    if (position.y > GetScreenHeight() - spriteImage.height - verticalLimit)
        position.y = GetScreenHeight() - spriteImage.height - verticalLimit;
}
