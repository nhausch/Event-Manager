#ifndef EVENT_H
#define EVENT_H

#include <string>
#include "Date.h"

class Event : public Date
{
    private:
        int eventID;
        std::string description;
    
    public:
    
    // Constructor
    Event(int d, int m, int y, int ID, std::string desc) : Date(d,m,y)
    {
        eventID = ID;
        description.assign(desc);
    }

    int getID() const;
    
    std::string getDesc() const;
    
    void updateDesc (std::string newDesc) ;
};

#endif
