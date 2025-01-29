project(native_grap)
set(INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/)



#Executables
add_executable(${PROJECT_NAME} WIN32 "src/main.cpp" )



# Link library
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include/")



# Install
install(TARGETS ${PROJECT_NAME} DESTINATION "${INSTALL_DIR}/bin/")


