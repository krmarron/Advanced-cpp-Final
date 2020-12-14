#include "database.h"

//create database
Database::Database()
{
    cout << "********* CREATING DATABASE ***************" << endl;
    DRIVER = QString("QSQLITE");
    if(!QSqlDatabase::isDriverAvailable(DRIVER)){
        qWarning() << "ERROR: driver not available";
    }
}

//open connection
void Database::open() {
    cout << "************* OPENING DATABASE ****************" << endl;
    db = QSqlDatabase::addDatabase(DRIVER);
    db.setDatabaseName("videogames.sqlite");
    if(!db.open()) {
        qWarning() << "ERROR: " << db.lastError();
    }
}

//close connection
void Database::close() {
    cout << "********* CLOSING DATABASE *************" << endl;
    db.close();
    QSqlDatabase::removeDatabase(DRIVER);
}

//generate test data (DOESNT WORK)****************************************************
void Database::rebuildTestDatabase() {
    //recreate tables
    QSqlQuery query;
    query.exec("DROP TABLE IF EXISTS User");
    query.exec("DROP TABLE IF EXISTS Games");
    query.exec("DROP TABLE IF EXISTS Library");

    query.exec("CREATE TABLE User (UserId INTEGER PRIMARY KEY, Name TEXT)");
    query.exec("CREATE TABLE Games (GameId INTEGER PRIMARY KEY, Title TEXT, Genre TEXT, Console TEXT, Price REAL, Players Real)");
    query.exec("CREATE TABLE Library (UserId INTEGER FOREIGN KEY, GameId INTEGER)");

    //add users
    QSqlQuery insertUser;
    insertUser.prepare("INSERT INTO User (Name) VALUES (:name)");
    insertUser.bindValue(":name", "Kasey");
    insertUser.exec();
    long long userId1 = getLatestRowId();
    insertUser.bindValue(":name", "Jordan");
    insertUser.exec();
    long long userId2 = getLatestRowId();

    //add game
    QSqlQuery insertGame;
    insertGame.prepare("INSERT INTO Games (Title, Genre, Console, Price) VALUES (:title, :genre, :console, :price)");
    insertGame.addBindValue("Call of Duty: Cold War");
    insertGame.addBindValue("FPS");
    insertGame.addBindValue("PC");
    insertGame.addBindValue(59.99);
    insertGame.exec();
    long long gameId = getLatestRowId();

}

//perform game request (UNUSED) (ALTERED FOR TEST DATA)
void Database::performGameRequest(/*GameRequest &request*/) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Games");
    query.exec();

}

//get user from database
void Database::getUser(long long userId, User &user) {
    QSqlQuery query;
    query.prepare("SELECT UserId, Name FROM User WHERE UserId = ?");
    query.addBindValue(userId);
    query.exec();
    query.next();
    user.setId(query.value(0).toLongLong());
}

//Get all users from database
unique_ptr<QSqlQuery> Database::getUsers() {
    auto queryPtr = make_unique<QSqlQuery>();
    queryPtr->exec("SELECT UserId, Name FROM User");
    return queryPtr;
}

//generate next row id
long Database::getLatestRowId() {
    QSqlQuery query;
    query.exec("SELECT last_insert_rowid()");
    query.next();
    return query.value(0).toLongLong();
}

//get all games
vector<unique_ptr<VideoGame>> Database::getGames() {
    Database db;
    db.open();
    auto queryPtr = make_unique<QSqlQuery>();
    queryPtr->exec("SELECT * FROM Games");
    vector<unique_ptr<VideoGame>> games;

    while (queryPtr->next()) {
        QString title = queryPtr->value(0).toString();
        string t = title.toStdString();
        QString genre = queryPtr->value(1).toString();
        string g = genre.toStdString();
        QString console = queryPtr->value(2).toString();
        string c = console.toStdString();
        double price = queryPtr->value(3).toDouble();
        int players = queryPtr->value(4).toInt();
        unique_ptr<VideoGame> game = make_unique<VideoGame>(t, g, c, price, players);
    }
    db.close();
    return games;

}

//add a game to database
void Database:: addGame(QVariant title, QVariant genre, QVariant console, QVariant price, QVariant players) {
    Database db;
    db.open();
    QSqlQuery addGame;
    addGame.prepare("INSERT INTO Games (Title, Genre, Console, Price, Players) VALUES (:title, :genre, :console, :price, :players)");
    addGame.addBindValue(title);
    addGame.addBindValue(genre);
    addGame.addBindValue(console);
    addGame.addBindValue(price);
    addGame.addBindValue(players);
    addGame.exec();
    db.close();
}
