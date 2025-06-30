# Mountain weather App

## Introduction
This Mountain weather repo is very much a work in progress. I'm not sure what the end goal will be but it may lead to some changes in the code present in the repo. I understand professional projects are almost unanimously declarative in nature. I'm approaching this imperatively just out of inquisitiveness. Please overlook some optimizations I have yet to get around to, see this as proof that I am competent with cmake, OOP principles and RAII concepts. I'm following the KISS principle so don't expect overly elaborate displays of code where it is not necessary.

In this markdown I will outline the current code base, potential future development as well as changes I am considering to make in the future.

## Why build a mountain weather app
TL;DR I like hiking and camping in the mountains, preferably somewhere where the weather is good.

I thought it would be interesting to create some kind of application that can retrieve accurate weather forecasts for all the major mountains in Ireland, then if I have the urge to spend my weekend outdoors, I can run this app and quickly get an idea of where the weather will be best. 

## Getting into the code

### Logging the mountains
To load the list of mountains,attributes and coordinates, I have created a CSV file, much of the data obtained from [this Wiki page](https://en.wikipedia.org/wiki/Lists_of_mountains_in_Ireland). To get the coordinated google maps was used. 

The CSV data is read into the In the app on initialization. this data only needs to be loaded once.

#### future optimizations to consider
At present the class is a run time polymorphism but I think it could be optimize as a compile time polymorphism template. I am in two minds about this though, as it is loading external data, the use of exception handling would be useful. In a template, and error reading the CSV could cause headaches. 

Another optimization I am more certain about is the use of pointers when accessing the mountain data. To simplify memory management I will use smart pointer for the mountain data. As the data is loaded in once and not changes, it should be made a static too.


### Getting the weather Forecast
 Met Eireann has an open API where weather forecast for a specific timeframe and coordinates can be requested. This is the source of the weather data. Please read the *API_Notes.odt* file in the *RawData* folder.
 The API data is received in xml format. the *WeatherForecast* module interfaces with the API, sending the request, receiving the response and extracts the weather information in XML format and places it in a *ForecastData* structure. This *ForecastData* structure is used in the *MountainMapping* module, which stores this structure with the matching *MountainData* structure in the *MountainReport* structure. 

#### Further optimizations
There are multiple data points in the XML file, the WeatherForecast module only skims the top layer at the moment.  There could be potential for a vector of *ForeCastData* on each API call but further analysis is required before proceeding.  


### TimeConfig
This module was created for time-framing the forecast data. The time needs to be formatted for use with the API. There are some methods created to calculate what date next Saturday will be too.

### MountainMapping
MountainMapping has a *MountainReport* structure that hold both *mountainData* and *ForeCastData*. The weather data can be updated by API call.

### What next
Here is where I'm kind of at a crossroads of what to do. I don't need to harvest fields of data to figure out where the weather will be good.  I have no experience with SQL but this could be a good learning opertunity to learn. Alternatively, instead of caching weather data (which is occurring on init), it could just be set to retrieve on request, making a more agile system.

I considered making a basic CLI interface but Irish mountain's don't have names that roll off the tongue of dyslexics such as myself. I think it could be a good home lab project to create a restful API interface for this and run it in the backend and have a frontend in html or python. 

## Conclusion 
I could go into further detail on this apps structure but in its current state of development this may be a fools errand. Keep an eye on development, if you have an opinion to share I am all ears.  