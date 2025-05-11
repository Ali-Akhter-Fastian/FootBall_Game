#include "footballgame.h"
#include "raylib.h"
#include "ball.h"
#include "background.h"
#include "player.h"
#include "goalie.h"
#include <iostream>
#include <fstream>
#include <string>
#include<stdexcept>
using namespace std;

bool flag = false;
string highestGoalScored = "\t\tNEW RECORD\nHighest Goal Scored: ";

void FootballGame::resetPositons()
{
    ((Player *)entities[0])->setPosition({float(SCREEN_WIDTH / 2.0 - 100), float(SCREEN_HEIGHT / 2.0)});
    ((Player *)entities[1])->setPosition({float(SCREEN_WIDTH / 2.0 + 100), float(SCREEN_HEIGHT / 2.0)});
    ((Player *)entities[1])->setDirection({-1.0, 0.0});
    ((Player *)entities[0])->setDirection({1.0, 0.0});
    ((Goalie *)entities[2])->setDirection({0.0, 1.0});
    ((Goalie *)entities[3])->setDirection({0.0, -1.0});
    ((Ball *)entities[4])->setDirection({0.0, 0.0});
    ((Ball *)entities[4])->setSpeed(0);
    ((Goalie *)entities[2])->setPosition({80, float(SCREEN_HEIGHT / 2.0)});
    ((Goalie *)entities[3])->setPosition({float(SCREEN_WIDTH - 100), float(SCREEN_HEIGHT / 2.0)});
    ((Ball *)entities[4])->updatePosition({float(SCREEN_WIDTH / 2.0 - 7), float(SCREEN_HEIGHT / 2.0 - 7)});
}

void FootballGame::simulatePausedScreen()
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(GREEN);
        DrawText("Game Paused", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 150, 50, BLACK);
        DrawText("Press Esc to continue", SCREEN_WIDTH / 2 - 300, SCREEN_HEIGHT / 2 + 20, 50, BLACK);
        EndDrawing();
    }
}

void FootballGame::pauseForGoal(int limit)
{
    int delay = 0;
    while (delay < limit * 60)
    {
        BeginDrawing();
        ClearBackground(WHITE);
        background.loadBackground(SCREEN_WIDTH, SCREEN_HEIGHT);
        for (int i = 0; i < 5; i++)
        {
            entities[i]->draw();
        }
        DrawText(TextFormat("%d - %d", score[0], score[1]), SCREEN_WIDTH / 2.0 - 50, 10, 45, WHITE);
        DrawText(TextFormat("Time: %d", timeElapsed / 60), SCREEN_WIDTH / 2.0 - 30, SCREEN_HEIGHT - 35, 30, WHITE);
        EndDrawing();
        delay++;
    }
}

void FootballGame::isGoaled()
{
    ifstream inFile("highscore.txt");
    int highScore = 0;
    if (inFile)
        inFile >> highScore;
    inFile.close();

    if (((Ball *)entities[4])->getPosition().x <= horizontalLimit &&
        ((Ball *)entities[4])->getPosition().y >= ((Goalie *)entities[2])->getMinHeight() &&
        ((Ball *)entities[4])->getPosition().y <= ((Goalie *)entities[2])->getMaxHeight())
    {
        score[1]++;
        if (score[1] > highScore)
        {
            ofstream outFile("highscore.txt", ios::trunc);
            outFile << score[1];
            outFile.close();
            flag = true;
            highestGoalScored = "\t\tNEW RECORD\nHighest Goal Scored: " + to_string(score[1]);
        }
        PlaySound(goalSound);
        DrawText("GOOAAALLL",SCREEN_WIDTH/2,SCREEN_HEIGHT/3,50,BLACK);
        pauseForGoal(3.5);
        resetPositons();
    }
    else if (((Ball *)entities[4])->getPosition().x >= SCREEN_WIDTH - horizontalLimit - ((Ball *)entities[4])->getSpriteImage().width &&
    ((Ball *)entities[4])->getPosition().y >= ((Goalie *)entities[3])->getMinHeight() &&
    ((Ball *)entities[4])->getPosition().y <= ((Goalie *)entities[3])->getMaxHeight())
    {
        score[0]++;
        if (score[0] > highScore)
        {
            ofstream outFile("highscore.txt", ios::trunc);
            outFile << score[0];
            outFile.close();
            flag = true;
            highestGoalScored = "\t\tNEW RECORD\nHighest Goal Scored: " + to_string(score[0]);
        }
        PlaySound(goalSound);
        DrawText("GOOAAALLL",SCREEN_WIDTH/2,SCREEN_HEIGHT/3,50,BLACK);
        pauseForGoal(3.5);
        resetPositons();
    }
}

void FootballGame::showOpeningScreen()
{
    Image temp = LoadImage("images/Newopening.png");
    ImageResize(&temp, SCREEN_WIDTH, SCREEN_HEIGHT);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTexture(LoadTextureFromImage(temp), 0, 0, WHITE);
        DrawText("Press any key to start",SCREEN_WIDTH/2-300,SCREEN_HEIGHT/2+300,40,WHITE);
        EndDrawing();
        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ESCAPE))
            break;
    }
}

void FootballGame::showClosingScreen()
{
    int delay = 0;
    while (delay < 300)
    {
        BeginDrawing();
        DrawText("Game Over", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 150, 50, BLACK);
        DrawText(TextFormat("Final Score: %d - %d", score[0], score[1]), SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 + 20, 50, BLACK);
        delay++;
        EndDrawing();
    }
}

void FootballGame::isHighestScored()
{
    if (flag)
    {
        PlaySound(highscoreSound);
        SetSoundVolume(highscoreSound,0.5f);
        int pause = 0;
        while (pause < 300)
        {
            BeginDrawing();
            ClearBackground(GREEN);
            DrawText(highestGoalScored.c_str(), SCREEN_WIDTH / 2 - 250, SCREEN_HEIGHT / 2 - 200, 60, BLACK);
            pause++;
            EndDrawing();
        }
        flag = false;
    }
}

void FootballGame::simulateGame()
{
    PlaySound(backgroundMusic);
    SetSoundVolume(backgroundMusic, 0.5f);
    showOpeningScreen();
    SetSoundVolume(backgroundMusic, 0.1f);

    ((Player *)entities[0])->setPosition({float(SCREEN_WIDTH / 2.0 - 100), float(SCREEN_HEIGHT / 2.0)});
    ((Player *)entities[1])->setPosition({float(SCREEN_WIDTH / 2.0 + 100), float(SCREEN_HEIGHT / 2.0)});
    ((Goalie *)entities[2])->setPosition({80, float(SCREEN_HEIGHT / 2.0)});
    ((Goalie *)entities[3])->setPosition({float(SCREEN_WIDTH - 100), float(SCREEN_HEIGHT / 2.0)});
    ((Ball *)entities[4])->updatePosition({float(SCREEN_WIDTH / 2.0 - 7), float(SCREEN_HEIGHT / 2.0 - 7)});

    while (!WindowShouldClose())
    {
        try{

            if (IsKeyDown(KEY_TAB))
            {
                simulatePausedScreen();
            }
    
            BeginDrawing();
            ClearBackground(WHITE);
            background.loadBackground(SCREEN_WIDTH, SCREEN_HEIGHT);
    
            entities[0]->update(horizontalLimit, verticalLimit);
            entities[1]->update(horizontalLimit, verticalLimit);
            ((Ball *)entities[4])->update((Player *)entities[0], (Player *)entities[1], horizontalLimit, verticalLimit);
            ((Goalie *)entities[2])->update((Ball *)entities[4], horizontalLimit, verticalLimit);
            ((Goalie *)entities[3])->update((Ball *)entities[4], horizontalLimit, verticalLimit);
            isGoaled();
    
            for (int i = 0; i < 5; i++)
            {
                entities[i]->draw();
            }
    
            DrawText(TextFormat("%d - %d", score[0], score[1]), SCREEN_WIDTH / 2.0 - 50, 10, 45, WHITE);
            DrawText(TextFormat("Time: %d", timeElapsed / 60), SCREEN_WIDTH / 2.0 - 30, SCREEN_HEIGHT - 35, 30, WHITE);
            timeElapsed++;
    
            if (timeElapsed >= timeLimit * 60)
            {
                EndDrawing();
                break;
            }
        }catch(const exception &e){
            cout<<"Exceotion caught: "<<e.what()<<endl;
        }

        EndDrawing();
    }

    showClosingScreen();
    isHighestScored();
}
