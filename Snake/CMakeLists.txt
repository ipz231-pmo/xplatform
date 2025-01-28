project(Snake VERSION 0.1)

set(INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME})



set(SRC
	./src/main.cpp
	./src/Game.cpp
	./src/Renderer.cpp
)


add_executable(${PROJECT_NAME} ${SRC} )

target_include_directories(${PROJECT_NAME} PRIVATE "./include/")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_BINARY_DIR}/")



install(TARGETS ${PROJECT_NAME} DESTINATION ./Snake/bin/)
install(DIRECTORY "./assets/" DESTINATION "./Snake/assets/")
