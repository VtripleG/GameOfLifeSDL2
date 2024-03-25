#include <iostream>
#include <unistd.h>
#include <SDL2/SDL.h>

#include "GameBoard.h"

int main()
{
    GameBoard board( 10, 10 );

        board.AddStartPoint( 3, 3 );
        board.AddStartPoint( 4, 4 );
        board.AddStartPoint( 4, 5 );
        board.AddStartPoint( 5, 3 );
        board.AddStartPoint( 5, 4 );

//        board.AddStartPoint( 3, 3 );
//        board.AddStartPoint( 3, 4 );
//        board.AddStartPoint( 4, 3 );

//        board.AddStartPoint( 3, 3 );
//        board.AddStartPoint( 4, 4 );
//        board.AddStartPoint( 3, 5 );

    bool** brd = board.GetBoard();

    for ( size_t row = 0; row < 10; ++row )
    {
        for( size_t colum = 0; colum < 10; ++colum )
            std::cout << '|' << brd[row][colum] << '|';

        std::cout << std::endl;
    }

    while ( board.HasNextGen() )
    {
        for( size_t counter = 0; counter < 20; ++counter )
            std::cout << '_';
        std::cout << std::endl;

        board.ComputeNextGen();

        brd = board.GetBoard();

        for ( size_t row = 0; row < 10; ++row )
        {
            for( size_t colum = 0; colum < 10; ++colum )
                std::cout << '|' << brd[row][colum] << '|';

            std::cout << std::endl;
        }

        sleep( 1 );
    }

    board.~GameBoard();
    return 0;
}
