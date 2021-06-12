#include "engine/Game.h"

int main()
{
    Game game{ "Hamburger VS Pizza", 720, 480, 1, 60 };

    game.gameLoop();

    return 0;
}