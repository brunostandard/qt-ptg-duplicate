#include "algos/perlinnoise.h"

namespace PTG{
namespace data{
    PerlinNoise::PerlinNoise(const size_t width, const size_t height) :  width(width), height(height),
        map(width, std::vector<double>(height))
    {
        siv::PerlinNoise noise(1337420);

        for(size_t y = 0; y < height; y++){
            for(size_t x = 0; x < width; x++){
                map[x][y] = noise.octaveNoise0_1(x / (width / 8.0), y / (height / 8.0), 4);
            }
        }
    }

    const std::vector<std::vector<double> > &PerlinNoise::getMap()
    {
        return map;
    }
}
}
