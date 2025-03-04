project(WINAPI_demo2)

set(${INSTALL_DIR} ${CMAKE_INSTALL_PREFIX}/WINAPI/${PROJECT_NAME})


set(SRC
	"src/main.cpp"
)

add_executable(${PROJECT_NAME} WIN32 ${SRC})
target_include_directories(${PROJECT_NAME} PRIVATE "include")
target_link_libraries(${PROJECT_NAME} comctl32.lib)

install(TARGETS ${PROJECT_NAME} DESTINATION ${INSTALL_DIR}/bin/)
install(DIRECTORY "${PROJECT_SOURCE_DIR}/assets" DESTINATION "${INSTALL_DIR}")
