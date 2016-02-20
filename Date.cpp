#include <sstream>
#include "Date.h"

using namespace std;

Date::Date(int d, int m, int y) 
{ 
    m_day = d; 
	m_month = m; 
	m_year = y; 
} 
	     
int Date::getDay() const     
{ 
    return m_day; 
} 
 
int Date::getMonth() const 
{ 
    return m_month; 
} 

int Date::getYear() const     
{ 
    return m_year; 
} 

string Date::to_string()
{
    stringstream s;
    s << getMonth() << "/" << getDay() << "/" << getYear() ;
    return s.str();
}
