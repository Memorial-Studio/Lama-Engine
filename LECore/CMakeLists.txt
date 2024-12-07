cmake_minimum_required(VERSION 3.12)
#ENGINE
set(ENGINE_PROJECT_NAME LamaEngineCore)

set(ENGINE_PUBLIC_INCLUDES 
	includes/LECore/Application.h
	includes/LECore/Event.h
	includes/LECore/Log.h
)

set(ENGINE_PRIVATE_INCLUDES 
	includes/LECore/Window.h
)

set(ENGINE_PRIVATE_SOURCES 
	src/LECore/Application.cpp
	src/LECore/Window.cpp
)

add_library(${ENGINE_PROJECT_NAME} STATIC
	${ENGINE_PUBLIC_INCLUDES}
	${ENGINE_PRIVATE_SOURCES}
	${ENGINE_PRIVATE_INCLUDES}
)

#set includes C++ public for using
target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC includes)
#set sourc C++ private
target_include_directories(${ENGINE_PROJECT_NAME} PRIVATE src)

#standart C++
set(CMAKE_CXX_STANDARD 20)

#add glfw submodule git
add_subdirectory(../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glfw)

#add spdlog submodule git
add_subdirectory(../external/spdlog ${CMAKE_CURRENT_BINARY_DIR}/spdlog)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE spdlog)

#add glad ^_^
add_subdirectory(../external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glad)