cmake_minimum_required(VERSION 3.12)
#ENGINE
set(ENGINE_PROJECT_NAME LamaEngineCore)

set(ENGINE_PUBLIC_INCLUDES 
	includes/LECore/Application.h
	includes/LECore/Event.h
	includes/LECore/Log.h
)

set(ENGINE_PRIVATE_INCLUDES 
	src/LECore/Window.h
	src/LECore/Rendering/OpenGL/ShaderProgram.h
	src/LECore/Rendering/OpenGL/VertexBuffer.h
	src/LECore/Rendering/OpenGL/VertexArray.h
	src/LECore/Rendering/OpenGL/IndexBuffer.h
)

set(ENGINE_PRIVATE_SOURCES 
	src/LECore/Application.cpp
	src/LECore/Window.cpp
	src/LECore/Rendering/OpenGL/ShaderProgram.cpp
	src/LECore/Rendering/OpenGL/VertexBuffer.cpp
	src/LECore/Rendering/OpenGL/VertexArray.cpp
	src/LECore/Rendering/OpenGL/IndexBuffer.cpp
)

set(ENGINE_ALL_SOURCES
	${ENGINE_PUBLIC_INCLUDES}
	${ENGINE_PRIVATE_SOURCES}
	${ENGINE_PRIVATE_INCLUDES}
)

add_library(${ENGINE_PROJECT_NAME} STATIC
	${ENGINE_ALL_SOURCES}
)
#CREATE in sln file struct as data 
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
	${ENGINE_ALL_SOURCES}
)





#set includes C++ public for using
target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC includes)
#set sourc C++ private
target_include_directories(${ENGINE_PROJECT_NAME} PRIVATE src)

target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC cxx_std_20)

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

add_subdirectory(../external/glm ${CMAKE_CURRENT_BINARY_DIR}/glm)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glm)

set(IMGUI_INCLUDES
	../external/imgui/imgui.h
	../external/imgui/backends/imgui_impl_glfw.h
	../external/imgui/backends/imgui_impl_opengl3.h	
)

set(IMGUI_SOURCES
	../external/imgui/imgui.cpp
	../external/imgui/backends/imgui_impl_glfw.cpp
	../external/imgui/backends/imgui_impl_opengl3.cpp	
	../external/imgui/imgui_draw.cpp
	../external/imgui/imgui_widgets.cpp
	../external/imgui/imgui_tables.cpp
	../external/imgui/imgui_demo.cpp	
)

add_library(ImGui STATIC
	${IMGUI_INCLUDES}
	${IMGUI_SOURCES}
)

#add for Engine or internal use ImGui
target_include_directories(ImGui PUBLIC ../external)
target_include_directories(ImGui PUBLIC ../external/imgui)
target_link_libraries(ImGui PRIVATE glad glfw)

target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE ImGui)