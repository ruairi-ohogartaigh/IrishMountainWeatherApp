#include "Map_config.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

MountainLog::MountainLog() {}
MountainLog::MountainLog(const std::string &filename) {
    Mountain_List = parseMountainCSV(filename);
}
MountainLog::~MountainLog() {}

std::vector<MountainLog::MountainReport> MountainLog::get_mountain_list() const {
    return Mountain_List;
}

void MountainLog::set_mountain_list(std::vector<MountainReport> NewMountainList) {
    Mountain_List = std::move(NewMountainList);
}

std::vector<MountainLog::MountainReport> MountainLog::parseMountainCSV(const std::string& filename) {
    std::vector<MountainReport> mountainVec;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << "\n";
        return mountainVec;
    }

    std::string line;
    // Skip header
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        MountainReport mntr;
        std::string field;

        std::getline(ss, field, ','); mntr.MountainInfo.rank = std::stoi(field);
        std::getline(ss, mntr.MountainInfo.name, ',');
        std::getline(ss, mntr.MountainInfo.Irish_name, ',');
        std::getline(ss, mntr.MountainInfo.name_translation, ',');
        std::getline(ss, mntr.MountainInfo.range_area, ',');
        std::getline(ss, mntr.MountainInfo.Province, ',');
        std::getline(ss, mntr.MountainInfo.County, ',');
        std::getline(ss,  mntr.MountainInfo.height_m , ',');
        std::getline(ss, mntr.MountainInfo.Prominence , ','); 
        std::getline(ss, mntr.MountainInfo.rating, ','); 
        std::getline(ss, mntr.MountainInfo.Latitude, ',');
        std::getline(ss, mntr.MountainInfo.Longitude, ','); 
        std::getline(ss, mntr.MountainInfo.Importance, ',');

        mountainVec.push_back(mntr);
    }

    return mountainVec;
}


MountainLog::MountainReport MountainLog::set_mountain_instance_forecast(int index, WeatherForecast::ForecastData forecast) {
    if (index < 0 || index >= static_cast<int>(Mountain_List.size())) {
        throw std::out_of_range("Index out of range in set_mountain_instance_forecast");
    }
    Mountain_List[index].forecast = forecast;
    return Mountain_List[index];
}

