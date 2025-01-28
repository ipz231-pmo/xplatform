project(WINAPI_demo2)


# Useful Variables
set(INSTALL_DIRECTORY ${CMAKE_INSTALL_PREFIX}/WINAPI/${PROJECT_NAME})
set(SRC
	"src/main.cpp"
	"src/game.cpp"
	"src/renderer.cpp" 
	"src/input.cpp")


# Executable
add_executable(${PROJECT_NAME} ${SRC})
target_include_directories(${PROJECT_NAME} PRIVATE "./include")
target_link_libraries(${PROJECT_NAME} Kernel32.lib)


# Instalation
install(TARGETS ${PROJECT_NAME} DESTINATION ${INSTALL_DIRECTORY}/bin/)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/assets/ DESTINATION ${INSTALL_DIRECTORY}/assets/)
