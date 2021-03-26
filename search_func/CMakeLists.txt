set(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/Source/search_func.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/main.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/utils.cpp)
    
add_executable(searchTest ${SOURCE} ${CMAKE_CURRENT_SOURCE_DIR}/../DeckBuilder/Card.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Include ${CMAKE_CURRENT_SOURCE_DIR}/../DeckBuilder)
target_link_libraries(searchTest ${SQLite3_LIBRARIES})
