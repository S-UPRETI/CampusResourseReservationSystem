#include "Resource.h"
#include <iostream>
using namespace std;

Resource::Resource(int id, string name, string type, bool available)
    : id(id), name(name), type(type), available(available) {}

int Resource::getId() const { return id; }
string Resource::getName() const { return name; }
string Resource::getType() const { return type; }
bool Resource::isAvailable() const { return available; }
void Resource::setAvailable(bool status) { available = status; }

void Resource::displayInfo() const {
    cout << "[" << id << "] " << name << " - " << type << " - "
         << (available ? "Available" : "Unavailable") << endl;
}