#ifndef USER_H
#define USER_H
#include <iostream>
using namespace std;

class User
{
private:
    string name;
    long id;

public:
    User();
    User(long id);
    User(string name, long id);
    void setName(string name);
    string getName();
    void setId(long id);
    long getId();
};

#endif // USER_H
