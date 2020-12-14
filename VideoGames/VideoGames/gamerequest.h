#ifndef GAMEREQUEST_H
#define GAMEREQUEST_H

#include "user.h"
#include "videogame.h"
#include "multiplayergame.h"
#include <time.h>

/* *********************CLASS NOT USED************************* */

//Initialize user class
class User;

//Initialize VideoGame class
class VideoGame;

//Initialize MultiplayerGame class
class MultiplayerGame;

//Game Request Class
class GameRequest {
private:
    long requestId;             //request id
    User& user;                 //user to be altered
    VideoGame& game;            //videogame to be altered
    MultiplayerGame& mGame;     //multiplayer game to be altered
    time_t timestamp;           //time of request
    friend class Database;      //database access
public:
    //Constructors
    GameRequest(long requestId, User& user, VideoGame& game, time_t timestamp);
    GameRequest(long requestId, User& user, MultiplayerGame& mgame, time_t timestamp);

    //Getters and Setters
    long getId() const {return requestId;}
    VideoGame& getGame() const {return game;}
    MultiplayerGame& getMGame() const {return mGame;}
    void setRequestId(long long id) {requestId = id;}
    void setTimestamp(time_t time) {timestamp = time;}
};

#endif // GAMEREQUEST_H
