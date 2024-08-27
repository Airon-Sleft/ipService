cmake_minimum_required(VERSION 3.8)

project(ipService)

add_executable(ipService source/main.cpp source/geoBase.cpp source/downloader.cpp source/unpacker.cpp source/console_logger.cpp source/utils.cpp source/geo_db_checker.cpp source/configuration.cpp)

set(CMAKE_CXX_STANDARD 17)
set_target_properties(${TARGET} PROPERTIES
	    CXX_STANDARD 17
	        CXX_STANDARD_REQUIRED YES
		    CXX_EXTENSIONS NO
	    )

find_package(CURL REQUIRED)
find_package(libzip REQUIRED)                                            
target_link_libraries(ipService PRIVATE libzip::zip) 
include_directories(${CMAKE_SOURCE_DIR}/source/include/extern)
include_directories(${CMAKE_SOURCE_DIR}/source/include/)
target_link_libraries(ipService PRIVATE ${CURL_LIBRARIES})

#configure_file(${CMAKE_SOURCE_DIR}/source/ipBase.csv ipBase.csv COPYONLY)
