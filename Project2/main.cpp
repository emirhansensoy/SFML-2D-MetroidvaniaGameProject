#include "stdafx.h"
#include "Game.h"

int main()
{
    srand(static_cast<unsigned>(time(NULL)));

    Game game;

    game.run();

    return 0;
}