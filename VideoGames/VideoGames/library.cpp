#include "library.h"
#include "HttpServer.h"
#include <iostream>
using namespace std;

//destructor for library class
Library::~Library() {
    for (auto pair : idUserMap) {
        delete pair.second;
    }
}

//gets next id
long Library::getUniqueId() {
    return nextUniqueId++;
}

//starts program
int main() {
    Library library("Kasey's Game Storage");
    HttpServer server;

    server.startServer(library);

    return 0;
}
