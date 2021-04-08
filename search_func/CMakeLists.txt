set(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/Source/search_func.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/main.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/utils.cpp)
    
add_executable(searchTest ${SOURCE} ${PROJECT_SOURCE_DIR}/DeckBuilder/Source/Card.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Include ${PROJECT_SOURCE_DIR}/DeckBuilder/Include)
target_link_libraries(searchTest ${SQLite3_LIBRARIES})
