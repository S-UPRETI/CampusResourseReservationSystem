#include "ResourceManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

void ResourceManager::loadFromFile(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Could not open " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, name, type, availStr;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, type, ',');
        getline(ss, availStr, ',');

        if (idStr.empty()) continue;

        int id = stoi(idStr);
        bool available = (availStr == "1" || availStr == "true");

        resources.push_back(Resource(id, name, type, available));
    }
    file.close();
}

void ResourceManager::displayAll() const {
    for (const auto& r : resources) {
        r.displayInfo();
    }
}

void ResourceManager::showAvailable() const {
    for (const auto& r : resources) {
        if (r.isAvailable()) {
            r.displayInfo();
        }
    }
}