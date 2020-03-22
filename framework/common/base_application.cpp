//
// Created by Chen.Zr on 2020/3/20.
//

#include "base_application.hpp"

bool engine::BaseApplication::m_bQuit = false;

int engine::BaseApplication::Initialize() {
    std::cout << m_Config;
    return 0;
}

void engine::BaseApplication::Finalize() {

}

void engine::BaseApplication::Tick() {

}

bool engine::BaseApplication::IsQuit() {
    return m_bQuit;
}

engine::BaseApplication::BaseApplication(const engine::GfxConfiguration &Config)
: m_Config(Config) {}
