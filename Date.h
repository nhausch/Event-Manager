#ifndef DATE_H 
#define DATE_H 

#include <string>

class Date
{ 
    private: 
        int m_day, m_month, m_year;

    public: 

       Date(int d, int m, int y) ;
	     
       int getDay() const ;
 
       int getMonth() const ; 

       int getYear() const ; 

       virtual std::string to_string() ;
}; 
#endif