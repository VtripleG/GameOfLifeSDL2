#pragma once

#include <SDL.h>

#include "GameBoard.h"

class GameScene
{
public:
    GameScene( GameBoard& GameBoard, int speedLVL = 5 );

    bool Init();

    void Start();

    void Quit();

private:
    void Display();

    void Pause();

    void EndGame();

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    GameBoard& m_gameBoard;
    const int m_startX = 10;
    const int m_startY = 10;
    int m_rectSize;
    double m_frameInterval;
};
