#ifndef GLOBAL_H
#define GLOBAL_H

#include "waittingpage.h"
#include "hintpage.h"
#include "aboutpage.h"
#include "gamepage.h"
#include "pausingpage.h"
#include "game/GreedySnakeGame.h"

class Global
{
public:
    static WaittingPage* waittingPage;
    static HintPage* hintPage;
    static AboutPage* aboutPage;
    static GamePage* gamePage;
    static PausingPage* pausingPage;
    static QWidget* lastPage;
    static GreedySnakeGame* game;
    static int maxLength;
    static bool hasPopToast;
    static bool needToShowBuffer;
};

#endif // GLOBAL_H
