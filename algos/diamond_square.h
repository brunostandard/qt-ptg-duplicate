// Copyright (c) 2018 Martyn Afford
// Licensed under the MIT licence
#ifndef DIAMOND_SQUARE_H
#define DIAMOND_SQUARE_H

#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <random>
#include <vector>
#include <cassert>

namespace PTG {
    namespace data {
        typedef std::vector<int> iVec;
       /**
        * Algorithm for generating a std::vector matrix of procedural height map information.
        * It is mainly a wrapper on the diamond square functions below, which is adapted from Martyn Afford.
        * The returned matrix contains type double.
        */
        class DiamondSquare {
        private:
            std::size_t size;
            std::vector<iVec> map;
            int sum_of_values;
            bool noWrapFlag;
        public:
            /**
             * @brief DiamondSquare constructs an empty, 1x1 map by default.
             */
            DiamondSquare();

            /**
             * @brief DiamondSquare constructs a map of a giving size and wrapping style.
             * The map only has corner seed, and the algorithm itself is ran with the () operator.
             *
             * @param _size the size to generate the heightmap with.
             * @param _noWrapFlag flag if this noise map should wrap: it is true by default.
             */
            DiamondSquare(const std::size_t _size, bool _noWrapFlag = true);

            /**
             * @brief setMap sets the size of map to generate.
             * @param _size the size of map to generate.
             */
            void setMap(const std::size_t _size);

            /**
             * @brief operator () randomizes the values of this heightmap.
             */
            void operator()();

            /**
             * @brief getAverageValue gets the average height value from this DiamondSquare algorithm.
             * @return the average value.
             */
            int getAverageValue() const;

            /**
             * @brief getMap gets the vector of vectors representing a heightmap.
             * @return
             */
            const std::vector<iVec>& getMap();

            /**
             * @brief operator << outputs terrain information to the console.
             * @param out the output stream to use.
             * @param that the DiamondSquare object to output to the console.
             * @return
             */
            friend std::ostream& operator<<(std::ostream& out, const DiamondSquare& that);
        };
        
        std::ostream& operator<<(std::ostream& out, const DiamondSquare& that);
    }
}

namespace heightfield {

/// Generate a heightfield using random midpoint displacement and the
/// diamond-square algorithm.
///
/// \param size
///   Size of the desired heightfield. Valid values are powers of two plus one
///   (i.e., 2^n + 1), such as 129, 257 and 513. Must be at least five. Invalid
///   sizes will trigger an assertion failure.
/// \param random
///   A callback of the form `float(float limit)` that returns a random value
///   ranging from 0 (inclusive) to limit (exclusive).
/// \param variance
///   A callback of the form `float(int level)` that returns the maximum
///   variance in one direction for the specified level. The level starts from
///   zero and increases for each recursion. For example, a heightfield of size
///   129 has seven levels, zero through six. Generally speaking, the variance
///   halves each iteration. A good start is `constant * pow(0.5f, level)`.
/// \param at
///   A callback of the form `U(int, int)` that returns a mutable reference to
///   the heightfield location specified by the coordinates. A coordinate will
///   range from zero (inclusive) to size (exclusive). The return type U can be
///   any numeric type but it must be, or act as, a non-const reference to allow
///   the algorithm to output its results. This allows the user to decide how
///   the heightfield is stored in memory.
///
/// The corner points of the heightfield should be initialised to suitable
/// starting values before calling this function.
///
/// The resulting heightfield is not tileable. Points along the edges are
/// averaged over three neighbouring points instead of the usual four.
///
/// Variance is defined in one direction but is applied in both. If we assume
/// an integer type for the heightfield and an initial value of 128, then a
/// variance of 128 will result in a range of 0 to 255.
///
/// No clamping is performed by this algorithm so if the randomness, variance
/// and initial values combine to generate a value smaller or larger than the
/// data type referenced by `at`, underflow or overflow can occur.
///
/// The time complexity of this algorithm is O(n^2) where n is `size`. The
/// space complexity is constant (and small) as this algorithm makes no
/// allocations internally, relying on the user to provide the data structure
/// and accessing it via `at`.
template <typename T, typename T2, typename T3>
int 
diamond_square_no_wrap(int size, T&& random, T2&& variance, T3&& at)
{
    //assert(size >= 5 && ((size - 1) & (size - 2)) == 0 && "valid size");
    int sum_of_values = 0;
    int level = 0;
    int stride = size - 1;
    int end = size - 1;

    while (stride > 1) {
        auto range = variance(level);
        auto half = stride / 2;

        // diamond step
        for (int y = 0; y < end; y += stride) {
            for (int x = 0; x < end; x += stride) {
                auto tl = at(x, y);
                auto bl = at(x, y + stride);
                auto tr = at(x + stride, y);
                auto br = at(x + stride, y + stride);

                auto average = (tl + tr + br + bl) / 4.0f;
                auto displacement = random(range * 2) - range;

                at(x + half, y + half) = average + displacement;
                sum_of_values += at(x + half, y + half);
            }
        }

        // square step
        // top
        for (int x = half; x < end; x += stride) {
            auto down = at(x, half);
            auto left = at(x - half, 0);
            auto right = at(x + half, 0);

            auto average = (down + left + right) / 3.0f;
            auto displacement = random(range * 2) - range;

            at(x, 0) = average + displacement;
            sum_of_values += at(x,0);
        }

        // bottom
        for (int x = half; x < end; x += stride) {
            auto up = at(x, end - half);
            auto left = at(x - half, end);
            auto right = at(x + half, end);

            auto average = (up + left + right) / 3.0f;
            auto displacement = random(range * 2) - range;

            at(x, end) = average + displacement;
            sum_of_values += at(x,end);
        }

        // left
        for (int y = half; y < end; y += stride) {
            auto up = at(0, y - half);
            auto down = at(0, y + half);
            auto right = at(half, y);

            auto average = (up + down + right) / 3.0f;
            auto displacement = random(range * 2) - range;

            at(0, y) = average + displacement;
            sum_of_values += at(0,y);
        }

        // right
        for (int y = half; y < end; y += stride) {
            auto up = at(end, y - half);
            auto down = at(end, y + half);
            auto left = at(end - half, y);

            auto average = (up + down + left) / 3.0f;
            auto displacement = random(range * 2) - range;

            at(end, y) = average + displacement;
            sum_of_values += at(end,y);
        }

        // centre
        bool offset = true;

        for (int y = half; y < end; y += half) {
            for (int x = offset ? stride : half; x < end; x += stride) {
                auto up = at(x, y - half);
                auto down = at(x, y + half);
                auto left = at(x - half, y);
                auto right = at(x + half, y);

                auto average = (up + down + left + right) / 4.0f;
                auto displacement = random(range * 2) - range;

                at(x, y) = average + displacement;
                sum_of_values += at(x,y);
            }

            offset = !offset;
        }

        stride /= 2;
        ++level;
    }
    return sum_of_values;
}

/// Generate a tileable heightfield using random midpoint displacement and the
/// diamond-square algorithm.
///
/// \param size
///   Size of the desired heightfield. Valid values are powers of two (i.e.,
///   2^n), such as 128, 256 and 512. Must be at least four. Invalid sizes will
///   trigger an assertion failure.
/// \param random
///   A callback of the form `float(float limit)` that returns a random value
///   ranging from 0 (inclusive) to limit (exclusive).
/// \param variance
///   A callback of the form `float(int level)` that returns the maximum
///   variance in one direction for the specified level. The level starts from
///   zero and increases for each recursion. For example, a heightfield of size
///   128 has seven levels, zero through six. Generally speaking, the variance
///   halves each iteration. A good start is `constant * pow(0.5f, level)`.
/// \param at
///   A callback of the form `U(int, int)` that returns a mutable reference to
///   the heightfield location specified by the coordinates. A coordinate will
///   range from zero (inclusive) to size (exclusive). The return type U can be
///   any numeric type but it must be, or act as, a non-const reference to allow
///   the algorithm to output its results. This allows the user to decide how
///   the heightfield is stored in memory.
///
/// The top left point of the heightfield should be initialised to a suitable
/// starting value before calling this function.
///
/// The resulting heightfield is tileable.
///
/// Variance is defined in one direction but is applied in both. If we assume
/// an integer type for the heightfield and an initial value of 128, then a
/// variance of 128 will result in a range of 0 to 255.
///
/// No clamping is performed by this algorithm so if the randomness, variance
/// and initial values combine to generate a value smaller or larger than the
/// data type referenced by `at`, underflow or overflow can occur.
///
/// The time complexity of this algorithm is O(n^2) where n is `size`. The
/// space complexity is constant (and small) as this algorithm makes no
/// allocations internally, relying on the user to provide the data structure
/// and accessing it via `at`.
template <typename T, typename T2, typename T3>
int
diamond_square_wrap(int size, T&& random, T2&& variance, T3&& at)
{
    //assert(size >= 4 && (size & (size - 1)) == 0 && "valid size");

    int level = 0;
    int stride = size;
    int end = size;
    int mask = size - 1;

    auto at_wrap = [&at, mask](int x, int y) { return at(x & mask, y & mask); };

    while (stride > 1) {
        auto range = variance(level);
        auto half = stride / 2;

        // diamond step
        for (int y = 0; y < end; y += stride) {
            for (int x = 0; x < end; x += stride) {
                auto tl = at(x, y);
                auto bl = at_wrap(x, y + stride);
                auto tr = at_wrap(x + stride, y);
                auto br = at_wrap(x + stride, y + stride);

                auto average = (tl + tr + br + bl) / 4.0f;
                auto displacement = random(range * 2) - range;

                at(x + half, y + half) = average + displacement;
            }
        }

        // square step
        // top
        for (int x = half; x < end - stride; x += stride) {
            auto up = at(x, end - half);
            auto down = at(x, half);
            auto left = at(x - half, 0);
            auto right = at(x + half, 0);

            auto average = (up + down + left + right) / 4.0f;
            auto displacement = random(range * 2) - range;

            at(x, 0) = average + displacement;
        }

        // top rightmost
        {
            int x = end - half;
            auto up = at(x, end - half);
            auto down = at(x, half);
            auto left = at(x - half, 0);
            auto right = at(0, 0);

            auto average = (up + down + left + right) / 4.0f;
            auto displacement = random(range * 2) - range;

            at(x, 0) = average + displacement;
        }

        // left
        for (int y = half; y < end; y += stride) {
            auto up = at(0, y - half);
            auto down = at(0, y + half);
            auto left = at(end - half, y);
            auto right = at(half, y);

            auto average = (up + down + left + right) / 4.0f;
            auto displacement = random(range * 2) - range;

            at(0, y) = average + displacement;
        }

        // left bottommost
        {
            int y = end - half;
            auto up = at(0, y - half);
            auto down = at(0, 0);
            auto left = at(end - half, y);
            auto right = at(half, y);

            auto average = (up + down + left + right) / 4.0f;
            auto displacement = random(range * 2) - range;

            at(0, y) = average + displacement;
        }

        // centre
        bool offset = true;

        for (int y = half; y < end; y += half) {
            for (int x = offset ? stride : half; x < end; x += stride) {
                auto up = at(x, y - half);
                auto down = at_wrap(x, y + half);
                auto left = at(x - half, y);
                auto right = at_wrap(x + half, y);

                auto average = (up + down + left + right) / 4.0f;
                auto displacement = random(range * 2) - range;

                at(x, y) = average + displacement;
            }

            offset = !offset;
        }

        stride /= 2;
        ++level;
    }
    return 100;
}
} // heightfield namespace

#endif /* DIAMOND_SQUARE_HPP */
