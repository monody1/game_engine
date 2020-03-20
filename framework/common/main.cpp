#include <iostream>
#include "appliction.hpp"

using namespace engine;

namespace engine {
    extern IApplication *g_p_app;
}

int main() {
    int ret;

    if ((ret = g_p_app -> Initialize() != 0)){
        std::cout << "App Initialize failed, will exit now." << std::endl;
        return ret;
    }
    while(!g_p_app -> IsQuit()) {
        g_p_app->Tick();
    }

    g_p_app->Finalize();

    return 0;
}