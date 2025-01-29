project(BlockOutlining)

set(INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/)
set(SRC
"src/main.cpp"
)
set(SRC_LIB 
"toolkit/Shader.cpp"
 "toolkit/Texture2D.cpp")

add_executable(${PROJECT_NAME} ${SRC} ${SRC_LIB})

target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/toolkit")
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} glm)
target_link_libraries(${PROJECT_NAME} stbi)

install(DIRECTORY "${PROJECT_SOURCE_DIR}/resources/" DESTINATION "${INSTALL_DIR}")

install(TARGETS ${PROJECT_NAME} DESTINATION "${INSTALL_DIR}/bin/")
install(DIRECTORY "${CMAKE_INSTALL_PREFIX}/bin/" DESTINATION "${INSTALL_DIR}/bin/")
