
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
*                                                                             *
*  Started by Jorge Bárcena on March of 2020                                  *
*                                                                             *
*  This is free software released into the public domain.                     *
*                                                                             *
*  j.barcenalumbreras@gmail.com                                               *
*                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#ifndef START_HEADER
#define START_HEADER

#include <SFML/Graphics.hpp>
#include "SFML/OpenGL.hpp"
#include <Vector.hpp>

using namespace toolkit;
using namespace sf;

namespace TerrainPerlingNoiseGeneration
{
    /*
    * Creador del terreno
    */
    class TerrainGeneration 
    {    

    private:

        int cols;

        int rows;

        int scale = 40;

        std::vector<GLuint> vertex_list_id;

    public:

        TerrainGeneration()
        {
            int w = 600;
            int h = 600;

            cols = w / scale;
            rows = h / scale;
        }

        int get_scale()
        {
            return scale;
        }

        void drawRect(float x, float y, float w, float h);

        void update(float delta);

        void render(sf::RenderWindow& window);

    };

}

#endif