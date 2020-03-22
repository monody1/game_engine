//
// Created by Chen.Zr on 2020/3/20.
//

#include "base_application.hpp"

namespace engine{
    GfxConfiguration config;
    BaseApplication g_App = BaseApplication(config);
    IApplication *g_pApp = &g_App;
}
