#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "Resource.h"
#include <vector>
#include <string>
using namespace std;

class ResourceManager {
private:
    vector<Resource> resources;

public:
    void loadFromFile(string filename);
    void displayAll() const;
    void showAvailable() const;
};

#endif
