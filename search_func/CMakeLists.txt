file(GLOB SOURCE CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp)
add_executable(searchTest ${SOURCE})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Include ${CMAKE_CURRENT_SOURCE_DIR}/../DeckBuilder)
target_link_libraries(searchTest ${SQLite3_LIBRARIES})
