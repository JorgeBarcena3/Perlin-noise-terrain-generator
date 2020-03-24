
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

void TerrainPerlingNoiseGeneration::TerrainGeneration::drawRect(float x, float y, float w, float h)
{

    float w2 = w / 2;
    float h2 = h / 2;

    glVertex3i(x - w2, y - h2, 1);
    glVertex3i(x - w2, y + h2, 1);
    glVertex3i(x + w2, y + h2, 1);
    glVertex3i(x + w2, y - h2, 1);
}

void TerrainPerlingNoiseGeneration::TerrainGeneration::update(float delta)
{

    float radius = 350;

    // Se crea una lista y se guarda su identificador:

    for (int x = 0; x < cols; x++)
    {
        for (int y = 0; y < rows; y++)
        {
            // Se compilan los comandos que dibujan el círculo en la lista:

            vertex_list_id.push_back( glGenLists(1) );

            glNewList(vertex_list_id[vertex_list_id.size() - 1], GL_COMPILE);
            {
                // Se establece el color:

                glColor3ub(255, 255, 255);

                // Se dibuja el círculo con coordenadas locales de vértices cacheadas:

                glBegin(GL_TRIANGLE_FAN);
                {
                    drawRect(x * scale, y * scale, scale, scale);

                }
                glEnd();
            }
            glEndList();

        }
    }



}

void TerrainPerlingNoiseGeneration::TerrainGeneration::render(sf::RenderWindow& window)
{
    for (auto id : vertex_list_id)
    {
        glCallList(id);
    }

}
