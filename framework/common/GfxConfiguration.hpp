//
// Created by Chen.Zr on 2020/3/22.
//

#ifndef GAME_ENGINE_GFXCONFIGURATION_HPP
#define GAME_ENGINE_GFXCONFIGURATION_HPP

#pragma once

#include <cstdint>
#include <string>
#include <iostream>

namespace engine {
    struct GfxConfiguration {
        GfxConfiguration(uint32_t r = 8, uint32_t g = 8, uint32_t b = 8, uint32_t a = 8,
                         uint32_t s = 0, uint32_t d = 32, uint32_t msaa = 0,
                         uint32_t screenWidth = 1440, uint32_t screenHeight = 900,
                         const std::string& title = "default")
                : redBits(r), greenBits(g), blueBits(b), alphaBits(a), depthBits(d),
                  stencilBits(s), msaaSamples(msaa), screenWidth(screenWidth),
                  screenHeight(screenHeight), windowTitle(title) {}

        uint32_t redBits;
        uint32_t greenBits;
        uint32_t blueBits;
        uint32_t alphaBits;
        uint32_t depthBits;
        uint32_t stencilBits;
        uint32_t msaaSamples;
        uint32_t screenWidth;
        uint32_t screenHeight;
        std::string windowTitle;

        friend std::ostream& operator<<(std::ostream& out, const GfxConfiguration& config){
            out    << "GfxConfiguration: " <<
            "R: "  << config.redBits       <<
            ", G: "<< config.greenBits     <<
            ", B: "<< config.blueBits      <<
            ", A: "<< config.alphaBits     <<
            ", D: "<< config.depthBits     <<
            ", S: "<< config.stencilBits   <<
            ", M: "<< config.msaaSamples   <<
            ", W: "<< config.screenWidth   <<
            ", H: "<< config.screenHeight   <<
            std::endl;
            return out;
        }
    };
}

#endif //GAME_ENGINE_GFXCONFIGURATION_HPP
