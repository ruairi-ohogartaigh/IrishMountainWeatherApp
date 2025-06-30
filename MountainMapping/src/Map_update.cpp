
#include<vector>
#include <string>
#include <WeatherForecast.hpp>
#include "Map_config.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

void set_mountain_forecast(MountainLog::MountainReport* MountainLogInstance, WeatherForecast::ForecastData updatedForecast){

    MountainLogInstance->forecast=updatedForecast;
};
