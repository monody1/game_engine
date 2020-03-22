//
// Created by Chen.Zr on 2020/3/22.
//

#include "osx_application.hpp"

namespace engine{
    GfxConfiguration config;
    BaseApplication g_App = OsxApplication(config);
    IApplication *g_pApp = &g_App;
}

int engine::OsxApplication::Initialize() {
    int res = BaseApplication::Initialize();

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    m_pWindow = glfwCreateWindow(config.screenWidth, config.screenHeight, config.windowTitle.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_pWindow);
    return res;
}

void engine::OsxApplication::Finalize() {
    glfwDestroyWindow(m_pWindow);
    glfwTerminate();
}

void engine::OsxApplication::Tick() {
    glfwPollEvents();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(m_pWindow);
}

bool engine::OsxApplication::IsQuit() {
    return BaseApplication::IsQuit();
}

engine::OsxApplication::OsxApplication(const engine::GfxConfiguration &Config) : BaseApplication(Config) {}
