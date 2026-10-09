#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <vector>
#include "Resource.h"

// Stores and manages all the resources in the system
class ResourceManager {
private:
    std::vector<Resource> resources; // List of resources

public:
    ResourceManager();

    // Loads resource information from a file
    bool loadFromFile(const std::string& filename);

    // Displays all resources or only available ones
    void displayAll() const;
    void displayAvailable() const;

    // Finds a resource using its ID
    Resource* findResource(const std::string& resourceID);

    // Changes the availability of a resource
    bool setResourceAvailability(
        const std::string& resourceID,
        bool available
    );

     // Returns the total number of resources
    int getResourceCount() const;

     // Gives access to the resource list without changing it
    const std::vector<Resource>& getAllResources() const;

    // Updates the request count for a resource
    bool recordRequest(const std::string& resourceID);

   // Sorts resources by name using merge sort
    void sortResourcesByName();

    // Shows resources based on how many times they were requested
    void displayMostRequestedResources() const;
};

#endif
