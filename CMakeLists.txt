cmake_minimum_required (VERSION 3.30)

project ("GameEngine")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME}
    src/main.cpp
 "src/EntityManger.cpp" "include/ecs/EntityManager.h" "include/ecs/Types.h" "include/ecs/Ecs.h" "src/Ecs.cpp" "include/ecs/ComponentArray.h" "include/ecs/ComponentsManager.h"  "src/ComponentsManager.cpp" "include/ecs/System.h" "include/ecs/View.h" "include/ecs/SystemManager.h")


target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)