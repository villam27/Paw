# module1 CMakeLists.txt

set(MODULE_NAME module1)

add_library(${MODULE_NAME} module1.cpp)

target_include_directories(${MODULE_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(BUILD_TESTS)
    add_executable(test_module1 test_module1.cpp)
    set_target_properties(test_module1 PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests
    )
    target_link_libraries(test_module1 gtest gtest_main module1)
    add_test(NAME test_module1 COMMAND test_module1)
endif()
