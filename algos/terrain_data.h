#ifndef TERRAIN_DATA
#define TERRAIN_DATA

#include "biome.h"
#include "perlinnoise.h"
#include "diamond_square.h"
#include <QString>
namespace PTG {
namespace data {

	/**	The TerrainData struct will encapsulate all the data that is required to
		generate a world-biome. From the basics of such has height to the temperature
		and moisture noise masks.
	*/
	struct TerrainData {
		size_t length;	// the size of the map
		double sea_level; // the average sea level
		double hill_level; // the average hill level
		double mount_level; // the average mountain level
		std::vector<std::vector<int>> height;
		std::vector<std::vector<bool>> ocean;
		std::vector<std::vector<double>> moisture;
		std::vector<std::vector<double>> temp;
        std::vector<std::vector<double>> noise;
		double offset;

        /**
         * @brief TerrainData constructs a new terrain data object.
         * @param _length the size of the terrain to create.
         * @param _sea_level the sea cutoff level to use.
         * @param _hill_level the hill cutoff level to use.
         * @param _mount_level the mountain cutoff level to use.
         */
		TerrainData(size_t _length,
            double _sea_level = 0, double _hill_level = 0, double _mount_level = 0) :
		length(_length),
        sea_level(_sea_level),
		hill_level(_hill_level),
		mount_level(_mount_level),
        height(0,std::vector<int>(0)),
		ocean(0,std::vector<bool>(0)),
		moisture(0,std::vector<double>(0)),
		temp(0,std::vector<double>(0)),
        noise(PerlinNoise(length,length).getMap()),
		offset(0)
		{
			DiamondSquare obj(length);
			obj(); // generate the height map
            if (sea_level == 0.0){
                sea_level = obj.getAverageValue();
            }
            if (hill_level == 0.0) {
            	hill_level = sea_level+30;
            }
            if (mount_level == 0.0) {       	
                mount_level = sea_level+50;
            }
            //qDebug() << "sea_level :" << sea_level;

            height = obj.getMap();

			Biome obj2(height, sea_level, hill_level, mount_level);

            obj2(); // initialize moisture and winds
            offset = obj2.average_moisture()-.1;
            //qDebug() << obj2.average_moisture();
            ocean = std::move(obj2.get_ocean_map());
            moisture = std::move(obj2.get_moisture_map());
            temp = std::move(obj2.get_temp_map());


		}

        /**
         * @brief TerrainData TerrainData constructs a new terrain data object,
         * using DiamondSquare noise as a heightmap.
         * @param obj the DiamondSquare object to use for height.
         * @param _sea_level the sea cutoff level to use.
         * @param _hill_level the hill cutoff level to use.
         * @param _mount_level the mountain cutoff level to use.
         */
		TerrainData(DiamondSquare& obj,
			double _sea_level = 0, double _hill_level = 0, double _mount_level = 0) :
			sea_level(_sea_level),
			hill_level(_hill_level),
            mount_level(_mount_level),
            offset(0)
		{
            if (sea_level == 0.0){
                sea_level = obj.getAverageValue();
            }
            if (hill_level == 0.0) {
            	hill_level = sea_level+30;
            }
            if (mount_level == 0.0) {       	
                mount_level = sea_level+50;
            }
            height = obj.getMap();
			length = height.size();
            noise = PerlinNoise(length,length).getMap();
			Biome obj2(height, sea_level, hill_level, mount_level);
            obj2(); // initialize moisture and winds
            offset = 1.5;
            //qDebug() << obj2.average_moisture();
            ocean = std::move(obj2.get_ocean_map());
            moisture = std::move(obj2.get_moisture_map());
            temp = std::move(obj2.get_temp_map());

		}

        /**
         * @brief get_land_art looks up the appropriate biome color to use for a tile,
         * based on some function of moisture and temperature.
         * @param k the horizontal dimension of this tile.
         * @param r the vertical dimension of this tile.
         * @return a string for the appropriate QPixmap to use.
         */
        const QString get_land_art(size_t k, size_t r) const {
			double height_value = height[k][r];
            double moist = moisture[k][r] + noise[k][r];
            double tem = temp[k][r] + noise[k][r];
			QString str;
			QString postfix;
			QString prefix;
			// first determine height;
			if (height_value < hill_level) {
				// plains
				prefix = "";
				postfix = "";

			}
			else if ((height_value >= hill_level )&&(height_value < mount_level)) {
				// a hill
				prefix = "hill/";
				postfix = "-hill";
			}
			else {
				// a mountain
				prefix = "mount/";
				postfix = "-mount";
			}
            if (tem<= -5) {
				str = "tundra";
				//tundra only
			}
            else if ((-5< tem)&&(tem <= 8)){
				//qDebug() << temp;
                if (moist< 0.25*offset){
					// cold desesrt
					str = "colddesert";
				}
                else if ((moist>= 0.25*offset)&&(moist < 0.30*offset )) {
					// woodland
					str = "woodland";

				}
                else if (moist >= 0.30*offset) {//&&(moisture <= 0.5)) {
					// boreal forest
					str = "borforest";
				}
			}
           else if ((8 < tem) &&(tem <=20)) {
				//qDebug() << temp;
                if (moist < 0.25*offset){
					// cold desert
					str = "colddesert";

				}
                else if ((moist >= 0.25*offset)&&(moist <0.35*offset)){
					// woodland
					str = "woodland";

				}
                else if ((moist >=0.35*offset)&&(moist < 0.55*offset)){
				   // temp seasonal forest
					str = "tempsforest";

				}
				else {
					// temperate rain forest
					str = "temprforest";

				}
			}
			else { // temp is greater than 20
                if (moist < 0.25*offset) {
					//subtrop desert
					str = "subdesert";

				}
                else if ((moist >= 0.25*offset)&&(moist < 0.55*offset)) {
					// tropical seasonal forest
					str = "tropsforest";

				}
				else {
					// tropical rain forest
					str = "troprforest";

				}
			}

            str = ":/textures/" + prefix + str + postfix + ".png";
			return str;
		}

	};
}
}

#endif
