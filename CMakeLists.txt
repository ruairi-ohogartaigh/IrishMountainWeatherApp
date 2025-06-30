cmake_minimum_required(VERSION 3.10.0)

set(this MountainWeatherApp)
project(this VERSION 0.1.0 LANGUAGES C CXX)

add_executable(MountainWeatherApp main.cpp)

include(CTest)
include_directories(RawData)
enable_testing()

set (CMAKE_CXX_STANDARD 23)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)



# third-party library curl
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})
target_link_libraries(MountainWeatherApp PRIVATE ${CURL_LIBRARIES})



set (SubPrjt
 WeatherForecast
 MountainMapping
 TimeConfig
 )

foreach(Project IN LISTS SubPrjt)
    include_directories(${Project})
    if (NOT TARGET ${Project})
        message(STATUS "Adding subdirectory: ${Project}")
        add_subdirectory(${Project})
    else()
        message(STATUS "Target ${Project} already exists, skipping.")
    endif()
    target_link_libraries(MountainWeatherApp PRIVATE ${SubPrjt})
endforeach()
