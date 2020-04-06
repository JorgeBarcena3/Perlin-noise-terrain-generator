
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on april of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "../header/View.hpp"
#include <iostream>
#include <cassert>
#include "../header/Vertex_Shader.hpp"
#include "../header/Fragment_Shader.hpp"
#include "../header/exampleShapes/Cylinder.hpp"
#include "../header/exampleShapes/Malla.hpp"
#include <glm/gtc/matrix_transform.hpp>         // translate, rotate, scale, perspective
#include <glm/gtc/type_ptr.hpp>                 // value_ptr

#define PI 3.1415f

namespace exampleShapes
{

    using namespace std;

    View::View(int width, int height)
    {

        resize(width, height);

        //shapes.push_back(new Cylinder(2, 3, 20));
        shapes.push_back(new Malla(10, 2));

        //glEnable     (GL_CULL_FACE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glClearColor(0.f, 0.f, 0.f, 1.f);

        // Se compilan y se activan los shaders:

        shaderProgram.attach(Vertex_Shader(Shader::Source_Code::from_file("../../assets/vertexShader.vglsl")));
        shaderProgram.attach(Fragment_Shader(Shader::Source_Code::from_file("../../assets/fragmentShader.fglsl")));

        shaderProgram.link();
        shaderProgram.use();

        projection_matrix = glm::perspective(20.f, GLfloat(width) / height, 1.f, 50.f);
        projection_view_matrix_id = shaderProgram.get_uniform_id("projection_view_matrix");

    }

    void View::update(float time)
    {

    }

    void View::render()
    {

        static float angle = 0;
        angle += 0.8f;

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.f);

        //Se renderizan las shapes
        for (auto shape : shapes)
        {
            // Se rota el cubo y se empuja hacia el fondo:

            glm::mat4 model_view_matrix;

            model_view_matrix = glm::translate(model_view_matrix, glm::vec3(-3, 0, -30.f));
            model_view_matrix = glm::rotate(model_view_matrix, PI, glm::vec3(6.f, 0.f, 0.f));

            glm::mat4 projection_view_matrix = projection_matrix * model_view_matrix;
            glUniformMatrix4fv(projection_view_matrix_id, 1, GL_FALSE, glm::value_ptr(projection_view_matrix));

            shape->render();

        }

    }

    void View::resize(int width, int height)
    {
        // Se establece la configuración básica:
        projection_matrix = glm::perspective(20.f, GLfloat(width) / height, 1.f, 50.f);
        glViewport(0, 0, width, height);
    }

    bool View::uploadUniformVariable(const char* name, float value)
    {
        GLint id = shaderProgram.get_uniform_id(name);

        if (id != -1)
        {
            shaderProgram.set_uniform_value(id, value);
            return true;

        }

        return false;
    }

    bool View::uploadUniformVariable(const char* name, Vector3f value)
    {
        GLint id = shaderProgram.get_uniform_id(name);

        if (id != -1)
        {
            shaderProgram.set_uniform_value(id, value);
            return true;
        }

        return false;
    }

}
