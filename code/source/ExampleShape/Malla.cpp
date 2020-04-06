
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Jorge Barcena on March of 2020                                  *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  j.barcenalumbreras@gmail.com                                               *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <GL/glew.h>            // Debe incluirse antes que gl.h
#include "../../header/exampleShapes/Malla.hpp"
#include <SFML/OpenGL.hpp>
#include <cmath>
#include <glm/vec3.hpp>

#define PI2 2.0 * 3.141592

namespace exampleShapes
{

    Malla::Malla(int _grid_size, int _square_size)
    {

        grid_size = _grid_size;
        square_size = _square_size;

        std::vector< GLfloat > normals;
        std::vector< GLfloat > colors;

        // Se generan índices para los VBOs del cubo:

        glGenBuffers(VBO_COUNT, vbo_ids);
        glGenVertexArrays(1, &vao_id);

        // Se activa el VAO del cubo para configurarlo:

        glBindVertexArray(vao_id);

        /**********************
        ** DATOS DE VERTICES **
        ***********************/
        createVertices(coordinates, normals);

        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[COORDINATES_VBO]);
        glBufferData(GL_ARRAY_BUFFER, coordinates.size() * sizeof(GLfloat), &coordinates[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        /*******************
        ** DATOS DE COLOR **
        ********************/
        createColors(colors, coordinates);

        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[COLORS_VBO]);
        glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), &colors[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

        /**********************
        ** DATOS DE NORMALES **
        ***********************/

        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[NORMALS_VBO]);
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), &normals[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);


        /*********************
        ** DATOS DE INDICES **
        **********************/

        createIndices(coordinates);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_ids[INDICES_IBO]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLubyte), &indices[0], GL_STATIC_DRAW);

        glBindVertexArray(0);
    }

    Malla::~Malla()
    {
        // Se liberan los VBOs y el VAO usados:

        glDeleteVertexArrays(1, &vao_id);
        glDeleteBuffers(VBO_COUNT, vbo_ids);
    }

    void Malla::createVertices(std::vector< GLfloat >& coordinates, std::vector< GLfloat >& normals)
    {

        float vertex_number = grid_size * grid_size;

        float x = 0, z = 0, offset = square_size, index = 0;

        for (float i = 0; i < vertex_number; i++)
        {
            coordinates.push_back(x); // x
            coordinates.push_back(0); // y
            coordinates.push_back(z); // z

            normals.push_back(0); // x
            normals.push_back(1); // y
            normals.push_back(0); // z

            if (index >= (grid_size - 1)) // Cambiamos de linea
            {
                x = 0;
                z += offset;
                index = 0;
            }
            else
            {
                x += offset;
                index++;
            }


        }

    }

    void Malla::createIndices(std::vector< GLfloat >& coordinates)
    {

        float offset_y = 1;
        float offset_x = 0;
        int index = 0;
        int vertex_triangles = ( coordinates.size() / 3 ) - grid_size;

        for (int i = 0; i < vertex_triangles; i++)
        {
            float bottomOffset = grid_size * offset_y + offset_x;

            indices.push_back(i);
            indices.push_back(bottomOffset + 0);
            indices.push_back(bottomOffset + 1);


            indices.push_back(bottomOffset + 1);
            indices.push_back(i + 1);
            indices.push_back(i);

            if ( (index + 1 ) >= (grid_size - 1)) // Cambio de linea
            {
                offset_y++;
                index = 0;
                offset_x = 0;
                i++;
            }
            else
            {
                offset_x++;
                index++;
            }


        }

    }

    void Malla::createColors(std::vector< GLfloat >& colors, std::vector< GLfloat >& coordinates)
    {
        colors.resize(coordinates.size());

        for (size_t i = 0; i < colors.size(); i += 3)
        {
            colors[i] = (0.5f);
            colors[i + 1] = (0.25f);
            colors[i + 2] = (1);
        }
    }

    void Malla::render()
    {
        // Se selecciona el VAO que contiene los datos del objeto y se dibujan sus elementos:

        glBindVertexArray(vao_id);
        glDrawElements(GL_TRIANGLES, indices.size() * sizeof(GLubyte), GL_UNSIGNED_BYTE, 0);
        glBindVertexArray(0);
    }

}
