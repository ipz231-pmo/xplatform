project(demo1)

set(INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/)

add_executable(${PROJECT_NAME} "src/main.cpp" "src/Engine/Block.cpp" "src/Engine/Chunk.cpp" "src/Engine/Camera.cpp" "src/Engine/Engine.cpp" "src/Engine/World.cpp")

target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include/")
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} glm)
target_link_libraries(${PROJECT_NAME} stbi)
target_link_libraries(${PROJECT_NAME} glh)

install(DIRECTORY "${PROJECT_SOURCE_DIR}/assets/" DESTINATION "${INSTALL_DIR}/assets/")

install(TARGETS ${PROJECT_NAME} DESTINATION "${INSTALL_DIR}/bin/")
install(DIRECTORY "${CMAKE_INSTALL_PREFIX}/bin/" DESTINATION "${INSTALL_DIR}/bin/")
