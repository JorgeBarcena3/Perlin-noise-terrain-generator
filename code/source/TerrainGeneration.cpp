
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
*                                                                             *
*  Started by Jorge Bárcena on March of 2020                                  *
*                                                                             *
*  This is free software released into the public domain.                     *
*                                                                             *
*  j.barcenalumbreras@gmail.com                                               *
*                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "../headers/TerrainGeneration.hpp"

void TerrainPerlingNoiseGeneration::TerrainGeneration::update(float delta)
{

    // Se crea una lista y se guarda su identificador:

    vertex_list_id = glGenLists(1);

    // Se compilan los comandos que dibujan el círculo en la lista:

    glNewList(vertex_list_id, GL_COMPILE);
    {
        // Se establece el color:

        glColor3ub(255,0,0);

        // Se dibuja el círculo con coordenadas locales de vértices cacheadas:

        glBegin(GL_TRIANGLE_FAN);
        {
            // Se añade el primer vértice en el centro:

            glVertex2f(0, 0);

            // Se añaden vértices sobre el borde del círculo:

            for (float angle = 0.f; angle < 6.283185f; angle += 0.1f)
            {
                glVertex2f(std::cosf(angle) * 10, std::sinf(angle) * 10);
            }

            // Se añade un último vértice de cierre donde angle vale 0

            glVertex2f(10, 0);
        }
        glEnd();
    }
    glEndList();

}

void TerrainPerlingNoiseGeneration::TerrainGeneration::render(sf::RenderWindow& window)
{

    glCallList(vertex_list_id);

}
