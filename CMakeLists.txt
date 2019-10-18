project(vkapp)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11 ")

file(GLOB vkapp_SRC "src/*.h" "src/*.hpp" "src/*.c" "src/*.cpp")

add_executable(${PROJECT_NAME} ${vkapp_SRC})

find_package(Vulkan REQUIRED)
find_package(glfw3 3.3 REQUIRED)

if (VULKAN_FOUND)
    message(STATUS  "Found Vulkan, Including and Linking now")
    include_directories(${Vulkan_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${Vulkan_LIBRARIES} glfw)
endif (VULKAN_FOUND)

target_include_directories(vkapp PUBLIC "include")