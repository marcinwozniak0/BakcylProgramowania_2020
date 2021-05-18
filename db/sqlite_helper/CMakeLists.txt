if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.11.0")
    file(GLOB SOURCE_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp)
else()
    file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp)
endif()

add_library(sqlite_helper STATIC ${SOURCE_FILES})
target_include_directories(sqlite_helper PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include)
target_link_libraries(sqlite_helper ${SQLite3_LIBRARIES})
