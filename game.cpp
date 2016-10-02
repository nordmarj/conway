#include <vector>
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include "game.h"

/*
 * Creates a board of x*y squares set to zero.
 */
Game::Game(int x, int y)
{
    xSize = x;
    ySize = y;
    board.resize(x, std::vector<int>(y, 0));
    for(int i = 0; i < x; i++)
    {
        for(int j = 0; j < y; j++)
        {
            board[i][j] = 0;
        }
    }
}

/*
 * Gets board width in squares.
 */
int Game::getXSize()
{
    return xSize;
}

/*
 * Gets board heigth in squares.
 */
int Game::getYSize()
{
    return ySize;
}

/*
 * Gets the value of square x,y. Values of x and y that lie outside the board are handled by wrapping around the edges.
 */
int Game::getSquare(int x, int y)
{

    if(x < 0)
    {
        x = (xSize + x)%xSize;
    }
    if(y < 0)
    {
        y = (ySize + y)%ySize;
    }
    return board[x%xSize][y%ySize];
}

/*
 * Sets square x,y to value val.
 */
bool Game::setSquare(int x, int y, int val)
{
    if((x > xSize) || (y > ySize) || (x < 0) || (y < 0))
    {
        return false;
    }
    else
    {
        board[x][y] = val;
        return true;
    }
}

/*
 * Applies the rules of Conways game of life to update the board one timestep.
 */
void Game::advanceTime()
{
    std::vector<std::vector<int> > newBoard = board;
    for(int i = 0; i < xSize; i++)
    {
        for(int j = 0; j < ySize; j++)
        {
            int neighbors = countNeighbors(i,j);
            if(neighbors < 2)
            {
                newBoard[i][j] = 0;
            }
            if(neighbors == 2)
            {
                newBoard[i][j] = board[i][j];
            }
            if(neighbors == 3)
            {
                newBoard[i][j] = 1;
            }
            if(neighbors > 3)
            {
                newBoard[i][j] = 0;
            }
        }
    }
    board = newBoard;
}

/*
 * Gets the number of live (nonzero) neighbors to square x,y.
 */
int Game::countNeighbors(int x, int y)
{
    int ans = 0;
    for(int i = x-1; i <= x + 1; i++)
    {
        for(int j = y-1; j <= y + 1; j++)
        {
            if(!((i == x) && (j == y)))
            {
                if(getSquare(i,j)!=0)
                {
                    ans += 1;
                }
            }
        }
    }
    return ans;
}
