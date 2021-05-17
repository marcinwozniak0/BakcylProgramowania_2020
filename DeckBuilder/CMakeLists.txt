if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.11.0")
    file(GLOB SOURCE_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp)
else()
    file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Include)

add_executable(DeckBuilderSources ${SOURCE_FILES})
target_link_libraries (DeckBuilderSources PUBLIC card_api QT_LIBS)

set(BASE64_SOURCES ${PROJECT_SOURCE_DIR}/cpp-base64/base64.cpp)
add_library(Base64 ${BASE64_SOURCES})
target_include_directories(Base64 PUBLIC ${PROJECT_SOURCE_DIR}/cpp-base64)
target_link_libraries (DeckBuilderSources PUBLIC Base64)