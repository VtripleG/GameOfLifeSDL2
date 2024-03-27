#include <iostream>
#include <unistd.h>
#include <SDL.h>

#include "GameBoard.h"
#include "GameScene.h"

int main()
{
    const int width = 21;
    const int height = 21;
    GameBoard board( width, height );

    GameScene scene( board );
    if( scene.Init() )
        scene.Start();

    board.~GameBoard();
    scene.Quit();
    return 0;
}
