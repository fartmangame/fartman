# deps.cmake - build vendored dependencies from external/

# SDL3
add_subdirectory(${CMAKE_SOURCE_DIR}/external/SDL)

# SDL3_image
add_subdirectory(${CMAKE_SOURCE_DIR}/external/SDL_image)

# SDL3_mixer
add_subdirectory(${CMAKE_SOURCE_DIR}/external/SDL_mixer)

# glm (header-only, no build system needed, but adding for find_package support)
add_subdirectory(${CMAKE_SOURCE_DIR}/external/glm)
