
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
*                                                                             *
*  Started by Jorge Bárcena on March of 2020                               *
*                                                                             *
*  This is free software released into the public domain.                     *
*                                                                             *
*  j.barcenalumbreras@gmail.com                                               *
*                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "../headers/TerrainGeneration.hpp"
#include "../headers/Helper.hpp"
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#define WIDTH  700
#define HEIGHT  700

using namespace sf;
using namespace TerrainPerlingNoiseGeneration;

void reset_viewport(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, GLdouble(width), 0, GLdouble(height), +1, -1);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_MODELVIEW);
}


int main()
{
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "LightSpeed - Jorge Barcena", sf::Style::Default, ContextSettings(32));

    window.setVerticalSyncEnabled(true);

    TerrainGeneration generator;

    // Configuramos el OpenGL
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    reset_viewport(WIDTH, HEIGHT);

    bool running = true;

    /* initialize random seed: */
    srand(time(NULL));



    do
    {
        // Process window events:

        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                running = false;
            }

        }

        glClear(GL_COLOR_BUFFER_BIT);

        glLoadIdentity();
        glTranslatef(float(WIDTH / 2), float(HEIGHT / 2), 0.f);

        generator.update(0);

        generator.render(window);        

        window.display();

    } while (running);


    return EXIT_SUCCESS;
}
