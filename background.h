#ifndef background_h
#define background_h

#include "raylib.h"
#include<stdexcept>
class Background
{
    Texture2D stadium;
    Texture2D goalLeft;
    Texture2D goalRight;

public:
    Background() {}
    Background(const float screenWidth, const float screenHeight)
    {   try{
        Image temp = LoadImage("images/ground.jpg");
        if (temp.width == 0 || temp.height == 0) {
            throw runtime_error("Failed to load stadium image: images/ground.jpg");
        }
        ImageResize(&temp, (int)screenWidth, (int)screenHeight);
        stadium = LoadTextureFromImage(temp);
         if (stadium.id == 0) {
            throw runtime_error("Failed to load stadium texture.");
        }
        temp = LoadImage("images/goalL.png");
         if (temp.width == 0 || temp.height == 0) {
            throw runtime_error("Failed to load left goal image: images/goalL.png");
        }
        ImageResize(&temp, 80, 130);
        goalLeft = LoadTextureFromImage(temp);
          if (goalLeft.id == 0) {
            throw runtime_error("Failed to load left goal texture.");
        }
        temp = LoadImage("images/goalR.png");
       if (temp.width == 0 || temp.height == 0) {
            throw runtime_error("Failed to load right goal image: images/goalR.png");
        }
        ImageResize(&temp, 80, 130);
        goalRight = LoadTextureFromImage(temp);
        if (goalRight.id == 0) {
            throw runtime_error("Failed to load right goal texture.");
        }
        UnloadImage(temp); // Unload the image after loading the texture
    }
     catch (const runtime_error& e) {
        cerr << "Error in Background constructor: " << e.what() << endl;
        throw; // Rethrow to handle it at the higher level if needed
    }
    }
    ~Background()
    {
        UnloadTexture(stadium);
        UnloadTexture(goalLeft);
        UnloadTexture(goalRight);
    }
    void loadBackground(const float screenWidth, const float screenHeight);
};

#endif