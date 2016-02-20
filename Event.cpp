#include <sstream>
#include "Event.h"

using namespace std;

int Event::getID() const
{
    return eventID;
}

string Event::getDesc() const
{
    return description;
}

void Event::updateDesc (string newDesc)
{
    description.assign(newDesc);
}