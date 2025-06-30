#include <iostream>
/* to be removed*/
#include <string>

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <iostream>
namespace fs = std::filesystem;

#include <vector>
/*stop removing */
#include <WeatherForecast.hpp>
#include <MountainMapping.hpp>
#include <TimeConfig.hpp>

using std::cout, std::endl;

bool ConfigWeatherForecast(){
    Clock clk;
    std::cout << "Current path is " << fs::current_path() << '\n'; // (1)
    MountainLog Irish_mountains("../RawData/MountainRangeList_long_lat.csv"); 
    MountainLog::MountainReport WeatherReport{};

    auto ListOf_Mnts =  Irish_mountains.get_mountain_list();
    for(size_t mnt = 0; mnt < ListOf_Mnts.size(); ++mnt){
        auto local = ListOf_Mnts.at(mnt);
        WeatherForecast dataExtract;
        std::string metdate=clk.getTime_sat_noon();//.get_time_now();//date.str().append("T"+time.str());
        std::string metdatend = clk.getTime_sat_noon();//clk.get_time_1hr();
        WeatherForecast::ForecastData WeatherReport=  dataExtract.getWeatherDataFromAPI(local.MountainInfo.Longitude, local.MountainInfo.Latitude , metdate, metdatend);
        local.forecast=WeatherReport;
        std::cout<<"Mountain store name, height: "+local.MountainInfo.name+" : "+ local.MountainInfo.height_m+" m , forecast temp:, "<<WeatherReport.temperature;
        std::cout<<"C, precipitation: "<<WeatherReport.precipitation<<" mm, report altitude:"<<WeatherReport.altitude<<"m"<<std::endl;
        Irish_mountains.set_mountain_instance_forecast(mnt, local.forecast);
    }

    WeatherForecast xml_extract= WeatherForecast();  
 return true;
};

int main(int, char**){
    if(ConfigWeatherForecast()){
        //run backend service
        std::cout<<"Environment configured";
    }
    return 0;
};
