# SDL2
FetchContent_Declare(
  SDL2_
  URL https://github.com/libsdl-org/SDL/releases/download/release-2.28.4/SDL2-devel-2.28.4-VC.zip
)
FetchContent_Populate(SDL2_)
FetchContent_MakeAvailable(SDL2_)
# SDL2_image
FetchContent_Declare(
  SDL2_IMAGE_
  URL https://github.com/libsdl-org/SDL_image/releases/download/release-2.6.3/SDL2_image-devel-2.6.3-VC.zip
)
FetchContent_Populate(SDL2_IMAGE_)
FetchContent_MakeAvailable(SDL2_IMAGE_)
set(PSDL2_PATH ${sdl2__SOURCE_DIR})
set(PSDL2_IMAGE_PATH ${sdl2_image__SOURCE_DIR})
file(COPY cmake/sdl2-config.cmake DESTINATION ${PSDL2_PATH})
file(COPY "${PSDL2_IMAGE_PATH}/include/SDL_image.h" DESTINATION "${PSDL2_PATH}/include")
file(COPY "${PSDL2_IMAGE_PATH}/lib/x64/SDL2_image.dll" DESTINATION "${PSDL2_PATH}/lib/x64")
file(COPY "${PSDL2_IMAGE_PATH}/lib/x64/SDL2_image.lib" DESTINATION "${PSDL2_PATH}/lib/x64")
set(SDL2_DIR ${PSDL2_PATH})
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PSDL2_PATH}/lib/x64/SDL2.dll" $<TARGET_FILE_DIR:MyProject>)
#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PSDL2_PATH}/lib/x64/SDL2_image.dll" $<TARGET_FILE_DIR:MyProject>)
