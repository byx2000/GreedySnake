#pragma once

#include <vector>
#include <windows.h>
#include <ctime>
#include "Snake.h"
#include "ObserverMode.h"
#include "gamepage.h"

/*
    Definition of all game data structure
    The structure stores all relevant data of the game,
    and provides various operations for the game.
*/
class GreedySnakeGame;
class GamePage;

class GameStatus
{
protected:
    GreedySnakeGame* game;
public:
    GameStatus(GreedySnakeGame* game);
    virtual void start() = 0;
    virtual void step() = 0;
    virtual void pause() = 0;
    virtual void exit() = 0;
    virtual void changeDirection(int d) = 0;
    virtual ~GameStatus(){}
};

class WaittingForStart : public GameStatus
{
public:
    WaittingForStart(GreedySnakeGame* game);
    void start();
    void step();
    void pause();
    void exit();
    void changeDirection(int d);
};

class Running : public GameStatus
{
public:
    Running(GreedySnakeGame* game);
    void start();
    void step();
    void pause();
    void exit();
    void changeDirection(int d);
};

class Pausing : public GameStatus
{
public:
    Pausing(GreedySnakeGame* game);
    void start();
    void step();
    void pause();
    void exit();
    void changeDirection(int d);
};

class GreedySnakeGame : public DataSource
{
private:
    int spaceWidth, spaceHeight;
    int initLength;
    Snake* snake;
    vector<vector<int>> gameMap;
    bool hasFood;
    int xFood, yFood;
    int score;
    int speed;

    WaittingForStart* waittingForStartStatus;
    Running* runningStatus;
    Pausing* pausingStatus;
    GameStatus* currentStatus;

    void updateMap();
public:
    enum {BLANK, BODY, FOOD};

    friend class WaittingForStart;
    friend class Running;
    friend class Pausing;
    friend class GameStatus;
    friend class GamePage;

    void generateFood();
    bool getHasFood();
    void setHasFood(bool hasFood);
    GreedySnakeGame(int spaceWidth, int spaceHeight, int initLength);
    ~GreedySnakeGame();
    void initGame();
    void printMap() const;
    void setCurrentState(GameStatus* status);
    GameStatus* getWaittingForStartStatus() const;
    GameStatus* getRunningStatus() const;
    GameStatus* getPausingStatus() const;
    void launchSnake();
    void setDirection(int d);
    void start();
    void step();
    void pause();
    void exit();
    void changeDirection(int d);

    void registerGamePage(GamePage* painter);
};
