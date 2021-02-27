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
    
#Search for dependencies
find_package(SQLite3)
if (NOT SQLite3_FOUND)
    set(SQLITE3_ROOT "${CMAKE_BINARY_DIR}/sqlite3")
    ExternalProject_Add(
        SQLite3
        GIT_REPOSITORY https://github.com/azadkuh/sqlite-amalgamation.git
        
        PREFIX ${SQLITE3_ROOT}
        INSTALL_COMMAND make
        )
    ExternalProject_Get_Property(SQLite3 binary_dir)
    set(SQLITE3_LIBRARIES "${binary_dir}/libsqlite3.a")
    add_dependencies(Deckbuilder SQLite3)
endif()

find_package(JsonCpp)
if (NOT JsonCpp_FOUND)
    set(JSONCPP_ROOT "${CMAKE_BINARY_DIR}/jsoncpp")
    ExternalProject_Add(
        JsonCpp-git
        GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git

        PREFIX ${JSONCPP_ROOT}
        CMAKE_ARGS -DBUILD_STATIC_LIBS=ON -DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=debug -DARCHIVE_INSTALL_DIR=. -G "Unix Makefiles" -DCMAKE_INSTALL_INCLUDEDIR=include/jsoncpp
        INSTALL_COMMAND make
        )
    ExternalProject_Get_Property(JsonCpp-git binary_dir)
    set(JSONCPP_LIBRARIES "${binary_dir}/lib/libjsoncpp.a")
    #add_library(jsoncpp STATIC IMPORTED)
    #set_property(TARGET jsoncpp PROPERTY IMPORTED_LOCATION ${JSONCPP_LIBRARIES})
    add_dependencies(Deckbuilder JsonCpp-git)
else()
    set(JSONCPP_LIBRARIES "JsonCpp::JsonCpp")
endif()

find_package(Qt5 COMPONENTS Widgets)
if (NOT Qt5_FOUND)
    ExternalProject_Add(
        Qt5
        GIT_REPOSITORY https://github.com/qt/qt5.git 
        GIT_TAG origin/release/5.15.2
        )
endif()

target_link_libraries(Deckbuilder PRIVATE Qt5::Widgets ${SQLite3_LIBRARIES} ${JSONCPP_LIBRARIES})


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
