#include "Resource.h"
#include <iostream>
#include <iomanip>

// Sets default values when a resource is created without details
Resource::Resource()
    : resourceID(""), name(""), type(""),
      available(true), requestCount(0) {
}

// Creates a resource with the given ID, name, type, and availability
Resource::Resource(const std::string& id,
                   const std::string& resourceName,
                   const std::string& resourceType,
                   bool isAvailable)
    : resourceID(id),
      name(resourceName),
      type(resourceType),
      available(isAvailable),
      requestCount(0) {
}

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

int Resource::getRequestCount() const {
    return requestCount;
}

// Increases the number of times this resource is requested
void Resource::recordRequest() {
    ++requestCount;
}

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

// Displays the resource details in aligned columns
void Resource::display() const {
    std::cout << std::left
              << std::setw(8) << resourceID
              << std::setw(20) << name
              << std::setw(24) << type
              << (available ? "Available" : "Unavailable")
              << '\n';
}
