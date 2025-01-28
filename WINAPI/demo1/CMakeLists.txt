project(WINAPI_demo1)


# Useful Variables
set(INSTALL_DIRECTORY ${CMAKE_INSTALL_PREFIX}/WINAPI/${PROJECT_NAME})
set(SRC
	"src/main.cpp"
	"src/Time.cpp" 
	"src/Window.cpp" 
	"src/App.cpp")

#set(SRC_GLAD "glad/src/glad_wgl.c")



# Executable
add_executable(${PROJECT_NAME} WIN32 ${SRC})
target_include_directories(${PROJECT_NAME} PRIVATE "include")
target_link_libraries(${PROJECT_NAME} Opengl32.lib)

#add_executable(${PROJECT_NAME} WIN32 ${SRC} ${SRC_GLAD})
#target_include_directories(${PROJECT_NAME} PRIVATE "glad/include")

target_link_libraries(${PROJECT_NAME} glh)

# Instalation
install(TARGETS ${PROJECT_NAME} DESTINATION ${INSTALL_DIRECTORY}/bin/)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/resources/ DESTINATION ${INSTALL_DIRECTORY})
