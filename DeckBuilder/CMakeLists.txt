file(GLOB SOURCE_FILES Source/*.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Include)
include_directories(${PROJECT_SOURCE_DIR}/db/card_api)
add_executable(sources ${SOURCE_FILES})
