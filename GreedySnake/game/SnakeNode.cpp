#include "SnakeNode.h"

/*
    Definition of the structure of the snake node
*/
SnakeNode::SnakeNode(int xPos, int yPos)
{
    setPos(xPos, yPos);
}

void SnakeNode::setPos(int xPos, int yPos)
{
    this->xPos = xPos;
    this->yPos = yPos;
}

int SnakeNode::getX()
{
    return xPos;
}

int SnakeNode::getY()
{
    return yPos;
}

bool SnakeNode::operator==(SnakeNode node)
{
    return xPos == node.getX() && yPos == node.getY();
}

string SnakeNode::toString()
{
    string s = "(";
    s += to_string(xPos);
    s += ",";
    s += to_string(yPos);
    s += ")";
    return s;
}
