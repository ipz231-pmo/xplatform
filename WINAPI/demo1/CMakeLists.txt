project(WINAPI_demo1)


# Useful Variables
set(INSTALL_DIRECTORY ${CMAKE_INSTALL_PREFIX}/WINAPI/${PROJECT_NAME})
set(SRC
	"src/main.cpp"
	"src/Time.cpp" 
)
set(TOOLKIT_SRC
	"toolkit/Shader.cpp"
	"toolkit/Camera.cpp"
	"toolkit/Transform.cpp" 
	"toolkit/Behavior.cpp"
)


# Executable
add_executable(${PROJECT_NAME} WIN32 ${SRC} ${TOOLKIT_SRC})

target_include_directories(${PROJECT_NAME} PRIVATE "include")
target_include_directories(${PROJECT_NAME} PRIVATE "toolkit")

target_link_libraries(${PROJECT_NAME} Opengl32.lib)
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} glm)

#add_executable(${PROJECT_NAME} WIN32 ${SRC} ${SRC_GLAD})
#target_include_directories(${PROJECT_NAME} PRIVATE "glad/include")

#target_link_libraries(${PROJECT_NAME} glh)

# Instalation
install(TARGETS ${PROJECT_NAME} DESTINATION ${INSTALL_DIRECTORY}/bin/)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/resources/ DESTINATION ${INSTALL_DIRECTORY})
