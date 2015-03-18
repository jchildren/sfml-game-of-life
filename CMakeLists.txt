cmake_minimum_required(VERSION 2.6)
project(game_of_life)

###########
## CMAKE ##
###########
# Use our modified FindSDL2* modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${game_of_life_SOURCE_DIR}/cmake")
# Set an output directory for our binaries
set(BIN_DIR ${game_of_life_SOURCE_DIR}/bin)

###########
## FLAGS ##
###########
# Bump up warning levels appropriately for clang, gcc & msvc
# Also set debug/optimization flags depending on the build type. IDE users choose this when
# selecting the build mode in their IDE
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
endif()

#############
## INCLUDE ##
#############

## EXTERNAL ##

# Look up SFML and add the include directory to our include path
find_package(SFML COMPONENTS graphics window system REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

find_package(Eigen3 REQUIRED)
include_directories(EIGEN3_INCLUDE_DIR)


## INTERNAL ##

#Recursively add files from source folder to
#list to be compiled, removing duplicates
file(GLOB_RECURSE game_of_life_SOURCES "src/*.cpp")
file(GLOB_RECURSE game_of_life_HEADERS "include/*.hpp")

set (game_of_life_INCLUDE_DIRS "")
foreach (_headerFile ${game_of_life_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND game_of_life_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES game_of_life_INCLUDE_DIRS)

include_directories(${game_of_life_INCLUDE_DIRS})

#############
## COMPILE ##
#############
#Sets executable file extension to .exe
set(CMAKE_EXECUTABLE_SUFFIX ".exe")


add_executable(game_of_life ${game_of_life_SOURCES})

#Link libraries
target_link_libraries(game_of_life ${SFML_LIBRARIES})

#############
## INSTALL ##
#############
install(TARGETS game_of_life RUNTIME DESTINATION ${BIN_DIR})
