#include <sstream>
#include "Activity.h"

using namespace std;

string Activity::getLoc() 
{
    return location;
}

void Activity::updateLoc (string newLoc)
{
    location.assign(newLoc);
}