# module2 CMakeLists.txt

set(MODULE_NAME module2)

add_library(${MODULE_NAME} module2.cpp)

target_include_directories(${MODULE_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)