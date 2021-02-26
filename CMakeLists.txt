cmake_minimum_required(VERSION 3.10)

project(Bakcyl2020)

set(LIBRARY_OUTPUT_PATH build/)
set(BINARY_OUTPUT_PATH build/)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-g3 -pthread -fconcepts -Wall -pedantic")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")

include (ExternalProject)

#Qt
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(SQLite3)
if (NOT SQLite3_FOUND)
    ExternalProject_Add(
        SQLite3
        GIT_REPOSITORY https://github.com/azadkuh/sqlite-amalgamation.git
        )
endif()
find_package(JsonCpp)
if (NOT JsonCpp_FOUND)
    ExternalProject_Add(
        JsonCpp
        GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git
        )
endif()
find_package(Qt5 COMPONENTS Widgets)
if (NOT Qt5_FOUND)
    ExternalProject_Add(
        Qt5
        GIT_REPOSITORY https://github.com/qt/qt5.git 
        GIT_TAG origin/release/5.15.2
        )
endif()

include(External_GTest.cmake)

add_executable(bakcyl_2020_ut "test.cpp")
target_link_libraries(bakcyl_2020_ut ${GTEST_MAIN_LIBRARY}
                                     ${GTEST_LIBRARY}
                                     ${GMOCK_MAIN_LIBRARY}
                                     ${GMOCK_LIBRARY})


#LOGIC
include_directories(${PROJECT_SOURCE_DIR}/Logger)
file(GLOB LOGGER_LIB ${PROJECT_SOURCE_DIR}/Logger/Logger.cpp)


set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ${LOGGER_LIB})

add_executable(Deckbuilder ${PROJECT_SOURCES})
    
target_link_libraries(Deckbuilder PRIVATE Qt5::Widgets ${SQLite3_LIBRARIES} JsonCpp::JsonCpp)


# Valgrind
find_program(VALGRIND "valgrind")
if(VALGRIND)
target_link_libraries(bakcyl_2020_ut LINK_PUBLIC)
add_custom_target(valgrind COMMAND "${VALGRIND}" --tool=memcheck
                                                 --leak-check=yes
                                                 --show-reachable=yes
                                                 --num-callers=20
                                                 --track-fds=no
                                                 --track-origins=yes
                                                 --error-exitcode=1
                                                 $<TARGET_FILE:bakcyl_2020_ut>)
endif()
