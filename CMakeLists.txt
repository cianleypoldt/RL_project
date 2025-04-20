cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main src/main.cpp "src/Display/Renderer.h" "src/Display/Renderer.cpp" "src/Display/Drawable.cpp" "src/Utility/utilities.h" "src/Utility/utilities.cpp" "src/Utility/geometry.cpp" "src/Physics/RigidBody.h" "src/Physics/Constraint.h" "src/Physics/Simulation.h" "src/Physics/RigidBody.cpp" "src/Physics/Simulation.cpp")
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)
