file(GLOB SOURCE_FILES Source/*.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Include)
add_executable(sources ${SOURCE_FILES})
