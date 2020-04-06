
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Jorge Barcena on March of 2020                                  *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  j.barcenalumbreras@gmail.com                                               *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef MALLA_HEADER
#define MALLA_HEADER

#include <SFML/OpenGL.hpp>
#include <vector>
#include "BaseShape.hpp"

namespace exampleShapes
{

    class Malla : public BaseShape
    {
    private:

        // Índices para indexar el array vbo_ids:

        enum
        {
            COORDINATES_VBO,
            COLORS_VBO,
            NORMALS_VBO,
            INDICES_IBO,
            VBO_COUNT
        };


    private:

        GLuint vbo_ids[VBO_COUNT];      // Ids de los VBOs que se usan
        GLuint vao_id;                  // Id del VAO del cubo

        int grid_size;
        int square_size;
        

        std::vector< GLubyte > indices;
        std::vector< GLfloat > coordinates;


    public:

        Malla(int grid_size, int square_size);
        ~Malla();

        void createVertices(std::vector< GLfloat >& coordinates, std::vector< GLfloat >& normals);
        void createIndices(std::vector< GLfloat >& coordinates);
        void createColors(std::vector< GLfloat >& colors, std::vector< GLfloat >& coodinates);

        void render() override;

    };

}

#endif
