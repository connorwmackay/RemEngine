
cmake_minimum_required(VERSION 3.16)
project(RemEngine)

include(FetchContent)

# GLFW

FetchContent_Declare(glfw
                     GIT_REPOSITORY https://github.com/glfw/glfw.git
                     GIT_TAG 3.3.7)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_GetProperties(glfw)

if(NOT glfw_POPULATED)
    FetchContent_Populate(glfw)
    add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()

# GLAD
FetchContent_Declare(glad2
                     GIT_REPOSITORY https://github.com/connorwmackay/glad.git
                     GIT_TAG v_glad2)
          
FetchContent_GetProperties(glad2)

if (NOT glad2_POPULATED)
    FetchContent_Populate(glad2)
    add_subdirectory(${glad2_SOURCE_DIR}/cmake ${glad2_BINARY_DIR})
endif()

glad_add_library(glad_gl_core_41 SHARED API gl:core=4.1)

# GLM
FetchContent_Declare(glm
                    GIT_REPOSITORY https://github.com/g-truc/glm
                    GIT_TAG 0.9.9.8)

FetchContent_GetProperties(glm)

if(NOT glm_POPULATED)
    FetchContent_Populate(glm)
    add_subdirectory(${glm_SOURCE_DIR} ${glm_BINARY_DIR})
endif()

# FastNoise 2
FetchContent_Declare(fastnoise2
                    GIT_REPOSITORY https://github.com/Auburn/FastNoise2/
                    GIT_TAG v0.9.6-alpha)

set(FASTNOISE2_NOISETOOL OFF CACHE BOOL "Build Noise Tool" FORCE)

FetchContent_GetProperties(fastnoise2)

if(NOT fastnoise2_POPULATED)
    FetchContent_Populate(fastnoise2)
    add_subdirectory(${fastnoise2_SOURCE_DIR} ${fastnoise2_BINARY_DIR})
endif()

# Project Config
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADER_FILES "src/world_matrices.h" "src/shader.h" "src/textureAtlas.h" "src/transform.h" "src/spectator.h" "src/mesh.h" "src/block.h" "src/Chunk.h" "src/gameObject.h"  "src/world.h" "src/gameInstance.h")
set(SRC_FILES "src/main.cpp" "src/shader.cpp" "src/textureAtlas.cpp" "src/transform.cpp" "src/spectator.cpp" "src/mesh.cpp" "src/block.cpp" "src/Chunk.cpp" "src/gameObject.cpp"  "src/world.cpp" "src/gameInstance.cpp")
add_executable (${CMAKE_PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC opengl32 glad_gl_core_41 glfw FastNoise glm::glm)
#target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 17)
endif()