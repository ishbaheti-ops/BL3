cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(BL3)

find_package(Geant4 REQUIRED ui_all vis_all) 
include(${Geant4_USE_FILE})

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)

file(GLOB MACRO_FILES "*.mac")
file(COPY ${MACRO_FILES} DESTINATION ${CMAKE_BINARY_DIR}/)

add_executable(BL3 ${sources})
target_link_libraries(BL3 ${Geant4_LIBRARIES})