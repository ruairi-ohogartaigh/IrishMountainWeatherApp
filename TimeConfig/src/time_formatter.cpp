#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <ctime>  
#include "time_formatter.hpp"
#include <string>
#include <chrono>

using std::chrono::time_point;

Clock::timeInfo  Clock::StreamTimeInstance(std::tm tm, auto systime){

        std::ostringstream date, time,hr, min;
        date << std::put_time(&tm, "%Y-%m-%d");
        time << std::put_time(&tm, "%H:%M");//:%S");
        hr << std::put_time(&tm, "%H");
        min << std::put_time(&tm, "%M");

        return LoadTimeStruct(date.str(),time.str(),hr.str(),min.str(),daysOfWeek(int(tm.tm_wday)));
 }

Clock::timeInfo Clock::timeStream_now(){

        time_t timestamp;
        time(&timestamp);
        auto now = std::chrono::system_clock::now();
        std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
        std::tm tm = *std::localtime(&now_time_t);
        return StreamTimeInstance(tm,now);

}

Clock::timeInfo Clock::getDateOfRequest(auto t_to_date){
        auto now = std::chrono::system_clock::now();
        Clock::timeInfo timeToGo;
        // Assume t_to_date is in nanoseconds, convert to std::chrono::nanoseconds
        auto offset = std::chrono::nanoseconds(t_to_date);
        auto future_time = now + offset;
        std::time_t sat_time_t = std::chrono::system_clock::to_time_t(future_time);
        std::tm tm = *std::localtime(&sat_time_t);
        return StreamTimeInstance(tm, future_time);
}

std::string Clock::get_time_now(){
        Clock::timeInfo T_now = timeStream_now();
        auto now = std::chrono::system_clock::now();
        std::string metdate=T_now.date.append("T"+T_now.time);

    return metdate;
}

std::string Clock::get_time_1hr(){
        Clock::timeInfo T_now = timeStream_now();
        std::string metdateplusOne = T_now.date.append("T" + std::to_string(std::stoi(T_now.hr) + 1) + ":" + T_now.min);
        return metdateplusOne;
}

std::string Clock::getTime_sat_noon(){
        std::string Sat_noon{};
        Clock::timeInfo T_now = timeStream_now();
        //exception for month turnover required
        if (T_now.dow != daysOfWeek::Sat){
                int DaysTilSat = int(daysOfWeek::Sat) - T_now.dow;
                T_now=getDateOfRequest(24*DaysTilSat*hr_in_ns);
                Sat_noon = T_now.date.append("T" + std::to_string(12) + ":" + "00");
        }
        //before noon on saturday
        else if(std::stoi(T_now.hr)<12){
                Sat_noon = T_now.date.append("T" + std::to_string(12) + ":" + T_now.min);
        }
        // afternoon Saturday, get noon next Saturday
        else{ 
                T_now=getDateOfRequest(24*7*hr_in_ns);
                Sat_noon = T_now.date.append("T" + std::to_string(12) + ":" + "00");
        }
        return Sat_noon;
}

std::string Clock::get_Time_Sun_noon(){}

Clock::timeInfo Clock::LoadTimeStruct(std::string date,std::string time,std::string hr, std::string min, daysOfWeek dow){
        timeInfo timeNow{};
        timeNow.date = date;
        timeNow.time = time;
        timeNow.hr = hr;
        timeNow.min = min;
        timeNow.dow = dow;
        return timeNow;
}
