#include "ResourceManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>

ResourceManager::ResourceManager() {}

// Splits a pipe-delimited line into tokens
static std::vector<std::string> splitLine(const std::string& line, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

bool ResourceManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: could not open file " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Skip blank lines and comment lines (e.g. "//sample resources.txt data")
        if (line.empty() || line[0] == '/' ) {
            continue;
        }

        std::vector<std::string> tokens = splitLine(line, '|');
        if (tokens.size() < 4) {
            std::cerr << "Warning: skipping malformed line: " << line << std::endl;
            continue;
        }

        std::string id     = tokens[0];
        std::string name   = tokens[1];
        std::string type   = tokens[2];
        std::string status = tokens[3];

        // Trim possible trailing '\r' (Windows line endings) or whitespace
        if (!status.empty() && (status.back() == '\r' || status.back() == '\n')) {
            status.pop_back();
        }

        bool isAvailable = (status == "Available");

        resources.push_back(Resource(id, name, type, isAvailable));
    }

    file.close();
    return true;
}

void ResourceManager::displayAll() const {
    if (resources.empty()) {
        std::cout << "No resources loaded." << std::endl;
        return;
    }

    std::cout << std::left
              << std::setw(8)  << "ID"
              << std::setw(20) << "Name"
              << std::setw(20) << "Type"
              << "Status" << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    for (const auto& resource : resources) {
        resource.display();
    }
}

void ResourceManager::displayAvailable() const {
    bool foundAny = false;

    std::cout << std::left
              << std::setw(8)  << "ID"
              << std::setw(20) << "Name"
              << std::setw(20) << "Type"
              << "Status" << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    for (const auto& resource : resources) {
        if (resource.isAvailable()) {
            resource.display();
            foundAny = true;
        }
    }

    if (!foundAny) {
        std::cout << "No available resources found." << std::endl;
    }
}

Resource* ResourceManager::findResource(const std::string& resourceID) {
    for (auto& resource : resources) {
        if (resource.getResourceID() == resourceID) {
            return &resource;
        }
    }
    return nullptr;
}

bool ResourceManager::setResourceAvailability(const std::string& resourceID, bool available) {
    Resource* resource = findResource(resourceID);
    if (resource == nullptr) {
        return false;
    }
    resource->setAvailable(available);
    return true;
}

int ResourceManager::getResourceCount() const {
    return static_cast<int>(resources.size());
}

const std::vector<Resource>& ResourceManager::getAllResources() const {
    return resources;
}
