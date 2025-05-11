#include <iostream>
#include "raylib.h"
#include "ball.h"
#include "background.h"
#include "player.h"
#include "goalie.h"
#include "footballgame.h"
using namespace std;
int main()
{
    // Initialize the game
    const float SCREEN_WIDTH = 1500;
    const float SCREEN_HEIGHT = 800;
    try{

        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Football Game");
        InitAudioDevice(); // Initialize audio device
        FootballGame game;
        game.simulateGame();
    }catch (const std::exception& e) {
        cerr << "Unhandled exception: " << e.what() << endl;
    } catch (...) {
        cerr << "An unknown error occurred." << endl;
    }

    return 0;
    // const int horizontalLimit = 55;
    // const int verticalLimit = 50;
    // InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Head Football Game");
    // SetTargetFPS(60);
    // // Making object of Ball and initializing it
    // Background background(SCREEN_WIDTH, SCREEN_HEIGHT);
    // Ball football;
    // Player player1("blue");
    // Player player2("red");
    // Goalie goalie1("blue");
    // Goalie goalie2("red");
    // goalie1.setMinHeight(320);
    // goalie1.setMaxHeight(450);
    // goalie2.setMinHeight(320);
    // goalie2.setMaxHeight(450);
    // goalie1.setPosition({80, SCREEN_HEIGHT / 2.0});
    // goalie2.setPosition({SCREEN_WIDTH - 100, SCREEN_HEIGHT / 2.0});
    // player1.setPosition({SCREEN_WIDTH / 2.0 - 100, SCREEN_HEIGHT / 2.0});
    // player2.setPosition({SCREEN_WIDTH / 2.0 + 100, SCREEN_HEIGHT / 2.0});
    // player1.setSpeed(3);
    // player2.setSpeed(3);
    // football.updatePosition({SCREEN_WIDTH / 2.0 - 7, SCREEN_HEIGHT / 2.0 - 7});
    // while (WindowShouldClose() == false)
    // {
    //     BeginDrawing();
    //     ClearBackground(WHITE);
    //     background.loadBackground(SCREEN_WIDTH, SCREEN_HEIGHT);
    //     player1.update(horizontalLimit, verticalLimit);
    //     player2.update(horizontalLimit, verticalLimit);
    //     football.update(&player1, &player2, horizontalLimit, verticalLimit);
    //     goalie1.update(&football, horizontalLimit, verticalLimit);
    //     goalie2.update(&football, horizontalLimit, verticalLimit);
    //     goalie1.draw();
    //     goalie2.draw();
    //     football.draw();
    //     player1.draw();
    //     player2.draw();
    //     EndDrawing();
    // }
    // CloseWindow();
}