#ifndef __Forecast__
#define  __Forecast__
//MOVE TO WeatherForecast SUBFOLDER!!!


class WeatherForecast{

public:
WeatherForecast();
~WeatherForecast();



static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);


struct ForecastData{
    std::string from {};
    std::string to {};
    double temperature {};
    double windSpeed {};
    double humidity {};
    double pressure {};
    double cloudiness {};
    double dewpoint {};
    double longitude {};
    double latitude {};
    double altitude {};
    std::string windDirection {};
    std::string windDirectionName {};
    std::string windSpeedName {};
    std::string symbol {};
    double precipitation {};
    double precipitationProbability {};
};

ForecastData parseWeatherData(const std::string& xml);
ForecastData getWeatherDataFromAPI(std::string longitude, std::string latitude, std::string str_t_min, std::string str_t_max);

// new xml 
ForecastData parseForecastXML(const std::string& xml) ;



//std::vector<std::vector<ForecastData>> parseForecastXML(const std::string& xml) ;

private:
};

#endif