# LuaC CMakeLists.txt

set(MODULE_NAME Config)
set(MODULE_NAME_TEST test_Config)

add_library(${MODULE_NAME} Config.cpp)

target_link_libraries(${MODULE_NAME}
    PRIVATE
    lua_static
    LuaC
)

target_include_directories(${MODULE_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(BUILD_TESTS)
    add_executable(${MODULE_NAME_TEST} test_Config.cpp)
    set_target_properties(${MODULE_NAME_TEST} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests
    )
    target_link_libraries(${MODULE_NAME_TEST} gtest gtest_main ${MODULE_NAME} lua_static LuaC)
    add_test(NAME ${MODULE_NAME_TEST} COMMAND ${MODULE_NAME_TEST})
endif()
