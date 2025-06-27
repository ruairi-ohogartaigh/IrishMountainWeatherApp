#include <iostream>
#include <string>
#include <curl/curl.h>
#include <bits/stdc++.h>
#include "Forecast.hpp"
#include <pugixml.hpp>

    WeatherForecast::WeatherForecast(){};

    size_t WeatherForecast::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp){
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
};


// std::string 
WeatherForecast::ForecastData WeatherForecast::getWeatherDataFromAPI(std::string longitude, std::string latitude, std::string datetimefrom, std::string datetimeto) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    std::string locale = "http://openaccess.pf.api.met.ie/metno-wdb2ts/locationforecast?lat=" + latitude + ";long=" + longitude+";from="+datetimefrom+";to="+datetimeto;
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL,locale.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Optional: set timeout and user agent
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 100L);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "MountainWeatherApp/1.0");

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);
    }
    return WeatherForecast::parseForecastXML(readBuffer);
};



WeatherForecast::~WeatherForecast(){};

/**/
 WeatherForecast::ForecastData WeatherForecast::parseForecastXML(const std::string& xml) {
    WeatherForecast::ForecastData data;
    pugi::xml_document doc;
    if (!doc.load_string(xml.c_str())) { 
        std::cerr << "Failed to parse XML\n";
        return data;
    }

    auto product = doc.child("weatherdata").child("product");
    auto timeElem = product.child("time");
    if (timeElem) {
        data.from = timeElem.attribute("from").as_string();
        data.to = timeElem.attribute("to").as_string();

        auto loc = timeElem.child("location");
        if (loc) {
            data.temperature = loc.child("temperature").attribute("value").as_double();
            data.humidity = loc.child("humidity").attribute("value").as_double();
            data.pressure = loc.child("pressure").attribute("value").as_double();
            data.cloudiness = loc.child("cloudiness").attribute("percent").as_double();
            data.dewpoint = loc.child("dewpointTemperature").attribute("value").as_double();

            // Try as child elements first
            if (loc.child("longitude"))
                data.longitude = loc.child("longitude").text().as_double();
            else if (loc.attribute("longitude"))
                data.longitude = loc.attribute("longitude").as_double();

            if (loc.child("latitude"))
                data.latitude = loc.child("latitude").text().as_double();
            else if (loc.attribute("latitude"))
                data.latitude = loc.attribute("latitude").as_double();

            if (loc.child("altitude"))
                data.altitude = loc.child("altitude").text().as_double();
            else if (loc.attribute("altitude"))
                data.altitude = loc.attribute("altitude").as_double();

            data.windSpeed = loc.child("windSpeed").attribute("mps").as_double();
            data.windSpeedName = loc.child("windSpeed").attribute("name").as_string();
            data.windDirection = loc.child("windDirection").attribute("deg").as_string();
            data.windDirectionName = loc.child("windDirection").attribute("name").as_string();
            data.symbol = loc.child("symbol").attribute("id").as_string();
            data.precipitation = loc.child("precipitation").attribute("value").as_double();
            data.precipitationProbability = loc.child("precipitation").attribute("probability").as_double();
        }
    }
    return data;
}
/**/


// verctorised TBD

/*

std::vector<WeatherForecast::ForecastData> parseForecastXML(const std::string& xml) {
    std::vector<WeatherForecast::ForecastData> forecasts;
    pugi::xml_document doc;
    if (!doc.load_string(xml.c_str())) {
        std::cerr << "Failed to parse XML\n";
        return forecasts;
    }

    auto product = doc.child("weatherdata").child("product");
    for (auto timeElem : product.children("time")) {
        WeatherForecast::ForecastData data;
        data.from = timeElem.attribute("from").as_string();
        data.to = timeElem.attribute("to").as_string();

        auto loc = timeElem.child("location");
        if (loc) {
            data.temperature = loc.child("temperature").attribute("value").as_double();
            data.humidity = loc.child("humidity").attribute("value").as_double();
            data.pressure = loc.child("pressure").attribute("value").as_double();
            data.cloudiness = loc.child("cloudiness").attribute("percent").as_double();
            data.dewpoint = loc.child("dewpointTemperature").attribute("value").as_double();
            data.longitude = loc.child("longitude").text().as_double();
            data.latitude = loc.child("latitude").text().as_double();
            data.altitude = loc.child("altitude").text().as_double();
            data.windSpeed = loc.child("windSpeed").attribute("mps").as_double();
            data.windSpeedName = loc.child("windSpeed").attribute("name").as_string();
            data.windDirection = loc.child("windDirection").attribute("deg").as_string();
            data.windDirectionName = loc.child("windDirection").attribute("name").as_string();
            data.symbol = loc.child("symbol").attribute("id").as_string();
            data.precipitation = loc.child("precipitation").attribute("value").as_double();
            data.precipitationProbability = loc.child("precipitation").attribute("probability").as_double();
        }
        forecasts.push_back(data);
    }
    return forecasts;
}

*/