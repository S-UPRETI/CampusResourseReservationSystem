#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

// This class stores information about each resource
class Resource {
private:
    std::string resourceID;   
    std::string name;         
    std::string type;   
    bool available;    
    int requestCount;

public:
   // Creates a resource with default values.
   Resource();

    // Initializes a resource with its details.
    Resource(const std::string& resourceID,
              const std::string& name,
              const std::string& type,
              bool available);

    // Returns the resource details.
    std::string getResourceID() const;
    std::string getName() const;
    std::string getType() const;

    bool isAvailable() const;
    int getRequestCount() const;

    // Increases the request count by one
    void recordRequest();

    // Updates resource information
    void setResourceID(const std::string& id);
    void setName(const std::string& newName);
    void setType(const std::string& newType);
    void setAvailable(bool status);

    // Displays the resource information
    void display() const;
};

#endif 
