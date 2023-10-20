# LuaC CMakeLists.txt

set(MODULE_NAME WinShape)
set(MODULE_NAME_TEST test_WinShape)

add_library(${MODULE_NAME} WinShape.cpp Mwindow.cpp App.cpp)

target_link_libraries(${MODULE_NAME}
    PRIVATE
    lua_static
    ${SDL2_LIBRARIES}
    LuaC
    Config
)

target_include_directories(${MODULE_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(BUILD_TESTS)
    add_executable(${MODULE_NAME_TEST} test_WinShape.cpp)
    set_target_properties(${MODULE_NAME_TEST} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests
    )
    target_link_libraries(${MODULE_NAME_TEST} gtest gtest_main ${MODULE_NAME} lua_static LuaC Config)
    add_test(NAME ${MODULE_NAME_TEST} COMMAND ${MODULE_NAME_TEST})
endif()
