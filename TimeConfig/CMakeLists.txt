cmake_minimum_required(VERSION 3.10.0)
project( TimeConfig VERSION 0.1.0)
# include subfolder projects ep5

set(ProjectType STATIC) # options are STATIC, SHARED, MODULE
include_directories(lib)

set(SourceFiles
    #src/API_data.cpp
    src/time_formatter.cpp
)

#
add_library(${PROJECT_NAME} ${ProjectType} ${SourceFiles})