#include "EasyDifficulty.h"
#include "Game.h"
#include "SFMLRenderer.h"

int main()
{
    EasyDifficulty difficulty;

    Game game(difficulty, false, true);

    SFMLRenderer renderer(game);

    renderer.run();

    return 0;
}