if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.11.0")
    file(GLOB SOURCE_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp)
else()
    file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Include)
add_executable(db_builder ${SOURCE_FILES})
target_link_libraries(db_builder JsonCpp::JsonCpp ${SQLite3_LIBRARIES} CURL::libcurl)
