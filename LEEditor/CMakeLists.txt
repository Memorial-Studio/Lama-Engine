cmake_minimum_required(VERSION 3.12)
#EDITOR
set(EDITOR_PROJECT_NAME LamaEngineEditor)

add_executable(${EDITOR_PROJECT_NAME}
	src/main.cpp
)

set(CMAKE_CXX_STANDARD 20)
#linkovka
target_link_libraries(${EDITOR_PROJECT_NAME} LamaEngineCore)

set_target_properties(${EDITOR_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)