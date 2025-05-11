#include "background.h"
#include "raylib.h"
#include<stdexcept>
#include <iostream>
using namespace std;

void Background::loadBackground(const float screenWidth, const float screenHeight)
{
            if (stadium.id == 0 || goalLeft.id == 0 || goalRight.id == 0) {
        throw runtime_error("Cannot draw: one or more textures are invalid.");
        }

        DrawTexture(stadium, 0, 0, WHITE);
        DrawTexture(goalLeft, 0, 335, WHITE);
        DrawTexture(goalRight, screenWidth - 80, 335, WHITE);
}