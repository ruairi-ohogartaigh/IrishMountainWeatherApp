

cmake_minimum_required(VERSION 3.10.0)
project( WeatherForecast VERSION 0.1.0)
# include subfolder projects ep5

set(ProjectType STATIC) # options are STATIC, SHARED, MODULE
include_directories(lib)

set(SourceFiles
    #src/API_data.cpp
    src/Forecast.cpp
)

#
add_library(${PROJECT_NAME} ${ProjectType} ${SourceFiles})




# third-party library curl
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})
target_link_libraries(WeatherForecast PRIVATE ${CURL_LIBRARIES})


add_subdirectory(pugixml ${CMAKE_BINARY_DIR}/pugixml)
# Link pugixml to your library
target_link_libraries(${PROJECT_NAME} PRIVATE pugixml)
target_link_libraries(${PROJECT_NAME} PRIVATE MountainMapping)
