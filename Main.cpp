#include <iostream>
#include <string>
#include <stdio.h>

#include "API.h"

#include "Mem2D.h"

void log(const std::string &text)
{
    std::cerr << text << std::endl;
}

class Nav
{
private:
    int8_t carNav = 0;
    int possition[2] = {0, 0};
    char carNavLabel[4] = {'n', 'e', 's', 'w'};

public:
    Nav()
    {
    }

    void moveUpdate()
    {
        int add[2];

        if (carNav == 0)
        { // N
            add[0] = 0;
            add[1] = 1;
        }
        else if (carNav == 1)
        { // E
            add[0] = 1;
            add[1] = 0;
        }
        else if (carNav == 2)
        { // S
            add[0] = 0;
            add[1] = -1;
        }
        else if (carNav == 3)
        { // W
            add[0] = -1;
            add[1] = 0;
        }

        possition[0] += add[0];
        possition[1] += add[1];
    }

    void turnLeftUpdate()
    {
        if (carNav == 0)
            carNav = 3;

        else
            carNav--;
    }

    void turnRightUpdate()
    {
        if (carNav == 3)
            carNav = 0;

        else
            carNav++;
    }

    int8_t getNav()
    {
        return carNav;
    }

    int8_t getNavLeft()
    {
        int8_t buff;
        if (carNav == 0)
            buff = 3;

        else
            buff = carNav - 1;
        return buff;
    }

    int8_t getNavRight()
    {
        int8_t buff;
        if (carNav == 3)
            buff = 0;

        else
            buff = carNav + 1;
        return buff;
    }

    char getNavLabel()
    {
        return carNavLabel[carNav];
    }

    char getNavLeftLabel()
    {
        char buff;
        if (carNav == 0)
            buff = 3;

        else
            buff = carNav - 1;
        return carNavLabel[buff];
    }

    char getNavRightLabel()
    {
        char buff;
        if (carNav == 3)
            buff = 0;

        else
            buff = carNav + 1;
        return carNavLabel[buff];
    }

    uint8_t getX()
    {
        return (possition[0]);
    }
    uint8_t getY()
    {
        return (possition[1]);
    }

    void printCoor()
    {
        std::string text = "Pos = ( ";
        text += std::to_string(getX());
        text += " , ";
        text += std::to_string(getY());
        text += ")";
        log(text);
    }
};

Mem2D mazeMem;
Nav compass;

void forward()
{
    API::moveForward();
    compass.moveUpdate();
    compass.printCoor();
}

void turnLeft()
{
    API::turnLeft();
    compass.turnLeftUpdate();
}

void turnRight()
{
    API::turnRight();
    compass.turnRightUpdate();
}

void uTurn()
{
    API::turnRight();
    API::turnRight();
    compass.turnRightUpdate();
    compass.turnRightUpdate();
}

void updateWall(uint8_t x, uint8_t y)
{
    if (API::wallFront())
    {
        mazeMem.setBitWall(x, y, compass.getNavLabel());
    }

    if (API::wallRight())
    {
        mazeMem.setBitWall(x, y, compass.getNavRightLabel());
    }

    if (API::wallLeft())
    {
        mazeMem.setBitWall(x, y, compass.getNavLeftLabel());
    }
    mazeMem.floodfill();
}
bool checked = false;
int count1 = 0;
int main(int argc, char *argv[])
{
    compass.printCoor();
    mazeMem.setText();

    while (true)
    {
        int currentX = compass.getX();
        int currentY = compass.getY();
        uint8_t currentVal = mazeMem.getCurrentVal(currentX, currentY);
        int8_t currentDir = compass.getNav();
        int neighbour[4];
        neighbour[0] = mazeMem.getNeighbourVal(currentX, currentY, 'n');
        neighbour[1] = mazeMem.getNeighbourVal(currentX, currentY, 'e');
        neighbour[2] = mazeMem.getNeighbourVal(currentX, currentY, 's');
        neighbour[3] = mazeMem.getNeighbourVal(currentX, currentY, 'w');

        updateWall(currentX, currentY);

        if (!API::wallFront() && !checked)
        {
            //log(std::to_string(compass.getNav()));
            if (neighbour[currentDir] != -1)
            {
                if (neighbour[currentDir] < currentVal)
                {

                    int8_t diff = neighbour[currentDir] - currentVal;
                    log(std::to_string(diff));
                    if (diff == -1)
                    {
                        forward();
                    }
                    else
                    {
                        /* code */ log("Checked");
                        checked = true;
                    }
                }
                else
                {
                    if (count1 == 0)
                    {
                        turnLeft();
                        // updateWall(compass.getX(), compass.getY());

                        turnLeft();
                        // updateWall(compass.getX(), compass.getY());
                        forward();
                        // updateWall(compass.getX(), compass.getY());
                        updateWall(compass.getX(), compass.getY());
                        turnRight();
                        // updateWall(compass.getX(), compass.getY());
                        forward();
                        updateWall(compass.getX(), compass.getY());
                        // log("Stuck Here");
                        count1++;
                    }
                    else if (count1 == 1)
                    {
                        turnRight();
                        forward();
                        updateWall(compass.getX(), compass.getY());
                    }
                }
            }
        }
        else
        {
            checked = false;
            int8_t neighbourLeft = neighbour[compass.getNavLeft()];
            int8_t neighbourRight = neighbour[compass.getNavRight()];
            if (neighbourLeft != -1 && neighbourRight != -1 && !API::wallRight() && !API::wallLeft())
            {
                log(std::to_string(neighbourLeft));
                log(std::to_string(neighbourRight));
                if (neighbourLeft > neighbourRight)
                {
                    int8_t diff = neighbourRight - currentVal;
                    if (diff == -1)
                    {
                        turnRight();
                    }
                    else
                    {
                        turnLeft();
                    }
                }
                else if (neighbourLeft < neighbourRight)
                {
                    int8_t diff = neighbourLeft - currentVal;
                    if (diff == -1)
                    {
                        turnLeft();
                    }
                    else
                    {
                        turnRight();
                    }
                }
                else
                {
                    log("Same Val");
                }
            }
            else
            {
                if (!API::wallLeft())
                {
                    turnLeft();
                }
                else
                {
                    turnRight();
                }
            }
        }
    }
}
