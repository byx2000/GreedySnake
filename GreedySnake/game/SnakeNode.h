#pragma once

#include <iostream>
#include <string>

using namespace std;

/*
    Declarations of the structure of the snake node
*/
class SnakeNode
{
private:
    /*
        The position of a node

        Screen coordinate schematic:
        (0,0)
           ------------------------>x
           |
           |
           |
           |
           |
           |
           |
           v
           y
    */
    int xPos, yPos;
public:
    SnakeNode(int xPos, int yPos); /*Constructor*/
    void setPos(int xPos, int yPos); /*Set the position of the node */
    int getX(); /*Get x value*/
    int getY(); /*Get y value*/
    bool operator==(SnakeNode node); /*Used by count in Snake.cpp*/
    string toString();
};
