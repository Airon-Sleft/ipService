cmake_minimum_required(VERSION 3.8)

project(ipService)

# set(CMAKE_DEBUG_POSTFIX d)

# add_library(ipService_compiler_flags INTERFACE)

find_package(CURL REQUIRED)
add_executable(ipService source/main.cpp source/geoBase.cpp source/downloader.cpp source/unpacker.cpp source/console_logger.cpp source/utils.cpp)
# set_target_properties(ipService PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CURL_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/source/include/extern)
include_directories(${CMAKE_SOURCE_DIR}/source/include/)
target_link_libraries(ipService ${CURL_LIBRARIES})
target_link_libraries(ipService ${CMAKE_SOURCE_DIR}/source/lib/libzip.so)

configure_file(${CMAKE_SOURCE_DIR}/source/ipBase.csv ipBase.csv COPYONLY)