#ifndef BIOME_H
#define BIOME_H

#include <vector>
#include <iostream>
#include <utility>
#include <cassert>
#include <QDebug>
#include "perlinnoise.h"
namespace PTG {
namespace data {
        /**
         * @brief The Biome class contains helping algorithms for generating a terrain,
         * such as finding water sources on a 2d tilemap, returning gradient values based on latitute,
         * etc.
         *
         * It stores similar maps of data as TerrainData.
         */
        class Biome {
            size_t map_size; // the height-map length-width size
            size_t length; // the length-width size for new Square Map
            size_t width;
            std::vector<std::vector<int>> height_map;
            std::vector<std::vector<bool>> ocean_map;
            std::vector<std::vector<double>> moisture_map;
            std::vector<std::vector<double>> temp_map;
            std::vector<std::vector<std::pair<int,int>>> wind_direction_map;
            std::vector<std::vector<double>> noise;
            double sea_level;
            double hill_level;
            double mount_level;

            /**
                This functions tries to find a source of moisture
                @param direction is the direction will be taking (backwards)
                @param k is the kth row of matrix
                @param r is the rth entry of kth row
                @param steps_taken is the number of steps taken backwards
            */
            double find_water_source(const std::pair<int,int>& direction,
                                            size_t k, size_t r, int steps_taken = 0) {
                // Try taking "steps" in the opposite direction of the wind.
                // Different terrain features affect how many steps are taken.
                if (steps_taken >= 40) {
                    return 0.0;
                }
                //else,
                if ((k == 0) && (direction.second*-1 == -1)) { // if we are going out of range
                    return 0.0; //exit
                }
                else if ((r == 0) && (direction.first == -1)) { // if we are going out of range
                    return 0.0; //exit
                }
                else { // else, we are not at an edge case.
                    // we are safe to use static casting
                    size_t stepk = k+static_cast<size_t>(direction.second*-1);// interpret direction to standard N-E-S-W coordinates
                    size_t stepr = r+static_cast<size_t>(direction.first); // interpret direction to standard N-E-S-W coordinates
                    steps_taken += 1; // increment steps_taken
                    if ((stepk >= length)||(stepr >= width)) { // if we are going out of range
                        return 0.0; // exit
                    }
                    if ((hill_level < height_map[stepk][stepr])&&(height_map[stepk][stepr] < mount_level)){
                            steps_taken += 10; // it should be harder to carry percipetation
                    }
                    if (height_map[stepk][stepr] >= mount_level){
                        return 0.0; //exit, we can't carry water through mountains.
                    }
                    // else,
                    if (ocean_map[stepk][stepr] == true){ // if we finally found a water source
                        return (10.0/(steps_taken)); // return source
                    }
                    // else, we didn't find a water source
                    return find_water_source(wind_direction_map[stepk][stepr],stepk,stepr,steps_taken);
                }
            }

            /**
                This funcitons returns what ougth to be the temperature at a given tile; Temperature
                is determined based on a formula and how many squares from the equation the current
                square is; The equator is interpreted as a size/2 (i.e square map size diveded by 2)
                @param int squares_from_equator is how many squares a certain tile is from the equator
            */
            double temperature_gradient(const int squares_from_equator) {
                // this is a quadratic function that gives us the temp
                // of every tile.
                double denom = length/2;
                double factor = -38.0/(denom*denom);
                // the quadratic equation
                return factor*squares_from_equator*squares_from_equator+28;
            }


            /**
                This functions sets the wind directions; it must be pre-defined for a sepcified square
                map size; Note that the bottom half of square map should be the horizonal mirror if the
                upper square map half.
            */
            void set_wind_dir_mask() {
                // Table corresponding to wind directions.
                std::vector<std::pair<int,int>> wind_table = {{0,-1},//{0,-1},{0,-1},{0,-1},//8
                                                                {-1,-1},//{-1,-1},{-1,-1},{-1,-1},//7
                                                                {-1,0},//{-1,0},{-1,0},{-1,0},//6
                                                                {1,0},//{1,0},{1,0},{1,0},//5
                                                                {1,1},//{1,1},{1,1},{1,1},//4
                                                                {0,1},//{0,1},{0,1},{0,1},//3
                                                                {0,-1},//{0,-1},{0,-1},//2
                                                                {-1,-1},//{-1,-1},{-1,-1},//1
                                                                {-1,0}}; //0
                // Iterate over all tiles on the wind direction map,
                // giving them appropriate values from the wind table.
                for (size_t k = 0; k <= (length)/2; ++k) { // for rows up to the half way point
                    for (size_t r = 0; r < width; ++r) { // for every entry of row
                        wind_direction_map[k][r] = wind_table[k*8/(length/2)];
                        auto inverted_wind = wind_table[k*8/(length/2)];
                        inverted_wind.first *= -1; // invert the wind direction
                        inverted_wind.second *= -1; // inver the wind direction
                        wind_direction_map[length-1-k][r] = inverted_wind;
                    }
                }
                for (size_t k = 0; k < length; ++k){
                    //qDebug() << wind_direction_map[k][0];
                }
            }

            /**
                This function generates moisture onto the land.
                This is accomplished by attempting to find a water source from every land tile.
            */
            void set_moisture_mask() {
                // for every square in the general square map
                for (size_t k = 0; k < length; ++k) {
                    for (size_t r = 0; r < width; ++r) {
                        // if we are currently on an ocean tile...
                        if (ocean_map[k][r] == false) {
                            moisture_map[k][r] = find_water_source(wind_direction_map[k][r],k,r);
                        }
                    }
                }
            }

        public:

            /**
                Constructs a Biome instance from a map and level parameters.
                @param map is the height map of T type of cells
                @param _sea_level is the current sea level
            */
            Biome(const std::vector<std::vector<int>>& map, double _sea_level, double _hill_level, double _mount_level) :
                    map_size(map.size()),
                    length(map_size),
                    width(map[0].size()),
                    height_map(length,std::vector<int>(width)),
                    ocean_map(length,std::vector<bool>(width)),
                    moisture_map(length,std::vector<double>(width)),
                    temp_map(length,std::vector<double>(width)),
                    wind_direction_map(length,std::vector<std::pair<int,int>>(width)),
                    noise(PerlinNoise(length,width).getMap()),
                    sea_level(_sea_level),
                    hill_level(_hill_level),
                    mount_level(_mount_level)
            {
                // Iterate over tiles, updating each tilemap.
                for (size_t k = 0; k < length; ++k) {
                    // for every entry in vec
                    for (size_t r = 0; r < width; ++r) {
                        // updating the moisture mask and ocean mask
                        height_map[k][r]  = map[k][r];
                        if (height_map[k][r] < sea_level) { // if this average value is below sea_level;
                            moisture_map[k][r] = 1.0;
                            ocean_map[k][r] = 1;
                        }
                        else {
                            moisture_map[k][r] = 0.0;
                            ocean_map[k][r] = 0;
                        }
                        // updating the temperature mask square
                        if (length/2 >= k){
                            temp_map[k][r] = temperature_gradient(static_cast<int>(length/2 - k));
                        }
                        else { // k is bigger, safe subtraction
                            temp_map[k][r] = temperature_gradient(static_cast<int>(k - length/2));
                        }
                        // not updating the wind direction mask here becuase it's pretty technical
                    }
                }
            }

            /**
                For a given coordinates, this functions returns the information of certain masks;
                @param i the row
                @param j is the entry of ith row
                @return is the pair of doubles where the first element moisture and the other is temperature
            */
            std::pair<double,double> get_tile_info(size_t i, size_t j) {
                double moisture = moisture_map[i][j];// + noise[i][j]/4;
                double temperature = temp_map[i][j];// + noise[i][j]/4;
                //if (ocean_map[i][j] == false)
                //    qDebug() << moisture;
                return std::pair<const double,const double>(moisture,temperature);
            }

            /**
                This function automates the need of setting up the moisture and wind directions masks
            */
            void operator()() {
                set_wind_dir_mask();
                set_moisture_mask();
            }

            /**
             * Calculate the average moisure value from the moisture map values over all land tiles.
             * @return the average land moisture value of this Biome.
             */
            double average_moisture() const {
                double value=0;
                int count=0;
                // Iterate over all values of ocean map,
                // adding them to the summing and counting variables.
                for (size_t k = 0; k < length; ++k){
                    for (size_t r = 0; r < length; ++r) {
                        if (ocean_map[k][r] == false){
                            value += moisture_map[k][r];
                            ++count;
                        }
                    }
                }
                return value/count;
            }
            /**
             * @brief get_height_map
             * @return this member's height map.
             */
            const std::vector<std::vector<int>>& get_height_map() {
            	return height_map;
            }
            /**
             * @brief get_ocean_map
             * @return this member's ocean map.
             */
            const std::vector<std::vector<bool>>& get_ocean_map() {
            	return ocean_map;
            }
            /**
             * @brief get_moisture_map
             * @return this member's moisture map.
             */
            const std::vector<std::vector<double>>& get_moisture_map() {
            	return moisture_map;
            }
            /**
             * @brief get_temp_map
             * @return this member's temperature map.
             */
            const std::vector<std::vector<double>>& get_temp_map() {
            	return temp_map;
            }
            /**
             * @brief get_noise_map
             * @returnhis member's noise map.
             */
            const std::vector<std::vector<double>>& get_noise_map() {
            	return noise;
            }            
        };
}
}
#endif
