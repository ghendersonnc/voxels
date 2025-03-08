cmake_minimum_required(VERSION 3.20)
project(voxels)

set(CMAKE_CXX_STANDARD 17)

Include(FetchContent)

# glad
add_library(glad STATIC "vendor/glad.c")
target_include_directories(glad PRIVATE EXCLUDE_FROM_ALL "${CMAKE_CURRENT_SOURCE_DIR}/include")

#glfw
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

#glm
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
)
FetchContent_MakeAvailable(glfw)
FetchContent_MakeAvailable(glm)

add_executable(${CMAKE_PROJECT_NAME})


set(RENDERER_SOURCES
    "src/renderer/Shader.cpp"
    "src/renderer/VertexArray.cpp"
    "src/renderer/VertexBuffer.cpp"
    "src/renderer/IndexBuffer.cpp"
    "src/renderer/Camera.cpp"
    "src/renderer/Vertex.cpp"
)

set(VOXEL_SOURCES
    "src/voxels/Chunk.cpp"
    "src/voxels/MeshBuilder.cpp"
    "src/voxels/MeshData.cpp"
    "src/voxels/Game.cpp"
)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    "src/Main.cpp"
    "src/Utility.cpp"           
    ${RENDERER_SOURCES}
    ${VOXEL_SOURCES}
 "src/voxels/Block.cpp")

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/renderer")
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/voxels")

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE RESOURCE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC
    glad
    glfw
    glm::glm
)