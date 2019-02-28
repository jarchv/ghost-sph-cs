cmake_minimum_required(VERSION 3.13.3)
project(base C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


file(GLOB TOOLS src/tools/*.cpp)
file(GLOB COMMONS src/commons/*.cpp)
add_library(base
    ${TOOLS}
    ${COMMONS}
)

target_compile_features(base PUBLIC cxx_std_11)

add_executable(out src/main.cpp)

# glfw
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries(${GLFW_LIBRARY_DIRS})

# opengl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# glew
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

#target_compile_features(base PUBLIC cxx_std_11)



#set_target_properties(out PROPERTIES 
#                      LINKER_LANGUAGE CXX)
                      
target_link_libraries(
        out
        PRIVATE
        base
        glfw
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
)
install(TARGETS out DESTINATION /usr/lib)

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "-o3 -fopenmp")
endif()
