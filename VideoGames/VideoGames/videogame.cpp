#include "videogame.h"

VideoGame::VideoGame()
{

}

VideoGame::VideoGame(string title, string genre, string console, double price, int players) {
    setTitle(title);
    setGenre(genre);
    setConsole(console);
    setPrice(price);
    setPlayers(players);
}

void VideoGame::setTitle(string title) {
    this->title = title;
}

void VideoGame::setGenre(string genre) {
    this->genre = genre;
}

void VideoGame::setConsole(string console) {
    this->console = console;
}

void VideoGame::setPrice(double price) {
    this->price = price;
}

string VideoGame::getTitle() {
    return title;
}

string VideoGame::getGenre() {
    return genre;
}

string VideoGame::getConsole() {
    return console;
}

double VideoGame::getPrice() {
    return price;
}
