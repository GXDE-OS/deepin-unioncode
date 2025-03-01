cmake_minimum_required(VERSION 3.0.2)

project(buildercore)

FILE(GLOB SRC_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.json"
)

add_library(${PROJECT_NAME}
    SHARED
    ${SRC_FILES}
    builder.qrc
)

target_link_libraries(${PROJECT_NAME}
    duc-framework
    duc-base
    duc-services
    duc-common
    ${QtUseModules}
    ${PkgUserModules}
)

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${PLUGIN_INSTALL_PATH})

