
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
*                                                                             *
*  Started by Jorge B�rcena on March of 2020                                  *
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

    // Se compilan los comandos que dibujan el c�rculo en la lista:

    glNewList(vertex_list_id, GL_COMPILE);
    {
        // Se establece el color:

        glColor3ub(255,0,0);

        // Se dibuja el c�rculo con coordenadas locales de v�rtices cacheadas:

        glBegin(GL_TRIANGLE_FAN);
        {
            // Se a�ade el primer v�rtice en el centro:

            glVertex2f(0, 0);

            // Se a�aden v�rtices sobre el borde del c�rculo:

            for (float angle = 0.f; angle < 6.283185f; angle += 0.1f)
            {
                glVertex2f(std::cosf(angle) * 10, std::sinf(angle) * 10);
            }

            // Se a�ade un �ltimo v�rtice de cierre donde angle vale 0

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
