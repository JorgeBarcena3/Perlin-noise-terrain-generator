
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on march of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef BASESHAPES_HEADER
#define BASESHAPES_HEADER

#include <memory>
#include <vector>
#include <cmath>
#include <SFML/OpenGL.hpp>

namespace exampleShapes
{

    class BaseShape
    {

    public:
        
        virtual void render() = 0;

    };

}

#endif
