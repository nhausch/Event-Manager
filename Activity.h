#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <string>
#include "Event.h"

class Activity : public Event
{
    private:
    std::string location;
    
    public:
        Activity(int d, int m, int y, int ID, std::string desc, std::string loc) : Event(d,m,y,ID,desc) {
            location.assign(loc);
        }
        std::string getLoc() ;
    
        void updateLoc (std::string newLoc) ;
};

#endif
