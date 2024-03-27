#include "GameScene.h"

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <chrono>
#include <SDL2/SDL.h>

enum GameSpeed
{
    LVL1 = 0,
    LVL2,
    LVL3,
    LVL4,
    LVL5
};

GameScene::GameScene( GameBoard& gameBoard, int speedLVL) :
    m_gameBoard(gameBoard)
{
    switch( speedLVL )
    {
    case 1:
        m_frameInterval = 2.0;
        break;
    case 2:
        m_frameInterval = 1.5;
        break;
    case 3:
        m_frameInterval = 1.0;
        break;
    case 4:
        m_frameInterval = 0.75;
        break;
    case 5:
        m_frameInterval = 0.5;
        break;
    default:
        m_frameInterval = 1;
        break;
    }
}

bool GameScene::Init()
{
    const int windowSize = 800;

    if( m_gameBoard.GetHeight() <= m_gameBoard.GetWidth() )
        m_rectSize = ( windowSize - m_startX * 2 ) / m_gameBoard.GetWidth();
    else
        m_rectSize = ( windowSize - m_startY * 2 ) / m_gameBoard.GetHeight();

    SDL_SetMainReady();

    if (SDL_Init(SDL_INIT_VIDEO))
        return false;

    m_window   = nullptr;
    m_renderer = nullptr;

    if (SDL_CreateWindowAndRenderer(windowSize, windowSize, SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS, &m_window, &m_renderer))
        return false;

    SDL_SetWindowTitle(m_window, "Game of Life");

    Display();

    SDL_Event event;

    while (1)
    {
        SDL_PollEvent(&event);

        if( event.type == SDL_QUIT )
            return false;

        if( SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_ESCAPE])
            return false;

        if( SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_RETURN])
            break;

        if( event.type == SDL_MOUSEBUTTONDOWN )
        {
            int mouseX;
            int mouseY;
            SDL_GetMouseState( &mouseX, &mouseY );
            m_gameBoard.AddStartPoint( ( mouseY - m_startY ) / m_rectSize, ( mouseX - m_startX ) / m_rectSize );
            Display();

        }
    }

    return true;
}

void GameScene::Start()
{
    SDL_Event event;
    auto timePointStart = std::chrono::steady_clock::now();

    while ( m_gameBoard.HasNextGen() )
    {
        SDL_PollEvent( &event );

        if( SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_SPACE])
        {
            Pause();
            continue;
        }

        if( event.type == SDL_QUIT )
            return;

        if( SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_ESCAPE])
            return;

        auto timePointFinish = std::chrono::steady_clock::now();

        double elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(timePointFinish - timePointStart).count();

        if ( elapsed < m_frameInterval )
        {
            usleep( 10000 );
            continue;
        }

        timePointStart = std::chrono::steady_clock::now();

        m_gameBoard.ComputeNextGen();

        Display();
    }

    EndGame();
}

void GameScene::Display()
{
    SDL_SetRenderDrawColor( m_renderer, 255, 255, 255, 255 );

    SDL_RenderClear( m_renderer );

    SDL_Rect rect;

    for( size_t rowCounter = 0; rowCounter < m_gameBoard.GetHeight(); ++rowCounter )
        for( size_t columCounter = 0; columCounter < m_gameBoard.GetWidth(); ++columCounter )
        {
            rect = { m_startX + m_rectSize*columCounter, m_startY + m_rectSize*rowCounter, m_rectSize, m_rectSize };
            if( m_gameBoard.GetBoard()[rowCounter][columCounter] )
            {
                SDL_SetRenderDrawColor( m_renderer, 100, 1, 1, 255 );
                SDL_RenderFillRect( m_renderer, &rect );
            }
            else
            {
                SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
                SDL_RenderDrawRect( m_renderer, &rect );
            }
        }

    SDL_RenderPresent(m_renderer);
}

void GameScene::Quit()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void GameScene::Pause()
{
    SDL_SetRenderDrawColor( m_renderer, 255, 255, 255, 255 );

    SDL_RenderClear( m_renderer );

    SDL_Rect rect;

    for( size_t rowCounter = 0; rowCounter < m_gameBoard.GetHeight(); ++rowCounter )
        for( size_t columCounter = 0; columCounter < m_gameBoard.GetWidth(); ++columCounter )
        {
            rect = { m_startX + m_rectSize*columCounter, m_startY + m_rectSize*rowCounter, m_rectSize, m_rectSize };
            if( m_gameBoard.GetBoard()[rowCounter][columCounter] )
            {
                SDL_SetRenderDrawColor( m_renderer, 200, 200, 200, 255 );
                SDL_RenderFillRect( m_renderer, &rect );
            }
            else
            {
                SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
                SDL_RenderDrawRect( m_renderer, &rect );
            }
        }

    SDL_RenderPresent(m_renderer);
}

void GameScene::EndGame()
{
    SDL_SetRenderDrawColor( m_renderer, 255, 255, 255, 255 );

    SDL_RenderClear( m_renderer );

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255 );

    SDL_Rect rect;

    for( size_t rowCounter = 0; rowCounter < m_gameBoard.GetHeight(); ++rowCounter )
        for( size_t columCounter = 0; columCounter < m_gameBoard.GetWidth(); ++columCounter )
        {
            rect = { m_startX + m_rectSize*columCounter, m_startY + m_rectSize*rowCounter, m_rectSize, m_rectSize };
            if( m_gameBoard.GetBoard()[rowCounter][columCounter] )
                SDL_RenderFillRect(m_renderer, &rect );
            else
                SDL_RenderDrawRect( m_renderer, &rect );
        }

    SDL_RenderPresent(m_renderer);

    SDL_Event event;

    while(1)
    {
        SDL_PollEvent( &event );

        if( event.type == SDL_QUIT || event.type == SDL_KEYDOWN )
            break;
    }

}
