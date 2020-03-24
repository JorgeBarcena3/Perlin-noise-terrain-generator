
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

        GLuint vertex_list_id;

    public:

        void update(float delta);

        void render(sf::RenderWindow& window);

    };

}

#endif