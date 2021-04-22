if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.11.0")
    file(GLOB SOURCE_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp)
else()
    file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp)
endif()

add_library(card_api STATIC ${SOURCE_FILES})
target_include_directories(card_api PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include)
target_link_libraries(card_api ${SQLite3_LIBRARIES} sqlite_helper)

add_executable(card_api_example card_api_example.cpp)
target_link_libraries(card_api_example card_api)
