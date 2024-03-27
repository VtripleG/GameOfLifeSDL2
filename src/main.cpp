#include <iostream>
#include <sstream>

#include "GameBoard.h"
#include "GameScene.h"

int main( int argc, char* argv[] )
{
    int width = 0;
    int height = 0;
    int speed = 0;

    std::istringstream convertionStrem;

    switch ( argc )
    {
    case 2:
        convertionStrem = std::istringstream( argv[1] );
        convertionStrem >> speed;
        break;
    case 4:
        convertionStrem = std::istringstream( argv[1] );
        convertionStrem >> width;

        convertionStrem = std::istringstream( argv[2] );
        convertionStrem >> height;

        convertionStrem = std::istringstream( argv[3] );
        convertionStrem >> speed;
        break;
    }

    std::cout << width << " " << height << " " << speed << std::endl;

    GameBoard board( width, height );

    GameScene scene( board, speed );
    if( scene.Init() )
        scene.Start();

    board.~GameBoard();
    scene.Quit();

    return 0;
}
