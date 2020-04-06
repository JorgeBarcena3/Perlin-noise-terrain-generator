
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Jorge Barcena on March of 2020                                  *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  j.barcenalumbreras@gmail.com                                               *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef CYLINDER_HEADER
#define CYLINDER_HEADER

#include <SFML/OpenGL.hpp>
#include <vector>
#include "BaseShape.hpp"

namespace exampleShapes
{

    class Cylinder : public BaseShape
    {
    private:

        // Índices para indexar el array vbo_ids:

        enum
        {
            COORDINATES_VBO,
            COLORS_VBO,
            NORMALS_VBO,
            TEXTURE_VBO,
            INDICES_IBO,
            VBO_COUNT
        };


    private:

        GLuint vbo_ids[VBO_COUNT];      // Ids de los VBOs que se usan
        GLuint vao_id;                  // Id del VAO del cubo

        float radius;
        float height;
        float sides;

        std::vector< GLubyte > indices;


    public:

        Cylinder(float radius, float height, float sides = 18);
        ~Cylinder();

        void createVertices(std::vector< GLfloat >& coordinates, std::vector< GLfloat >& normals, std::vector< GLfloat >& tx);
        void createIndices(std::vector< GLfloat >& coordinates);
        void createColors(std::vector< GLfloat >& colors, std::vector< GLfloat >& coodinates);

        void render() override;

    };

}

#endif
