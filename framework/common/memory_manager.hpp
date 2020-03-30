//
// Created by Chen.Zr on 2020/3/22.
//

#ifndef GAME_ENGINE_MEMORY_MANAGER_HPP
#define GAME_ENGINE_MEMORY_MANAGER_HPP

#include "runtime_module.hpp"
#include "allocator.hpp"

namespace engine {
    class MemoryManager: implements IRuntimeModule {
    public:
        int Initialize() override;

        void Finalize() override;

        void Tick() override;
    };
}


#endif //GAME_ENGINE_MEMORY_MANAGER_HPP
