//
// Created by Chen.Zr on 2020/3/22.
//

#ifndef GAME_ENGINE_OSX_APPLICATION_HPP
#define GAME_ENGINE_OSX_APPLICATION_HPP

#include "base_application.hpp"
#include <GLFW/glfw3.h>

namespace engine {

    class OsxApplication: implements BaseApplication {
    private:
        GLFWwindow * m_pWindow = nullptr;
    public:
        OsxApplication(const GfxConfiguration &Config);

        int Initialize() override;

        void Finalize() override;

        void Tick() override;

        bool IsQuit() override;
    };
}


#endif //GAME_ENGINE_OSX_APPLICATION_HPP
