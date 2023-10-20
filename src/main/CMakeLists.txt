# main CMakeLists.txt

set(MAIN_NAME main)

set(DATA_SOURCE_DIR ${CMAKE_SOURCE_DIR}/res)
set(DATA_DEST_DIR ${CMAKE_BINARY_DIR}/)
set(DATA_DEST_DIR_2 ${CMAKE_BINARY_DIR}/bin/Debug)

add_executable(${MAIN_NAME} main.cpp)

target_link_libraries(${MAIN_NAME}
    PRIVATE
    module1
    lua_static
    ${SDL2_LIBRARIES}
)

set_target_properties(${MAIN_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

file(COPY ${DATA_SOURCE_DIR} DESTINATION ${DATA_DEST_DIR})
file(COPY ${DATA_SOURCE_DIR} DESTINATION ${DATA_DEST_DIR_2})