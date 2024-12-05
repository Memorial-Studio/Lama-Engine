cmake_minimum_required(VERSION 3.12)

project(LamaEngine)
#name project for VS build_name
set(PROJECT_NAME LamaEngine)

#subdirectory CMake files
add_subdirectory(LECore)
add_subdirectory(LEEditor)

#set standart run in VS 2022 with start debug LamaEngineEditor
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT LamaEngineEditor)
#standart C++
set(CMAKE_CXX_STANDARD 20)