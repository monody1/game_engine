//
// Created by Chen.Zr on 2020/3/20.
//

#ifndef GAME_ENGINE_BASE_APPLICATION_HPP
#define GAME_ENGINE_BASE_APPLICATION_HPP

#include "appliction.hpp"
#include "GfxConfiguration.hpp"

namespace engine {
    class BaseApplication: implements IApplication{
    public:
        BaseApplication(const GfxConfiguration &mConfig);

        BaseApplication() = delete;

        int Initialize() override ;

        void Finalize() override;

        void Tick() override;

        bool IsQuit() override;

    protected:
        static bool m_bQuit;
        engine::GfxConfiguration m_Config;
    };
}


#endif //GAME_ENGINE_BASE_APPLICATION_HPP
