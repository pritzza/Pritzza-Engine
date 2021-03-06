#include "engine/Game.h"

int main()
{
    Game game{ "Hamburger VS Pizza", 150, 100, 4, 60 };

    game.gameLoop();

    return 0;
}