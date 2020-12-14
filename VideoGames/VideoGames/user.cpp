#include "user.h"

User::User()
{

}

User::User(long id) {
    setId(id);
}

User::User(string name, long id) {
    setName(name);
    setId(id);
}

void User::setName(string name) {
    this->name = name;
}

string User::getName() {
    return name;
}

void User::setId(long id) {
    this->id = id;
}

long User::getId() {
    return id;
}
