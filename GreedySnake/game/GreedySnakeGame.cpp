#include "GreedySnakeGame.h"
#include "gamepage.h"

///base class: game status
GameStatus::GameStatus(GreedySnakeGame* game)
{
    this->game = game;
}

///WaittingForStart status
WaittingForStart::WaittingForStart(GreedySnakeGame* game) : GameStatus(game){}
void WaittingForStart::step(){}
void WaittingForStart::pause(){}
void WaittingForStart::start()
{
    game->initGame();
    game->setCurrentState(game->getRunningStatus());
    game->notifyListeners(GamePage::STARTING);
}
void WaittingForStart::exit()
{

}
void WaittingForStart::changeDirection(int d){}

///Running status
Running::Running(GreedySnakeGame* game) : GameStatus(game){}
void Running::start(){}
void Running::step()
{
    if (!game->hasFood)
    {
        game->generateFood();
        game->hasFood = true;
    }

    //蛇头检测
    /*SnakeNode node = game->snake->getHeadNode();
    switch(game->snake->getDirection())
    {
    case UP:
        node.setPos(node.getX(), (node.getY() - 1 + spaceHeight) % spaceHeight);
        break;
    case DOWN:
        node.setPos(node.getX(), (node.getY() + 1) % spaceHeight);
        break;
    case LEFT:
        node.setPos((node.getX() - 1 + spaceWidth) % spaceWidth, node.getY());
        break;
    case RIGHT:
        node.setPos((node.getX() + 1) % spaceWidth, node.getY());
        break;
    }
    if (node.getX() == game->snake->getSnakeNode(1).getX() && node.getY() == game->snake->getSnakeNode(1).getY())
    {
        //go();
        game->gameMap[game->snake->getTailNode().getY()][game->snake->getTailNode().getX()] = GreedySnakeGame::BLANK;
        game->snake->go();
    }*/

    game->gameMap[game->snake->getTailNode().getY()][game->snake->getTailNode().getX()] = GreedySnakeGame::BLANK;
    game->snake->go();
    if (game->gameMap[game->snake->getHeadNode().getY()][game->snake->getHeadNode().getX()] == GreedySnakeGame::BODY)
    {
        game->setCurrentState(game->getWaittingForStartStatus());
        game->notifyListeners(GamePage::GAMEOVER);
        //game->notifyListeners(GamePage::WAITTING);
        return;
    }
    game->gameMap[game->snake->getHeadNode().getY()][game->snake->getHeadNode().getX()] = GreedySnakeGame::BODY;
    //updateMap();
    game->notifyListeners(GamePage::RUNNING);

    //game->launchSnake();
    if (game->snake->getHeadNode().getX() == game->xFood && game->snake->getHeadNode().getY() == game->yFood)
    {
        game->hasFood = false;
        game->snake->lengthen();
        game->score++;
        if (game->score % 5 == 0)
        {
            game->speed -= 10;
            game->speed = max(game->speed, 10);
            game->notifyListeners(GamePage::SPEEDCHANGED);
        }
        game->notifyListeners(GamePage::LONGER);
    }
    game->notifyListeners(GamePage::RUNNING);

    //Sleep(game->speed);
}
void Running::pause()
{
    game->setCurrentState(game->getPausingStatus());
    game->notifyListeners(GamePage::PAUSING);
}
void Running::exit()
{
    game->setCurrentState(game->getWaittingForStartStatus());
    game->notifyListeners(GamePage::WAITTING);
}
void Running::changeDirection(int d)
{
    //game->step();
    game->notifyListeners(GamePage::RUNNING);
    game->setDirection(d);

}

///Pausing status
Pausing::Pausing(GreedySnakeGame* game) : GameStatus(game){}
void Pausing::step(){}
void Pausing::pause(){}
void Pausing::changeDirection(int d){}
void Pausing::start()
{
    //cout << "continue game" << endl;
    game->setCurrentState(game->getRunningStatus());
    game->notifyListeners(GamePage::CONTINUE);
    //game->notifyListeners(GamePage::RUNNING);
}
void Pausing::exit()
{
    game->setCurrentState(game->getWaittingForStartStatus());
    game->notifyListeners(GamePage::WAITTING);
}

///game holder
void GreedySnakeGame::initGame()
{
    snake->initSnake();
    updateMap();
    hasFood = false;
    score = 0;
    speed = 150;
}

void GreedySnakeGame::updateMap()
{
    for (int i = 0; i < spaceHeight; ++i)
    {
        for (int j = 0; j < spaceWidth; ++j)
        {
            gameMap[i][j] = BLANK;
        }
    }
    for (int i = 0; i < snake->getLength(); ++i)
    {
        gameMap[snake->getSnakeNode(i).getY()][snake->getSnakeNode(i).getX()] = BODY;
    }
}

GreedySnakeGame::GreedySnakeGame(int spaceWidth, int spaceHeight, int initLength)
{
    assert(spaceWidth > 5 && spaceHeight > 5 && initLength < spaceHeight);

    ///init game basic data
    this->spaceWidth = spaceWidth;
    this->spaceHeight = spaceHeight;
    this->initLength = initLength;

    ///init snake
    snake = new Snake(spaceWidth, spaceHeight, initLength);

    ///set map size
    gameMap.resize(spaceHeight);
    for (int i = 0; i <spaceHeight; ++i)
    {
        gameMap[i].resize(spaceWidth);
    }

    ///update map
    //updateMap();

    ///init status
    waittingForStartStatus = new WaittingForStart(this);
    runningStatus = new Running(this);
    pausingStatus = new Pausing(this);
    currentStatus = waittingForStartStatus;

    //hasFood = false;
    initGame();
}

GreedySnakeGame::~GreedySnakeGame()
{
    if (snake != NULL)
        delete snake;
    if (waittingForStartStatus != NULL)
        delete waittingForStartStatus;
    if (runningStatus != NULL)
        delete runningStatus;
    if (pausingStatus != NULL)
        delete pausingStatus;
}

/*void GreedySnakeGame::printMap() const
{
    for (int i = 0; i < spaceHeight; ++i)
    {
        for (int j = 0; j < spaceWidth; ++j)
        {
            if (gameMap[i][j] == BLANK)
                cout << "  ";
            else if (gameMap[i][j] == BODY)
                cout << "* ";
            else if (gameMap[i][j] == FOOD)
                cout << "+ ";
        }
        cout << endl;
    }
    cout << endl;
}*/

void GreedySnakeGame::launchSnake()
{
    gameMap[snake->getTailNode().getY()][snake->getTailNode().getX()] = BLANK;
    snake->go();
    gameMap[snake->getHeadNode().getY()][snake->getHeadNode().getX()] = BODY;
    //updateMap();
    notifyListeners(GamePage::RUNNING);
}

void GreedySnakeGame::setDirection(int d)
{
    snake->setDirection(d);
}

void GreedySnakeGame::setCurrentState(GameStatus* status)
{
    currentStatus = status;
}

GameStatus* GreedySnakeGame::getWaittingForStartStatus() const
{
    return waittingForStartStatus;
}

GameStatus* GreedySnakeGame::getRunningStatus() const
{
    return runningStatus;
}
GameStatus* GreedySnakeGame::getPausingStatus() const
{
    return pausingStatus;
}

void GreedySnakeGame::start()
{
    currentStatus->start();
}

void GreedySnakeGame::step()
{
    currentStatus->step();
}

void GreedySnakeGame::pause()
{
    currentStatus->pause();
}

void GreedySnakeGame::exit()
{
    currentStatus->exit();
}

void GreedySnakeGame::changeDirection(int d)
{
    currentStatus->changeDirection(d);
}

void GreedySnakeGame::generateFood()
{
    srand((unsigned)time(NULL));
    xFood = rand() % spaceWidth;
    yFood = rand() % spaceHeight;
    while (gameMap[yFood][xFood] == BODY)
    {
        xFood = rand() % spaceWidth;
        yFood = rand() % spaceHeight;
    }
    gameMap[yFood][xFood] = FOOD;
}

bool GreedySnakeGame::getHasFood()
{
    return hasFood;
}

void GreedySnakeGame::setHasFood(bool hasFood)
{
    this->hasFood = hasFood;
}

///observer mode
void GreedySnakeGame::registerGamePage(GamePage* painter)
{
    registerListener(painter);
    painter->game = this;
}
