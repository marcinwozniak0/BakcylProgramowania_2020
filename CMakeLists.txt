cmake_minimum_required(VERSION 3.10)

project(Bakcyl2020)

set(LIBRARY_OUTPUT_PATH build/)
set(BINARY_OUTPUT_PATH build/)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-g3 -pthread -fconcepts -Wall -pedantic")

#Qt
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

include(External_GTest.cmake)

add_executable(bakcyl_2020_ut "test.cpp")

target_link_libraries(bakcyl_2020_ut ${GTEST_MAIN_LIBRARY}
                                     ${GTEST_LIBRARY}
                                     ${GMOCK_MAIN_LIBRARY}
                                     ${GMOCK_LIBRARY})

include_directories(${PROJECT_SOURCE_DIR}/Logger)
file(GLOB LOGGER_LIB ${PROJECT_SOURCE_DIR}/Logger/Logger.cpp)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ${LOGGER_LIB})

add_executable(Deckbuilder ${PROJECT_SOURCES})
    
target_link_libraries(Deckbuilder PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

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
