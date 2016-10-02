#ifndef GAME_H
#define GAME_H

class Game
{
public:
    explicit Game(int x=10,int y=10);
    int getSquare(int x, int y);
    bool setSquare(int x, int y, int val);
    void advanceTime();
    int countNeighbors(int x, int y);
    int getXSize();
    int getYSize();

private:
    std::vector<std::vector<int> > board;
    int xSize;
    int ySize;
};

#endif // GAME_H
