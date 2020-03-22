add_executable(osx_application)

target_sources(
        osx_application
        PRIVATE
        osx_application.cpp
)

target_link_libraries(
        osx_application
        PRIVATE
        glfw common "-framework OpenGL")

target_include_directories(
        osx_application
        PRIVATE
        ${CMAKE_SOURCE_DIR}/third_party/glfw-master/include
)
