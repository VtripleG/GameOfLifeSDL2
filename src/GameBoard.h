#pragma once

#include <iostream>
#include <vector>

class GameBoard
{
public:
    GameBoard(){}

    GameBoard( int width, int height )
    {
        m_height = height;
        m_width = width;
        m_boardCurrent = new bool*[m_height];

        for( size_t counter = 0; counter < m_height; ++counter )
            m_boardCurrent[counter] = new bool [m_width];

        m_boardFuture =  new bool*[m_height];

        for( size_t counter = 0; counter < m_height; ++counter )
            m_boardFuture[counter] = new bool [m_width];

        for( size_t rowCounter = 0; rowCounter < m_height; ++rowCounter )
            for( size_t columCounter = 0; columCounter < m_width; ++columCounter )
                m_boardCurrent[rowCounter][columCounter] = false;
    }

    ~GameBoard()
    {
        delete [] m_boardCurrent;
        delete [] m_boardFuture;

    }

    void ComputeNextGen()
    {
        for( size_t rowCounter = 0; rowCounter < m_height; ++rowCounter )
            for( size_t columCounter = 0; columCounter < m_width; ++columCounter )
            {
                int neighbourNum = NeighbourCounter( rowCounter, columCounter );

                if( ( neighbourNum == 2 || neighbourNum == 3 ) && m_boardCurrent[rowCounter][columCounter] == true )
                {
                    m_boardFuture[rowCounter][columCounter] = true;
                    continue;
                }

                if( neighbourNum == 3 && m_boardCurrent[rowCounter][columCounter] == false )
                {
                    m_boardFuture[rowCounter][columCounter] = true;
                    continue;
                }

                    m_boardFuture[rowCounter][columCounter] = false;
            }

        m_boardCurrent = m_boardFuture;
    }

    bool** GetBoard()
    {
        return m_boardCurrent;
    }

    void AddStartPoint( int row, int colum )
    {
        m_boardCurrent[row][colum] = true;
    }

private:
    int NeighbourCounter( int row, int colum )
    {
        int counterNeighbour = 0;

        std::vector<int> rowList;
        std::vector<int> columList;

        if( row == 0 )
        {
            rowList.push_back( m_height - 1 );
            rowList.push_back( m_height - 1 );
            rowList.push_back( m_height - 1 );
            rowList.push_back( row );
            rowList.push_back( row + 1 );
            rowList.push_back( row + 1 );
            rowList.push_back( row + 1 );
            rowList.push_back( row );
        }

        if( row == m_height - 1 )
        {
            rowList.push_back( row - 1 );
            rowList.push_back( row - 1 );
            rowList.push_back( row - 1 );
            rowList.push_back( row );
            rowList.push_back( 0 );
            rowList.push_back( 0 );
            rowList.push_back( 0 );
            rowList.push_back( row );
        }

        if( (row < m_height - 1) && (row > 0) )
        {
            rowList.push_back( row - 1 );
            rowList.push_back( row - 1 );
            rowList.push_back( row - 1 );
            rowList.push_back( row );
            rowList.push_back( row + 1 );
            rowList.push_back( row + 1 );
            rowList.push_back( row + 1 );
            rowList.push_back( row );
        }

        if( colum == 0 )
        {
            columList.push_back( m_width - 1 );
            columList.push_back( colum );
            columList.push_back( colum + 1 );
            columList.push_back( colum + 1 );
            columList.push_back( colum + 1 );
            columList.push_back( colum );
            columList.push_back( m_width - 1 );
            columList.push_back( m_width - 1 );
        }

        if( colum == m_width - 1 )
        {
            columList.push_back( colum - 1 );
            columList.push_back( colum );
            columList.push_back( 0 );
            columList.push_back( 0 );
            columList.push_back( 0 );
            columList.push_back( colum );
            columList.push_back( colum - 1 );
            columList.push_back( colum - 1 );
        }

        if( (colum < m_width - 1) && (colum > 0) )
        {
            columList.push_back( colum - 1 );
            columList.push_back( colum );
            columList.push_back( colum + 1 );
            columList.push_back( colum + 1 );
            columList.push_back( colum + 1 );
            columList.push_back( colum );
            columList.push_back( colum - 1 );
            columList.push_back( colum - 1 );
        }

        for( size_t counter = 0; counter < 8; ++counter)
        {
            if ( m_boardCurrent[ rowList[ counter ] ][ columList[ counter ] ] == true )
                ++counterNeighbour;
        }

        return counterNeighbour;
    }
private:
    bool** m_boardCurrent;
    bool** m_boardFuture;
    int m_height;
    int m_width;
};
