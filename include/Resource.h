#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
using namespace std;

class Resource {
private:
    int id;
    string name;
    string type;
    bool available;

public:
    Resource(int id, string name, string type, bool available);

    int getId() const;
    string getName() const;
    string getType() const;
    bool isAvailable() const;
    void setAvailable(bool status);

    void displayInfo() const;
};

#endif