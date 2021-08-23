#include "Game.h"
#include <string>
#define GAME_WIDTH 1210
#define GAME_HEIGHT 660

using namespace std;

static Stage gameStage;

int main(int args, char* argv[]) {

    Game* game = new Game;
    game->initialize("Bomberman", GAME_WIDTH, GAME_HEIGHT, false);
    game->loadStage(JUNGLE);

    while(game->isRunning()) {
        game->handleEvent();
        game->update();
        game->render();
    }

    game->clean();
    delete game;

    return 0;
}
