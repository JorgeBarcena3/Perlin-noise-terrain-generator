
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
#include "../../header/exampleShapes/Cylinder.hpp"
#include <SFML/OpenGL.hpp>
#include <cmath>
#include <glm/vec3.hpp>

#define PI2 2.0 * 3.141592

namespace exampleShapes
{

    Cylinder::Cylinder(float _radius, float _height, float _sides)
    {

        radius = _radius;
        height = _height;
        sides = _sides;

        std::vector< GLfloat > coordinates;
        std::vector< GLfloat > normals;
        std::vector< GLfloat > tx;
        std::vector< GLfloat > colors;

        // Se generan índices para los VBOs del cubo:

        glGenBuffers(VBO_COUNT, vbo_ids);
        glGenVertexArrays(1, &vao_id);

        // Se activa el VAO del cubo para configurarlo:

        glBindVertexArray(vao_id);

        /**********************
        ** DATOS DE VERTICES **
        ***********************/
        createVertices(coordinates, normals, tx);

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
        ** DATOS DE TEXTURA **
        **********************/

        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[TEXTURE_VBO]);
        glBufferData(GL_ARRAY_BUFFER, tx.size() * sizeof(GLfloat), &tx[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, 0);


        /*********************
        ** DATOS DE INDICES **
        **********************/

        createIndices(coordinates);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_ids[INDICES_IBO]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLubyte), &indices[0], GL_STATIC_DRAW);

        glBindVertexArray(0);
    }

    Cylinder::~Cylinder()
    {
        // Se liberan los VBOs y el VAO usados:

        glDeleteVertexArrays(1, &vao_id);
        glDeleteBuffers(VBO_COUNT, vbo_ids);
    }

    void Cylinder::createVertices(std::vector< GLfloat >& coordinates, std::vector< GLfloat >& normals, std::vector< GLfloat >& tx)
    {
        // draws a cylinder 'height' high on the y axis at x,y,z position
        const float theta = PI2 / (float)sides;
        float c = cos(theta);
        float s = sin(theta);

        // coordinates on top of the circle, on xz plane
        float x2 = radius, z2 = 0;
        float x = 0;
        float y = 0;
        float z = 0;


        for (int i = 0; i < sides; i++) {

            // texture coord
            const float texture_x = (float)i / sides;
            // normal
            const float nf = 1. / sqrtf(x2 * x2 + z2 * z2), xn = x2 * nf, zn = z2 * nf;

            // Cara de abajo
            normals.push_back(xn);
            normals.push_back(0);
            normals.push_back(zn);

            tx.push_back(texture_x);
            tx.push_back(0);

            coordinates.push_back(x + x2);
            coordinates.push_back(y);
            coordinates.push_back(z + z2);

            //Cara de arriba
            normals.push_back(xn);
            normals.push_back(0);
            normals.push_back(zn);

            tx.push_back(texture_x);
            tx.push_back(1);

            coordinates.push_back(x + x2);
            coordinates.push_back(y + height);
            coordinates.push_back(z + z2);

            // next position
            const float x3 = x2;
            x2 = c * x2 - s * z2;
            z2 = s * x3 + c * z2;
        }

    }

    void Cylinder::createIndices(std::vector< GLfloat >& coordinates)
    {

        int numVerticesAnillo = (coordinates.size()) / 3;

        int i = 0;

        for (i = 0; i < numVerticesAnillo - 2; i += 2)
        {

            indices.push_back(i);
            indices.push_back(i + 1);
            indices.push_back(i + 3);

            indices.push_back(i + 3);
            indices.push_back(i + 2);
            indices.push_back(i);


        }

        //Ultimo vertice

        indices.push_back(i);
        indices.push_back(i + 1);
        indices.push_back(1);

        indices.push_back(1);
        indices.push_back(0);
        indices.push_back(i);
    }

    void Cylinder::createColors(std::vector< GLfloat >& colors, std::vector< GLfloat >& coordinates)
    {
        colors.resize(coordinates.size());

        for (size_t i = 0; i < colors.size(); i += 3)
        {
            colors[i] = (0.5f);
            colors[i + 1] = (0.25f);
            colors[i + 2] = (1);
        }
    }

    void Cylinder::render()
    {
        // Se selecciona el VAO que contiene los datos del objeto y se dibujan sus elementos:

        glBindVertexArray(vao_id);
        glDrawElements(GL_TRIANGLES, indices.size() * sizeof(GLubyte), GL_UNSIGNED_BYTE, 0);
        glBindVertexArray(0);
    }

}
