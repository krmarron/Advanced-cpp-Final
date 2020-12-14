#include "multiplayergame.h"

MultiplayerGame::MultiplayerGame()
{

}

MultiplayerGame::MultiplayerGame(int players) {
    setPlayers(players);
}

void MultiplayerGame::setPlayers(int players) {
    this->players = players;
}

int MultiplayerGame::getPlayers() {
    return players;
}
