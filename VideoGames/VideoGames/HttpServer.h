#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <QtCore>
#include <QCoreApplication>
#include <QDir>
#include "httplib.h"
#include "database.h"
#include "library.h"

Q_DECLARE_METATYPE(std::string)

using namespace std;
using namespace httplib;

class HttpServer {
private:
    char* domain = "localhost";     //Domain name
    int port = 8080;                //Port for domain
public:
    //Start server
    void startServer(Library library) {
        Server svr;

        //Main menu
        svr.Get("/", [this](const Request&, Response& res) {

            //create body of webpage
            stringstream body;
            body << "<html><h1>Welcome to Kasey's Game Storage Service</h1>";
            body << "<p><a href = ../addGame>Add a Game</a></p>";
            body << "<p><a href = ../addUser>Add a User</a></p>";
            body << "<p><a href = ../viewGames>View All Games</a></p>";
            res.set_content(body.str(), "text/html");
        });

        //Get Mapping for view games
        svr.Get("/viewGames", [&](const Request&, Response& res) {

            //Create database connection
            Database database;

            //open connection
            database.open();

            //QSqlQuery to select all games from database
            QSqlQuery q;
            q.prepare("SELECT * FROM Games");

            //create body of webpage
            stringstream body;
            body << "<html>"
                    "<h1>View Games</h1>"
                    "<p>" << q.exec() << "</p>"
                    "<p><a href = ../>Back to main</a></p>"
                    "</html>";
            res.set_content(body.str(), "text/html");

            //close connection
            database.close();
        });

        //Get Mapping for add user
        svr.Get("/addUser", [this](const Request&, Response& res) {

            //Create body of webpage
            stringstream body;
            body << "<html><h1>Add a user</h1>"
                    "<form method = 'post'>"
                    "User Id: <input type = 'text' name = 'user_id'><br />"
                    "Name: <input type = 'text' name = 'name'><br />"

                    "<input type = 'submit' value = 'Submit' />"
                    "</form>"
                    "<p><a href = ../>Back to main</a></p>"
                    "</html>";
            res.set_content(body.str(), "text/html");
        });

        //Post Mapping for add user
        svr.Post("/addUser", [&](const Request& req, Response& res) {

            //Create database connection
            Database database;

            //open connection
            database.open();

            //get data from add user form and convert to usable datatype
            string name = req.get_param_value("name");
            QVariant n(QVariant::fromValue<std::string>(name));

            //add data into database
            QSqlQuery q;
            q.exec("INSERT INTO User(UserId, Name) VALUES (4, :name)");

            //get all users from database (For test purposes) *****WILL BE REMOVED*****
            QSqlQuery query;
            q.prepare("SELECT * FROM User");

            //create body of webpage
            stringstream body;
            body <<"<html>"
                   "<h1>User Added</h1>"
                   "<p>Name: " << name << "</p>"
                   "<p><a href = ../>Back to main</a></p>";
            res.set_content(body.str(), "text/html");

            //Show all users (for test purposes) *****WILL BE REMOVED*****
            cout << query.exec() << endl;

            //close connection
            database.close();
        });

        //Get Mapping for add game
        svr.Get("/addGame", [&](const Request&, Response& res) {

            //create body of webpage
            stringstream body;
            body << "<html><h1>Add a game</h1>";
            body << "<form method = 'post'>"
                        "Title: <input type = 'text' name = 'title'><br />"
                        "Genre: <input type = 'text' name = 'genre'><br />"
                        "Console: <input type = 'text' name = 'console'><br />"
                        "Price: <input type = 'text' name = 'price'><br />"
                        "Players: <input type = 'text' name = 'players'><br />"

                        "<input type = 'submit' value = 'Submit' />"
                   "</form>"
                   "<p><a href = ../>Back to main</a></p>";
            body << "</html>";
            res.set_content(body.str(), "text/html");
        });

        //Post Mapping for add game
        svr.Post("/addGame", [&](const Request& req, Response& res) {

            //create database connection
            Database database;

            //open connection
            database.open();

            //register string datatype to qmeta library (from stack overflow)
            qRegisterMetaType<std::string>("std::string");

            //Convert data from add game form to useable datatypes
            string title = req.get_param_value("title");
            QVariant t(QVariant::fromValue<std::string>(title));
            string genre = req.get_param_value("genre");
            QVariant g(QVariant::fromValue<std::string>(genre));
            string console = req.get_param_value("console");
            QVariant c(QVariant::fromValue<std::string>(console));
            string price = req.get_param_value("price");
            QVariant cost(QVariant::fromValue<std::string>(price));
            string players = req.get_param_value("players");
            QVariant p(QVariant::fromValue<std::string>(players));

            //QSqlQuery to add game to database
            QSqlQuery q;
            q.exec("INSERT INTO Games (Title, Genre, Console, Price, Players) VALUES (t, g, c, cost, p)");

            //QSqlQuery to show all games (For testing purposes) *****WILL BE REMOVED*****
            QSqlQuery query;
            q.prepare("SELECT * FROM Games");

            //create body of webpage
            stringstream body;
            body << "<html>"
                    "<h1>Game added</h1>"
                    "<p>Title: " << title << "</p>"
                    "<p>Genre: " << genre << "</p>"
                    "<p>Console: " << console << "</p>"
                    "<p>Price: $" << price << "</p>"
                    "<p>Players: " << players << "</p>"
                    "<p><a href = ../>Back to main</a></p>"
                    "</html>";
            res.set_content(body.str(), "text/html");

            //show all games in database (For testing purposes) *****WILL BE REMOVED*****
            cout << query.exec() << endl;

            //close connection
            database.close();
        });

        //Get mapping for users (unused)(from bank example)
        svr.Get(R"(/users/(\d+))", [&](const Request& req, Response& res) {
            Database database;
            database.open();

            int userId = stoi(string(req.matches[1]));

            stringstream body;
            body <<"<html>";
            User user(userId);
            library.getDatabase().getUser(userId, user);
            body << "<h1>User " << user.getId() << "</h1>";
            body << "Name: " << user.getName() <<
            "<p><a href = ../>Back to main</a></p>";
            body << "</html>";
            res.set_content(body.str(), "text/html");
            database.close();
        });

        //Start server output to console
        cout << "Starting server at http://" << domain << ":" << port << endl;
        svr.listen(domain, port);
    }
};

#endif // HTTPSERVER_H
