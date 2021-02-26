#include "engine/Game.h"

int main()
{
    Game game{ "Hamburger VS Pizza", 150, 100, 8, 10 };

    game.gameLoop();

    return 0;
}