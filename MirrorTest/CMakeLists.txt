project("MirrorTest")

set(${INSTALL_DIR} ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME})

add_subdirectory("src")

install(TARGETS ${PROJECT_NAME} DESTINATION ${INSTALL_DIR}/bin/)
install(DIRECTORY "${PROJECT_SOURCE_DIR}/assets/" DESTINATION "${INSTALL_DIR}/assets/")
