#ifndef DATABASE_H
#define DATABASE_H


#include <iostream>
#include <string>
#include "user.h"
#include "gamerequest.h"
#include <memory>
#include <vector>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

class Database
{
private:
    QSqlDatabase db;            //Initialize QSqlDatabase
    long getLatestRowId();      //Generates Next ID for database entries
    QString DRIVER;             //Initialize DRIVER QString for database connection
public:
    //Constructor
    Database();

    //Open Database
    void open();

    //Close Database
    void close();

    //Generate Database with test data
    void rebuildTestDatabase();

    //Perform a game request (Currently Unused)
    void performGameRequest(/*GameRequest &request*/);

    //Add a game to database (Currently Non-Functional)
    void addGame(QVariant, QVariant, QVariant, QVariant, QVariant);

    //Get a user from database (Currently Non-Functional)
    void getUser(long long userId, User &user);

    //Get all users from database (Currently Non-Functional)
    unique_ptr<QSqlQuery> getUsers();

    //Get all games from database (Currently Non-Functional)
    vector<unique_ptr<VideoGame>> getGames();

    //Get database connection (Currently unused)(Possibly not needed)
    QSqlDatabase getDatabase() {return db;}
};

#endif // DATABASE_H
