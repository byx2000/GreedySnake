#include "Snake.h"
#include "../global.h"

/*
    Definition of the structure of the snake
*/
Snake::Snake(int spaceWidth, int spaceHeight, int initLength)
{
    assert(spaceWidth > 5 && spaceHeight > 5 && initLength < spaceHeight);

    this->spaceWidth = spaceWidth;
    this->spaceHeight = spaceHeight;
    this->initLength = initLength;

    initSnake();
}

void Snake::initSnake()
{
    snake.clear();

    int x = spaceWidth / 2;
    int y = (spaceHeight - initLength) / 2;

    for (int i = 0; i < initLength; ++i)
    {
        snake.push_back(SnakeNode(x, y + i));
    }

    direction = UP;
}

int Snake::getLength()
{
    return snake.size();
}

SnakeNode Snake::getSnakeNode(int i)
{
    return snake[i];
}

SnakeNode Snake::getHeadNode()
{
    return snake[0];
}

SnakeNode Snake::getTailNode()
{
    return snake[snake.size() - 1];
}

void Snake::setDirection(int d)
{
    assert(d >= UP && d <= RIGHT);

    if ((d == direction)
        || (d == UP && direction == DOWN)
        || (d == DOWN && direction == UP)
        || (d == LEFT && direction == RIGHT)
        || (d == RIGHT && direction == LEFT))
        return;

    //蛇头检测
    SnakeNode node = snake[0];
    switch (d)
    {
    case UP:
        node.setPos(snake[0].getX(), (snake[0].getY() - 1 + spaceHeight) % spaceHeight);
        break;
    case DOWN:
        node.setPos(snake[0].getX(), (snake[0].getY() + 1) % spaceHeight);
        break;
    case LEFT:
        node.setPos((snake[0].getX() - 1 + spaceWidth) % spaceWidth, snake[0].getY());
        break;
    case RIGHT:
        node.setPos((snake[0].getX() + 1) % spaceWidth, snake[0].getY());
        break;
    }
    if (node.getX() == snake[1].getX() && node.getY() == snake[1].getY())
    {
        Global::game->step();
    }

    direction = d;
}

int Snake::getDirection()
{
    return direction;
}

void Snake::go()
{
    for (int i = snake.size() - 1; i >= 1; --i)
    {
        snake[i] = snake[i - 1];
    }

    switch (direction)
    {
    case UP:
        snake[0].setPos(snake[0].getX(), (snake[0].getY() - 1 + spaceHeight) % spaceHeight);
        break;
    case DOWN:
        snake[0].setPos(snake[0].getX(), (snake[0].getY() + 1) % spaceHeight);
        break;
    case LEFT:
        snake[0].setPos((snake[0].getX() - 1 + spaceWidth) % spaceWidth, snake[0].getY());
        break;
    case RIGHT:
        snake[0].setPos((snake[0].getX() + 1) % spaceWidth, snake[0].getY());
        break;
    }
}

void Snake::lengthen()
{
    snake.push_back(getTailNode());
}

void Snake::print()
{
    for (int i = 0; i < spaceHeight; ++i)
    {
        for (int j = 0; j < spaceWidth; ++j)
        {
            SnakeNode t(j, i);
            int cnt = count(snake.begin(), snake.end(), t);
            if (cnt == 0)
            {
                cout << ". ";
            }
            else
            {
                cout << "* ";
            }
        }
        cout << endl;
    }
    cout << endl;
}
