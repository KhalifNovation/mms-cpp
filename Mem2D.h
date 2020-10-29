#ifndef MAP
#define MAP

#include <iostream>
#include <string>
#include <stdio.h>

#include "API.h"

#define sizeX 16
#define sizeY 16

#define target1X 8
#define target1Y 8

#define target2X 7
#define target2Y 8

#define target3X 7
#define target3Y 7

#define target4X 8
#define target4Y 7

#define firstBox 14

class Mem2D
{
private:
    int8_t box[16][16][2] = {-1}; //  [x][y][0]=index  [x][y][0]=wall 0bxxxxWSEN 1 = have wall

public:
    int neigboorN[2] = {0, 1};
    int neigboorE[2] = {1, 0};
    int neigboorS[2] = {0, -1};
    int neigboorW[2] = {-1, 0};

    Mem2D()
    {

        box[target1X][target1Y][0] = 0;
        box[target2X][target2Y][0] = 0;
        box[target3X][target3Y][0] = 0;
        box[target4X][target4Y][0] = 0;

        bool done = false;
        int8_t index = 0;

        while (!done)
        {
            for (int8_t x = 0; x < sizeX; x++)
            {
                for (int8_t y = 0; y < sizeY; y++)
                {
                    if (box[x][y][0] == -1)
                        ;
                    else if (index == box[x][y][0])
                    {

                        int8_t cursorX;
                        int8_t cursorY;
                        cursorX = x + neigboorN[0];
                        cursorY = y + neigboorN[1];
                        std::cerr << "( ";
                        std::cerr << std::to_string(x);
                        std::cerr << " , ";
                        std::cerr << std::to_string(y);
                        std::cerr << ") = " << std::to_string(index) << std::endl;

                        if (box[cursorX][cursorY][0] == -1 && y + 1 < 15)
                        {
                            box[cursorX][cursorY][0] = index + 1;
                        }
                        cursorX = x + neigboorE[0];
                        cursorY = y + neigboorE[1];
                        if (box[cursorX][cursorY][0] == -1 && x + 1 < 15)
                        {
                            box[cursorX][cursorY][0] = index + 1;
                        }
                        cursorX = x + neigboorS[0];
                        cursorY = y + neigboorS[1];
                        if (box[cursorX][cursorY][0] == -1 && y - 1 > 0)
                        {
                            box[cursorX][cursorY][0] = index + 1;
                        }
                        cursorX = x + neigboorW[0];
                        cursorY = y + neigboorW[1];
                        if (box[cursorX][cursorY][0] == -1 && x - 1 > 0)
                        {
                            box[cursorX][cursorY][0] = index + 1;
                        }
                    }

                    //initial wall

                    if (x == 0)
                    {
                        setBitWall(x, y, 'w');
                    }

                    if (y == 0)
                    {
                        setBitWall(x, y, 's');
                    }

                    if (x == 15)
                    {
                        setBitWall(x, y, 'e');
                    }

                    if (y == 15)
                    {
                        setBitWall(x, y, 'n');
                    }
                }
            }
            std::cerr << "Inc Index = " << std::to_string(index) << std::endl;
            index++;

            if (index == 14)
            {
                done = true;
            }
        }
        // std::cerr << "( ";
        // std::cerr << std::to_string(neigboorW[0]);
        // std::cerr << " , ";
        // std::cerr << std::to_string(neigboorW[1]);
        // std::cerr << " )" << std::endl;

        //Test Path
        setPathDummy();
    }

    void setPathDummy()
    {
        box[0][0][0] = 84;
        box[0][1][0] = 83;
        box[0][2][0] = 82;
        box[1][2][0] = 81;
        box[2][2][0] = 80;
        box[2][1][0] = 79;
        box[3][1][0] = 78;
        box[3][0][0] = 77;
        box[4][0][0] = 76;
        box[5][0][0] = 75;
        box[6][0][0] = 74;
        box[7][0][0] = 73;
        box[8][0][0] = 72;
        box[9][0][0] = 71;
        box[10][0][0] = 70;
        box[11][0][0] = 69;
        box[12][0][0] = 68;
        box[13][0][0] = 67;
        box[14][0][0] = 66;
        box[15][0][0] = 65;
        box[15][1][0] = 64;
        box[14][1][0] = 63;
        box[13][1][0] = 62;
        box[12][1][0] = 61;
        box[11][1][0] = 60;
        box[10][1][0] = 59;
        box[9][1][0] = 58;
        box[8][1][0] = 57;
        box[7][1][0] = 56;
        box[6][1][0] = 55;
        box[5][1][0] = 54;
        box[4][1][0] = 53;
        box[4][2][0] = 52;
        box[4][3][0] = 51;
        box[4][4][0] = 50;
        box[4][5][0] = 49;
        box[4][6][0] = 48;
        box[3][6][0] = 47;
        box[2][6][0] = 46;
        box[1][6][0] = 45;
        box[1][7][0] = 44;
        box[1][8][0] = 43;
        box[2][8][0] = 42;
        box[3][8][0] = 41;
        box[4][8][0] = 40;
        box[5][8][0] = 39;
        box[5][9][0] = 38;
        box[5][10][0] = 37;
        box[5][11][0] = 36;
        box[5][12][0] = 35;
        box[6][12][0] = 34;
        box[7][12][0] = 33;
        box[8][12][0] = 32;
        box[9][12][0] = 31;
        box[9][13][0] = 30;
        box[10][13][0] = 29;
        box[11][13][0] = 28;
        box[12][13][0] = 27;
        box[13][13][0] = 26;
        box[14][13][0] = 25;
        box[14][12][0] = 24;
        box[13][12][0] = 23;
        box[12][12][0] = 22;
        box[11][12][0] = 21;
        box[10][12][0] = 20;
        box[10][11][0] = 19;
        box[11][11][0] = 18;
        box[12][11][0] = 17;
        box[13][11][0] = 16;
        box[13][10][0] = 15;
        box[12][10][0] = 14;
        box[11][10][0] = 13;
        box[10][10][0] = 12;
        box[10][9][0] = 11;
        box[11][9][0] = 10;
        box[12][9][0] = 9;
        box[13][9][0] = 8;
        box[13][8][0] = 7;
        box[12][8][0] = 6;
        box[11][8][0] = 5;
        box[10][8][0] = 4;
        box[9][8][0] = 3;
        box[9][9][0] = 2;
        box[8][9][0] = 1;
        box[7][8][0] = 0;

        box[2][0][0] = 7;
    }

    void setBitWall(uint8_t x, uint8_t y, char val)
    {
        int8_t buff;
        if (val == 'n')
        {
            buff = 0b00000001;
        }
        else if (val == 'e')
        {
            buff = 0b00000010;
        }
        else if (val == 's')
        {
            buff = 0b00000100;
        }
        else if (val == 'w')
        {
            buff = 0b00001000;
        }

        box[x][y][1] |= buff;
    }

    void clearBitWall(uint8_t x, uint8_t y, char val)
    {
        int8_t buff;
        if (val == 'n')
        {
            buff = 0b11111110;
        }
        else if (val == 'e')
        {
            buff = 0b11111101;
        }
        else if (val == 's')
        {
            buff = 0b11111011;
        }
        else if (val == 'w')
        {
            buff = 0b11110111;
        }

        box[x][y][1] &= buff;
    }

    void setText()
    {
        for (int8_t x = 0; x < sizeX; x++)
        {
            for (int8_t y = 0; y < sizeY; y++)
            {
                API::setText(x, y, std::to_string(box[x][y][0]));

                uint8_t buff = box[x][y][1];
                bool nLogic = buff & 0b00000001;
                bool eLogic = (buff & 0b00000010) >> 1;
                bool sLogic = (buff & 0b00000100) >> 2;
                bool wLogic = (buff & 0b00001000) >> 3;
                if (nLogic)
                {
                    API::setWall(x, y, 'n');
                }

                if (eLogic)
                {
                    API::setWall(x, y, 'e');
                }

                if (sLogic)
                {
                    API::setWall(x, y, 's');
                }

                if (wLogic)
                {
                    API::setWall(x, y, 'w');
                }
            }
        }
    }

    int8_t getCurrentVal(uint8_t x, uint8_t y)
    {
        return box[x][y][0];
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
        return box[x + index[0]][y + index[1]][0];
    }

    void setVal(uint8_t x, uint8_t y, int8_t val)
    {
        box[x][y][0] = val;
    }
};

#endif