#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <vector>
#include "Resource.h"


class ResourceManager {
private:
    std::vector<Resource> resources;

public:
    ResourceManager();

    bool loadFromFile(const std::string& filename);

   
    void displayAll() const;

   
    void displayAvailable() const;

   
    Resource* findResource(const std::string& resourceID);

   
    bool setResourceAvailability(const std::string& resourceID, bool available);

   
    int getResourceCount() const;

    
    const std::vector<Resource>& getAllResources() const;
};

#endif 
