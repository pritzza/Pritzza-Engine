#include "engine/Game.h"

int main()
{
    Game game{ "Hamburger VS Pizza", 1500, 1000, 1, 60 };

    game.gameLoop();

    return 0;
}