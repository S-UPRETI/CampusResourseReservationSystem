#include "Resource.h"
#include <iostream>
#include <iomanip>

Resource::Resource()
    : resourceID(""), name(""), type(""), available(true) {}

Resource::Resource(const std::string& resourceID,
                    const std::string& name,
                    const std::string& type,
                    bool available)
    : resourceID(resourceID), name(name), type(type), available(available) {}

// ---- Getters ----
std::string Resource::getResourceID() const {
    return resourceID;
}

std::string Resource::getName() const {
    return name;
}

std::string Resource::getType() const {
    return type;
}

bool Resource::isAvailable() const {
    return available;
}

// ---- Setters ----
void Resource::setResourceID(const std::string& id) {
    resourceID = id;
}

void Resource::setName(const std::string& newName) {
    name = newName;
}

void Resource::setType(const std::string& newType) {
    type = newType;
}

void Resource::setAvailable(bool status) {
    available = status;
}

// ---- Display ----
void Resource::display() const {
    std::cout << std::left
              << std::setw(8)  << resourceID
              << std::setw(20) << name
              << std::setw(20) << type
              << (available ? "Available" : "Unavailable")
              << std::endl;
}
