add_library(glh STATIC "src/Shader.cpp")
target_include_directories(glh PUBLIC "include")
target_link_libraries(glh glm)
target_link_libraries(glh glad)