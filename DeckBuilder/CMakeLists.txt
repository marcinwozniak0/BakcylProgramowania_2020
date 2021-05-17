if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.11.0")
    file(GLOB SOURCE_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp)
else()
    file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Include)
include_directories(${PROJECT_SOURCE_DIR}/cpp-base64)

add_executable(DeckBuilderSources ${SOURCE_FILES})
target_link_libraries (DeckBuilderSources PUBLIC card_api QT_LIBS)