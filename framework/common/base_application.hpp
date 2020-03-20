//
// Created by Chen.Zr on 2020/3/20.
//

#ifndef GAME_ENGINE_BASE_APPLICATION_HPP
#define GAME_ENGINE_BASE_APPLICATION_HPP

#include "appliction.hpp"

namespace engine {
    class BaseApplication: implements IApplication{
    public:
        int Initialize() override ;

        void Finalize() override;

        void Tick() override;

        bool IsQuit() override;

    protected:
        bool b_quit_;
    };
}


#endif //GAME_ENGINE_BASE_APPLICATION_HPP
