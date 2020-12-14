#ifndef VIDEOGAME_H
#define VIDEOGAME_H
#include <iostream>
using namespace std;

class VideoGame
{
private:
    long gameId;
    string title;
    string genre;
    string console;
    double price;
    int players;        //should be in multiplayer need to fix
public:
    VideoGame();
    VideoGame(string title, string genre, string console, double price, int players);
    void setTitle(string title);
    void setGenre(string genre);
    void setConsole(string console);
    void setPrice(double price);
    void setPlayers(int players) {this->players = players;}
    int getPlayers() {return players;}
    void setGameId(long id) {this->gameId = id;}
    long getGameId() {return gameId;}
    string getTitle();
    string getGenre();
    string getConsole();
    double getPrice();
};

#endif // VIDEOGAME_H
