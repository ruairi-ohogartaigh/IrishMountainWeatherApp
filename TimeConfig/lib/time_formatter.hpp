#ifndef __TIME_FORMATTER__
#define __TIME_FORMATTER__
#include <string>
#include <iostream>
#include <sstream>
#include <chrono>


using std::chrono::time_point;

class Clock
{
    public:

Clock(){};
~Clock(){};

enum daysOfWeek{
Sun,//0
Mon,
Tue,
Wed,
Thu,
Fri,
Sat //6
};

struct timeInfo
{
    std::string date;//= m_date;
    std::string time;//=m_time;
    std::string hr;//=m_hr;
    std::string min;//=m_min;
    daysOfWeek dow; // day of week
    // unsigned long duration;
};




std::string get_time_now();
std::string get_time_1hr();
std::string getTime_sat_noon();
std::string get_Time_Sun_noon();


private:
    const static long hr_in_ns= 3600000000000;
    timeInfo timeStream_now();
    timeInfo StreamTimeInstance(std::tm tm, auto systime);
    timeInfo getDateOfRequest(auto t_to_date);
    timeInfo LoadTimeStruct(std::string date,std::string time,std::string hr, std::string min, daysOfWeek dow);

};

#endif