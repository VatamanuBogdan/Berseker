cmake_minimum_required(VERSION 3.1)

# Set Berseker parameters
set(BERSEKER_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(BERSEKER_SOURCE_DIR ${BERSEKER_ROOT_DIR}/src/)
set(BERSEKER_DEPENDENCIES_DIR ${BERSEKER_ROOT_DIR}/deps/)
set(BERSEKER_BINARY_NAME Engine)

set(
    BERSEKER_SOURCES
    ${BERSEKER_SOURCE_DIR}/Rendering/GraphicsAPI/VertexBuffer.hpp
    ${BERSEKER_SOURCE_DIR}/Rendering/GraphicsAPI/VertexArray.hpp
    ${BERSEKER_SOURCE_DIR}/Rendering/GraphicsAPI/IndexBuffer.hpp
    ${BERSEKER_SOURCE_DIR}/Rendering/GraphicsAPI/ShaderProgram.cpp
    ${BERSEKER_SOURCE_DIR}/Rendering/GraphicsAPI/ShaderProgram.h
    ${BERSEKER_SOURCE_DIR}/Rendering/GraphicsAPI/Texture2D.hpp
    ${BERSEKER_SOURCE_DIR}/Rendering/GraphicsAPI/OpenGL.h
    ${BERSEKER_SOURCE_DIR}/Rendering/GraphicsAPI/OpenGL.cpp
    ${BERSEKER_SOURCE_DIR}/Rendering/Model.cpp
    ${BERSEKER_SOURCE_DIR}/Rendering/Renderer.cpp
    ${BERSEKER_SOURCE_DIR}/Rendering/Renderer.h
    ${BERSEKER_SOURCE_DIR}/Rendering/Mesh.h
    ${BERSEKER_SOURCE_DIR}/Window/Window.h
    ${BERSEKER_SOURCE_DIR}/Window/GLFW/GLFWWindow.cpp
    ${BERSEKER_SOURCE_DIR}/Window/GLFW/GLFWWindow.h
    ${BERSEKER_SOURCE_DIR}/Input/InputKeys.h
    ${BERSEKER_SOURCE_DIR}/Input/InputManager.h
    ${BERSEKER_SOURCE_DIR}/Application.cpp
    ${BERSEKER_SOURCE_DIR}/Application.h
    ${BERSEKER_SOURCE_DIR}/Scene.h
    ${BERSEKER_SOURCE_DIR}/Rendering/Primitives/Renderer.cpp
    ${BERSEKER_SOURCE_DIR}/Rendering/Primitives/Renderer.h
    ${BERSEKER_SOURCE_DIR}/Rendering/Primitives/Primitives.h
    ${BERSEKER_SOURCE_DIR}/Rendering/Utils.h
    ${BERSEKER_SOURCE_DIR}/Rendering/Utils.cpp
    ${BERSEKER_SOURCE_DIR}/Collision/BVH.cpp
    ${BERSEKER_SOURCE_DIR}/Collision/BVH.h
    ${BERSEKER_SOURCE_DIR}/Collision/BVolumes.cpp
    ${BERSEKER_SOURCE_DIR}/Collision/BVolumes.h
    ${BERSEKER_SOURCE_DIR}/ECS/ECS.cpp
    ${BERSEKER_SOURCE_DIR}/ECS/ECS.h
    ${BERSEKER_SOURCE_DIR}/ECS/Components/Transform.h
    ${BERSEKER_SOURCE_DIR}/ECS/Components/ColliderComponent.h
    ${BERSEKER_SOURCE_DIR}/ECS/Components/Identifier.h
    ${BERSEKER_SOURCE_DIR}/ECS/Components/Components.h
    ${BERSEKER_SOURCE_DIR}/Rendering/GraphicsAPI/FrameBuffer.cpp
    ${BERSEKER_SOURCE_DIR}/Rendering/GraphicsAPI/FrameBuffer.h
    ${BERSEKER_SOURCE_DIR}/Rendering/Material.hpp
    ${BERSEKER_SOURCE_DIR}/LightSource.h
    ${BERSEKER_SOURCE_DIR}/ResourceLoaders/ShaderRegistry.cpp
    ${BERSEKER_SOURCE_DIR}/ResourceLoaders/ShaderRegistry.h
    ${BERSEKER_SOURCE_DIR}/ResourceLoaders/ShaderResources.cpp
    ${BERSEKER_SOURCE_DIR}/ResourceLoaders/ShaderResources.h
    ${BERSEKER_SOURCE_DIR}/Rendering/LightSourceBillboard.cpp
    ${BERSEKER_SOURCE_DIR}/Rendering/LightSourceBillboard.h
    ${BERSEKER_SOURCE_DIR}/Rendering/GraphicsAPI/CubeMapTexture.hpp
    ${BERSEKER_SOURCE_DIR}/Rendering/Skybox.cpp
    ${BERSEKER_SOURCE_DIR}/Rendering/Skybox.h
    ${BERSEKER_SOURCE_DIR}/Core/Logger.cpp
    ${BERSEKER_SOURCE_DIR}/Core/Logger.h
    ${BERSEKER_SOURCE_DIR}/Core/Memory.cpp
    ${BERSEKER_SOURCE_DIR}/Core/Memory.h
    ${BERSEKER_SOURCE_DIR}/Core/Debug.h
)

# Set glfw library
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${BERSEKER_DEPENDENCIES_DIR}/glfw)

# Set glad library
add_subdirectory(${BERSEKER_DEPENDENCIES_DIR}/glad)

# Set glm library
add_subdirectory(${BERSEKER_DEPENDENCIES_DIR}/glm)

# Set spdlog library
add_subdirectory(${BERSEKER_DEPENDENCIES_DIR}/spdlog)

# Set assimp library
# add_subdirectory(${BERSEKER_DEPENDENCIES_DIR}/assimp)

# Set stb library
add_subdirectory(${BERSEKER_DEPENDENCIES_DIR}/stb)

add_library(
    ${BERSEKER_BINARY_NAME}
    ${BERSEKER_SOURCES}
)

target_link_libraries(
    ${BERSEKER_BINARY_NAME}
    glfw
    glad
    glm
    spdlog
    stb
    assimp
)

target_include_directories(
    ${BERSEKER_BINARY_NAME}
    PUBLIC ${BERSEKER_SOURCE_DIR}/
)