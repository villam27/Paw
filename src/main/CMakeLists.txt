# main CMakeLists.txt

set(MAIN_NAME main)

add_executable(${MAIN_NAME} main.cpp)

target_link_libraries(${MAIN_NAME}
    PRIVATE
    module1
    module2
    lua_static
    ${SDL2_LIBRARIES}
)

set_target_properties(${MAIN_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)