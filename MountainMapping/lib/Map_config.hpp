#ifndef __MAP_CONFIG__
#define __MAP_CONFIG__

#include<vector>
#include <string>
#include <WeatherForecast.hpp>


class MountainLog{
public:
    
    struct MountainData {
        int rank;
        std::string name;
        std::string Irish_name;
        std::string name_translation;
        std::string range_area;
        std::string Province;
        std::string County;
        std::string height_m;
        std::string Prominence;
        std::string rating;
        std::string Longitude;
        std::string Latitude;
        std::string Importance;
    };

        struct MountainReport{
        WeatherForecast::ForecastData forecast{}; // may need to update to vector
        MountainData MountainInfo{};

    };

    MountainLog();
    MountainLog(const std::string& filename);
    ~MountainLog();

    std::vector<MountainReport> parseMountainCSV(const std::string& filename);
    std::vector<MountainReport> get_mountain_list() const;
    MountainReport set_mountain_instance_forecast(int index, WeatherForecast::ForecastData forecast);
    void set_mountain_list(std::vector<MountainReport> NewMountainList);

private:
    std::vector<MountainReport> Mountain_List;
};
#endif
