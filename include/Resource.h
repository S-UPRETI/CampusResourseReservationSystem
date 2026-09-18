#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>


class Resource {
private:
    std::string resourceID;   
    std::string name;         
    std::string type;         
    bool available;           

public:
   
    Resource();
    Resource(const std::string& resourceID,
              const std::string& name,
              const std::string& type,
              bool available);

    
    std::string getResourceID() const;
    std::string getName() const;
    std::string getType() const;
    bool isAvailable() const;

  
    void setResourceID(const std::string& id);
    void setName(const std::string& name);
    void setType(const std::string& type);
    void setAvailable(bool status);

    
    void display() const;
};

#endif 
