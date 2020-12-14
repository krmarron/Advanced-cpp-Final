#ifndef MULTIPLAYERGAME_H
#define MULTIPLAYERGAME_H
#include "videogame.h"

//Multiplayer class (Child of VideoGame class) (Currently unused)
class MultiplayerGame : public VideoGame
{
private:
    int players;
public:
    MultiplayerGame();
    MultiplayerGame(int players);
    void setPlayers(int players);
    int getPlayers();
};

#endif // MULTIPLAYERGAME_H
