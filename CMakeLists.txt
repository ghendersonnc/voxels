cmake_minimum_required(VERSION 3.20)
project(voxels)

set(CMAKE_CXX_STANDARD 17)

Include(FetchContent)

add_library(glad STATIC "vendor/glad.c")
target_include_directories(glad PRIVATE EXCLUDE_FROM_ALL "${CMAKE_CURRENT_SOURCE_DIR}/include")

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
)
FetchContent_MakeAvailable(glm)


FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.15.1 
)
FetchContent_MakeAvailable(spdlog)


FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.91.9
)

FetchContent_Populate(imgui)
add_library(imgui)
add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)
target_include_directories(imgui PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)
target_sources(imgui PUBLIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_link_libraries(imgui PRIVATE glfw)

add_executable(${CMAKE_PROJECT_NAME})

set(RENDERER_SOURCES
    "src/renderer/Shader.cpp"
    "src/renderer/VertexArray.cpp"
    "src/renderer/VertexBuffer.cpp"
    "src/renderer/IndexBuffer.cpp"
    "src/renderer/Vertex.cpp"
    "src/renderer/Texture.cpp"
)

set(VOXEL_SOURCES
    "src/voxels/Chunk.cpp"
    "src/voxels/MeshBuilder.cpp"
    "src/voxels/MeshData.cpp"
    "src/voxels/Game.cpp"
    "src/voxels/Block.cpp"
    "src/voxels/World.cpp"
    "src/voxels/Crosshair.cpp"
    "src/voxels/Camera.cpp"
  "src/voxels/Sun.cpp")

target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    "src/Main.cpp"
    "src/Utility.cpp"           
    ${RENDERER_SOURCES}
    ${VOXEL_SOURCES}
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/renderer")
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/voxels")

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE RESOURCE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE LOG_PATH="${CMAKE_CURRENT_SOURCE_DIR}/log/")

# Hot reload support for Visual Studio
if (MSVC AND WIN32 AND NOT MSVC_VERSION VERSION_LESS 142)
  target_link_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:/INCREMENTAL>)  
  target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:/ZI>)
  target_link_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:RelWithDebInfo>:/INCREMENTAL>)  
  target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:RelWithDebInfo>:/ZI>)
endif()

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC
    glad
    glfw
    glm::glm
    spdlog::spdlog
    imgui
)