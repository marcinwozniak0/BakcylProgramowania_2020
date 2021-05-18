cmake_minimum_required(VERSION 3.14)

project(Bakcyl2020)

set(LIBRARY_OUTPUT_PATH build/)
set(BINARY_OUTPUT_PATH build/)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-g3 -pthread -fconcepts -Wall -pedantic")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")

# LIBS
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(SQLite3)
if (NOT SQLite3_FOUND)
    message(SEND_ERROR "sqlite3 package not found, please install it")
endif()
find_package(JsonCpp)
if (NOT JsonCpp_FOUND)
    message(SEND_ERROR "jsoncpp, or jsoncpp-dev package not found, please install it")
endif()
find_package(CURL)
if (NOT CURL_FOUND)
    message(SEND_ERROR "libcurl4-openssl-dev package not found, please install it")
endif()
find_package(Qt5 COMPONENTS Widgets Charts)
if (NOT Qt5_FOUND)
    message(SEND_ERROR "qt5 package not found, please install it")
endif()

# GTEST
include(External_GTest.cmake)
add_executable(bakcyl_2020_ut "test.cpp")
target_link_libraries(bakcyl_2020_ut ${GTEST_MAIN_LIBRARY}
                                     ${GTEST_LIBRARY}
                                     ${GMOCK_MAIN_LIBRARY}
                                     ${GMOCK_LIBRARY})


# LOGIC
include_directories(${PROJECT_SOURCE_DIR}/Logger)
file(GLOB LOGGER_LIB ${PROJECT_SOURCE_DIR}/Logger/*.cpp)

add_subdirectory(${PROJECT_SOURCE_DIR}/DeckBuilder)

# QT
add_subdirectory(${PROJECT_SOURCE_DIR}/QT)

set(PROJECT_SOURCES
    QT/Source/MainWindow.cpp
    QT/Include/MainWindow.h
    QT/Include/CardWindow.h
    QT/Include/CardsContainer.h
    QT/Include/DeckWindow.h
    QT/Source/CardWindow.cpp
    QT/Source/CardsContainer.cpp
    QT/Source/DeckWindow.cpp
    QT/Source/ErrorWindow.cpp
    )

add_executable(Deckbuilder ${PROJECT_SOURCES})
    
target_link_libraries(Deckbuilder PRIVATE Qt5::Widgets ${SQLite3_LIBRARIES} JsonCpp::JsonCpp CURL::libcurl)

# DATABASE
add_subdirectory(${PROJECT_SOURCE_DIR}/db/sqlite_helper)
add_subdirectory(${PROJECT_SOURCE_DIR}/db/db_builder)
add_subdirectory(${PROJECT_SOURCE_DIR}/db/card_api)

# VALGRIND
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

# MAIN
add_executable(Deckbuilder ${PROJECT_SOURCE_DIR}/main.cpp ${PROJECT_SOURCES})
    
target_link_libraries(Deckbuilder PRIVATE Qt5::Widgets 
                                          Qt5::Charts 
                                          ${SQLite3_LIBRARIES} 
                                          JsonCpp::JsonCpp
                                          DeckBuilderSources
                                          QT_LIBS
                                          db_builder
                                          card_api
                                          sqlite_helper
                                          ${LOGGER_LIB})
