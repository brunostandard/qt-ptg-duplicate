// Copyright (c) 2018 Martyn Afford
// Licensed under the MIT licence
#include "diamond_square.h"
namespace PTG {
    
    namespace data {
        DiamondSquare::DiamondSquare() : size(1), map(0,iVec(0)), noWrapFlag(true) {};
        DiamondSquare::DiamondSquare(const std::size_t _size, bool _noWrapFlag) :  size(_size),
            map(size,iVec(size)), noWrapFlag(_noWrapFlag) {
                std::size_t edge = size-1;
                map[0][0] = 128;
                map[0][edge] = 128;
                map[edge][0] = 128;
                map[edge][edge] = 128;
        }
        void DiamondSquare::setMap(const std::size_t _size) {
            size = static_cast<std::size_t>(std::pow(2,_size)+1);
            std::size_t edge = _size-1;
            map.clear();
            std::vector<iVec> temp(size,iVec(size));
            std::swap(temp,map);
            map[0][0] = 128;
            map[0][edge] = 128;
            map[edge][0] = 128;
            map[edge][edge] = 128;
        }
        void DiamondSquare::operator()() {
            auto& imap = map;
            auto seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::default_random_engine engine(seed);
            std::uniform_real_distribution<float> distribution{0, 1};
            
            if (noWrapFlag) {
                assert(size >= 5 && ((size - 1) & (size - 2)) == 0 && "valid size");
                heightfield::diamond_square_no_wrap(
                size,
                // random
                [&engine, &distribution](float range) {
                    return distribution(engine) * range;
                },
                // variance
                [](int level) { return 128 * std::pow(0.7f, level); },
                // at
                [&imap](int x, int y) -> int& { return imap[y][x]; });
            }

            else {
                assert(size >= 4 && (size & (size - 1)) == 0 && "valid size");
                heightfield::diamond_square_wrap(
                size,
                // random
                [&engine, &distribution](float range) {
                    return distribution(engine) * range;
                },
                // variance
                [](int level) { return 128 * std::pow(0.25f, level); },
                // at
                [&imap](int x, int y) -> int& { return imap[y][x]; });
            }
        
        }
        
        //std::size_t DiamondSquare::getSize() { return size; }
        
        const std::vector<iVec>& DiamondSquare::getMap() {  return map; }

        std::ostream& operator<<(std::ostream& out, const DiamondSquare& that) {
            for (auto& row : that.map) {
                for (auto cell : row) {
                out << cell << ' ';
                }
                out << '\n';
            }
            return out;
        }        
    }
}
