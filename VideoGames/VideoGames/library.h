#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <map>
#include "user.h"
#include "database.h"
using namespace std;

class Library
{
private:
    string name;                    //library name
    map<long, User*> idUserMap;     //map to connect games to users
    long nextUniqueId = 1000;       //generate ids
    Database database;              //create database connection
public:
    //constructor
    Library(string name) : name(name), database() {

    }

    //destructor
    ~Library();

    //Getters and setters
    void setName(string name) {this->name = name;}
    string getName() const {return name;}
    Database& getDatabase() {return database;}
    long getUniqueId();

};

#endif // LIBRARY_H
