#pragma once

#include <vector>
#include <algorithm>
#include <cassert>
#include "SnakeNode.h"

/*
    Declarations of the structure of the snake
    A snake is composed of multiple nodes,
    all nodes are stored in vector.
*/
class Snake
{
private:
    vector<SnakeNode> snake; /*which stored all nodes*/
    int spaceWidth, spaceHeight; /*Size of snakes' active space*/
    int initLength;
    int direction; /*Current direction of snake*/
public:
    enum {UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4}; /*constants of four directions*/

    Snake(int spaceWidth, int spaceHeight, int initLength); /*Constructor*/
    void initSnake();
    int getLength(); /*Get the length of the snake*/
    SnakeNode getSnakeNode(int i); /*Get the i node (i starts from zero)*/
    SnakeNode getHeadNode(); /*Get the first node*/
    SnakeNode getTailNode(); /*Get the last node*/
    void setDirection(int d); /*Set the direction of the snake*/
    int getDirection();
    void go(); /*Let the snake move one step (according to the current direction)*/
    void lengthen(); /*Increase the length of the snake by 1 (the new node coordinates are the same as the current last node).*/
    void print();
};
