//
// Created by Chen.Zr on 2020/3/20.
//

#include "base_application.hpp"

int engine::BaseApplication::Initialize() {
    b_quit_ = false;
    return 0;
}

void engine::BaseApplication::Finalize() {

}

void engine::BaseApplication::Tick() {

}

bool engine::BaseApplication::IsQuit() {
    return b_quit_;
}
