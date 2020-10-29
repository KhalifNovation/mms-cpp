#ifndef MAP
#define MAP

#include <iostream>
#include <string>
#include <stdio.h>

#include "API.h"

#define sizeX 5
#define sizeY 5

#define target1X 2
#define target1Y 2

class Mem2D
{
private:
    int8_t boxVal[5][5] = {-1}; //  [x][y][0]=index  [x][y][0]=wall 0bxxxxWSEN 1 = have wall
    bool boxWallHorizontal[5][6] = {0};
    bool boxWallVertical[6][5] = {0};
    bool boxCheck[5][5] = {false};

public:
    int neigboorN[2] = {0, 1};
    int neigboorE[2] = {1, 0};
    int neigboorS[2] = {0, -1};
    int neigboorW[2] = {-1, 0};

    int8_t neighbourNESW[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};

    Mem2D()
    {
        boxVal[target1X][target1Y] = 0;
        clearFlagBox();

        setLimitWall();
        setTestWall();

        floodfill();

        clearFlagBox();
    }

    void floodfill()
    {
        bool done = false;
        int8_t index = 0;
        while (!done)
        {

            for (int8_t y = 0; y < sizeX; y++)
            {
                for (int8_t x = 0; x < sizeY; x++)
                {

                    if (boxVal[x][y] == index && boxCheck[x][y])
                    {
                        int8_t neighbourX;
                        int8_t neighbourY;
                        int8_t newVal = index + 1;
                        bool wall[4];
                        wall[0] = boxWallHorizontal[x][y + 1];
                        wall[1] = boxWallVertical[x + 1][y];
                        wall[2] = boxWallHorizontal[x][y];
                        wall[3] = boxWallVertical[x][y];

                        for (int i = 0; i < 4; i++)
                        {
                            neighbourX = x + neighbourNESW[i][0];
                            neighbourY = y + neighbourNESW[i][1];

                            if (boxCheck[neighbourX][neighbourY])
                                continue;
                            if (neighbourX < 0)
                                continue;
                            if (neighbourX > sizeX - 1)
                                continue;
                            if (neighbourY < 0)
                                continue;
                            if (neighbourY > sizeY - 1)
                                continue;
                            if (wall[i])
                                continue;

                            boxVal[neighbourX][neighbourY] = newVal;
                            boxCheck[neighbourX][neighbourY] = true;
                        }
                    }

                    if (x == sizeX - 1 && y == sizeY - 1)
                    {
                        uint8_t boxCount = 0;
                        for (int8_t yCheck = 0; yCheck < sizeY; yCheck++)
                        {
                            for (int8_t xCheck = 0; xCheck < sizeX; xCheck++)
                            {
                                if (boxCheck[xCheck][yCheck])
                                {
                                    boxCount++;
                                }
                            }
                        }
                        if (boxCount == sizeX * sizeY)
                        {
                            done = true;
                        }
                    }
                }
            }
            index++;
        }

        for (int8_t yCheck = 0; yCheck < sizeY; yCheck++)
        {
            for (int8_t xCheck = 0; xCheck < sizeX; xCheck++)
            {
                boxCheck[xCheck][yCheck] = false;
            }
        }

        boxCheck[2][2] = true;
        setText();
    }

    void setLimitWall()
    {
        for (int8_t y = 0; y < sizeX; y++)
        {
            for (int8_t x = 0; x < sizeY; x++)
            {
                if (x == 0 && y == 0)
                {
                    setBitWall(x, y, 's');
                    setBitWall(x, y, 'w');
                }
                else if (x == sizeX - 1 && y == 0)
                {
                    setBitWall(x, y, 's');
                    setBitWall(x, y, 'e');
                }
                else if (x == 0 && y == sizeY - 1)
                {
                    setBitWall(x, y, 'n');
                    setBitWall(x, y, 'w');
                }
                else if (x == sizeX - 1 && y == sizeY - 1)
                {
                    setBitWall(x, y, 'n');
                    setBitWall(x, y, 'e');
                }
                else if (y == 0)
                {
                    setBitWall(x, y, 's');
                }
                else if (x == 0)
                {
                    setBitWall(x, y, 'w');
                }
                else if (y == sizeY - 1)
                {
                    setBitWall(x, y, 'n');
                }
                else if (x == sizeX - 1)
                {
                    setBitWall(x, y, 'e');
                }
            }
        }
    }

    void setTestWall()
    {
        // setBitWall(0, 0, 'e');
        // setBitWall(1, 0, 'n');
        // setBitWall(2, 0, 'n');
        // setBitWall(0, 1, 'n');
        // setBitWall(2, 1, 'n');
        // setBitWall(3, 1, 'n');
        // setBitWall(3, 1, 'e');
        // setBitWall(0, 2, 'e');
        // setBitWall(1, 2, 'e');
        // setBitWall(2, 2, 'n');
        // setBitWall(3, 2, 'e');
        // setBitWall(0, 3, 'e');
        // setBitWall(2, 3, 'e');
        // setBitWall(3, 3, 'e');
        // setBitWall(1, 4, 'e');
        // setBitWall(3, 4, 'e');
    }

    void clearFlagBox()
    {
        for (int8_t y = 0; y < sizeX; y++)
        {
            for (int8_t x = 0; x < sizeY; x++)
            {
                boxCheck[x][y] = false;
            }
        }

        boxCheck[target1X][target1Y] = true;
    }

    void setBitWall(uint8_t x, uint8_t y, char val)
    {
        if (val == 'n')
        {
            boxWallHorizontal[x][y + 1] = true;
        }
        else if (val == 'e')
        {
            boxWallVertical[x + 1][y] = true;
        }
        else if (val == 's')
        {
            boxWallHorizontal[x][y] = true;
        }
        else if (val == 'w')
        {
            boxWallVertical[x][y] = true;
        }
    }

    void clearBitWall(uint8_t x, uint8_t y, char val)
    {
        if (val == 'n')
        {
            boxWallHorizontal[x][y + 1] = false;
        }
        else if (val == 'e')
        {
            boxWallVertical[x + 1][y] = false;
        }
        else if (val == 's')
        {
            boxWallHorizontal[x][y] = false;
        }
        else if (val == 'w')
        {
            boxWallVertical[x][y] = false;
        }
    }

    void setText()
    {
        for (int8_t x = 0; x < sizeX; x++)
        {
            for (int8_t y = 0; y < sizeY; y++)
            {
                API::setText(x, y, std::to_string(boxVal[x][y]));

                if (boxWallHorizontal[x][y + 1])
                {
                    API::setWall(x, y, 'n');
                }

                if (boxWallVertical[x + 1][y])
                {
                    API::setWall(x, y, 'e');
                }

                if (boxWallHorizontal[x][y])
                {
                    API::setWall(x, y, 's');
                }

                if (boxWallVertical[x][y])
                {
                    API::setWall(x, y, 'w');
                }
            }
        }
        std::cerr << "Remmaping " << std::endl;
    }

    int8_t getCurrentVal(uint8_t x, uint8_t y)
    {
        return boxVal[x][y];
    }

    int getNeighbourS(int i)
    {
        return neigboorS[i];
    }

    int getNeighbourVal(int x, int y, char direction)
    {
        int index[2];

        if (direction == 'n')
        {
            index[0] = neigboorN[0];
            index[1] = neigboorN[1];
        }
        else if (direction == 'e')
        {
            index[0] = neigboorE[0];
            index[1] = neigboorE[1];
        }
        else if (direction == 's')
        {
            index[0] = neigboorS[0];
            index[1] = neigboorS[1];
        }
        else if (direction == 'w')
        {
            index[0] = neigboorW[0];
            index[1] = neigboorW[1];
        }

        // std::cerr << "( ";
        // std::cerr << std::to_string(neigboorW[0]);
        // std::cerr << " , ";
        // std::cerr << std::to_string(neigboorW[1]);
        // std::cerr << " )" << std::endl;

        if (x + index[0] < 0 || x + index[1] < 0) //|| x + index[0] > 15 || y + index[1] > 15)
            return -1;
        return boxVal[x + index[0]][y + index[1]];
    }

    void setVal(uint8_t x, uint8_t y, int8_t val)
    {
        boxVal[x][y] = val;
    }
};

#endif