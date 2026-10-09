#include "ResourceManager.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>

ResourceManager::ResourceManager() = default;

// Splits each line from the file into separate values
static std::vector<std::string> splitLine(
    const std::string& line,
    char delimiter
) {
    std::vector<std::string> tokens;
    std::stringstream stream(line);
    std::string token;

    while (std::getline(stream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

// Decides the order of resources by name or request count
static bool resourceComesBefore(
    const Resource& a,
    const Resource& b,
    bool byRequests
) {
    if (byRequests &&
        a.getRequestCount() != b.getRequestCount()) {
        return a.getRequestCount() > b.getRequestCount();
    }

    if (!byRequests && a.getName() != b.getName()) {
        return a.getName() < b.getName();
    }

    return a.getResourceID() < b.getResourceID();
}

// Combines two sorted sections into one sorted section
// This is part of our own Merge Sort implementation
static void mergeResources(
    std::vector<Resource>& items,
    int left,
    int middle,
    int right,
    bool byRequests
) {
    std::vector<Resource> temp;

    int i = left;
    int j = middle + 1;

    while (i <= middle && j <= right) {
        if (resourceComesBefore(
                items[i], items[j], byRequests)) {
            temp.push_back(items[i]);
            ++i;
        } else {
            temp.push_back(items[j]);
            ++j;
        }
    }

    while (i <= middle) {
        temp.push_back(items[i]);
        ++i;
    }

    while (j <= right) {
        temp.push_back(items[j]);
        ++j;
    }

    for (int k = 0; k < static_cast<int>(temp.size()); ++k) {
        items[left + k] = temp[k];
    }
}

// Uses recursion to divide the resources and sort each part
static void mergeSortResources(
    std::vector<Resource>& items,
    int left,
    int right,
    bool byRequests
) {
    if (left >= right) {
        return;
    }

    int middle = left + (right - left) / 2;

    mergeSortResources(items, left, middle, byRequests);

    mergeSortResources(items, middle + 1, right, byRequests);

    mergeResources(items, left, middle, right, byRequests);
}

// Reads resource information from a file and stores it in the vector
bool ResourceManager::loadFromFile(
    const std::string& filename
) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: could not open file "
                  << filename << '\n';
        return false;
    }

    resources.clear();

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '/') {
            continue;
        }

        std::vector<std::string> tokens =
            splitLine(line, '|');

        if (tokens.size() < 4) {
            std::cerr
                << "Warning: skipping malformed resource line: "
                << line << '\n';
            continue;
        }

        std::string status = tokens[3];

        if (!status.empty() && status.back() == '\r') {
            status.pop_back();
        }

        resources.emplace_back(
            tokens[0],
            tokens[1],
            tokens[2],
            status == "Available"
        );
    }

    return !resources.empty();
}

// Displays all resources in the system
void ResourceManager::displayAll() const {
    if (resources.empty()) {
        std::cout << "No resources loaded.\n";
        return;
    }

    std::cout << std::left
              << std::setw(8) << "ID"
              << std::setw(20) << "Name"
              << std::setw(24) << "Type"
              << "Status\n";

    std::cout << std::string(62, '-') << '\n';

    for (const auto& resource : resources) {
        resource.display();
    }
}

// Displays only resources that are currently available
void ResourceManager::displayAvailable() const {
    bool found = false;

    std::cout << std::left
              << std::setw(8) << "ID"
              << std::setw(20) << "Name"
              << std::setw(24) << "Type"
              << "Status\n";

    std::cout << std::string(62, '-') << '\n';

    for (const auto& resource : resources) {
        if (resource.isAvailable()) {
            resource.display();
            found = true;
        }
    }

    if (!found) {
        std::cout << "No available resources found.\n";
    }
}

// OUR OWN LINEAR SEARCH.
// Checks each resource ID until it finds a match
Resource* ResourceManager::findResource(
    const std::string& resourceID
) {
    for (auto& resource : resources) {
        if (resource.getResourceID() == resourceID) {
            return &resource;
        }
    }

    return nullptr;
}

// Changes the availability status of a resource
bool ResourceManager::setResourceAvailability(
    const std::string& resourceID,
    bool available
) {
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

const std::vector<Resource>&
ResourceManager::getAllResources() const {
    return resources;
}

// Updates the request count when a resource is requested
bool ResourceManager::recordRequest(
    const std::string& resourceID
) {
    Resource* resource = findResource(resourceID);

    if (resource == nullptr) {
        return false;
    }

    resource->recordRequest();
    return true;
}

// OUR OWN MERGE SORT.
// Sorts resources alphabetically by name
void ResourceManager::sortResourcesByName() {
    if (resources.size() > 1) {
        mergeSortResources(
            resources,
            0,
            static_cast<int>(resources.size()) - 1,
            false
        );
    }
}

void ResourceManager::displayMostRequestedResources() const {
    if (resources.empty()) {
        std::cout << "No resources loaded.\n";
        return;
    }

    std::vector<Resource> sorted = resources;

    if (sorted.size() > 1) {
        mergeSortResources(
            sorted,
            0,
            static_cast<int>(sorted.size()) - 1,
            true
        );
    }

    std::cout
        << "\n=== MOST REQUESTED RESOURCES "
        << "(current program run) ===\n";

    std::cout << std::left
              << std::setw(6) << "Rank"
              << std::setw(10) << "ID"
              << std::setw(24) << "Resource"
              << "Requests\n";

    int rank = 1;

    for (const auto& resource : sorted) {
        std::cout << std::left
                  << std::setw(6) << rank++
                  << std::setw(10) << resource.getResourceID()
                  << std::setw(24) << resource.getName()
                  << resource.getRequestCount()
                  << '\n';
    }
}
