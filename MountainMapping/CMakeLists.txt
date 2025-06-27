

cmake_minimum_required(VERSION 3.10.0)
project( MountainMapping VERSION 0.1.0)
# include subfolder projects ep5

set(ProjectType STATIC) # options are STATIC, SHARED, MODULE
include_directories(lib)

set(SourceFiles
   src/Map_update.cpp
   src/Map_config.cpp
)

add_library(${PROJECT_NAME} ${ProjectType} ${SourceFiles})

# third-party library curl
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})
target_link_libraries(MountainMapping PRIVATE ${CURL_LIBRARIES})

target_link_libraries(${PROJECT_NAME} PRIVATE  WeatherForecast)

