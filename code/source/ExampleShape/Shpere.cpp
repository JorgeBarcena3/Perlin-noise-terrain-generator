
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
#include "../../header/exampleShapes/Sphere.hpp"
#include <SFML/OpenGL.hpp>
#include <cmath>
#include <glm/vec3.hpp>

#define PI2 2.0 * 3.141592

namespace exampleShapes
{
    // Constantes locales para representar PI a falta de una definición propicia
    // en <cmath> o una librería más completa:

    static const float pi = 3.1415926536f;
    static const float pi_x_2 = 6.2831853072f;

    Sphere::Sphere(float radius, int number_of_bands, int number_of_slices)
    {
        features.radius = radius;
        features.number_of_bands = number_of_bands < 2 ? 2 : number_of_bands;
        features.number_of_slices = number_of_slices < 2 ? 2 : number_of_slices;

        cache_geometry();
    }

    void Sphere::render()
    {
        // Se dibujan los dos triangle fans que forman las tapas de los polos:

        for (Index_Buffer_Set::const_iterator cap = caps.begin(); cap != caps.end(); ++cap)
        {
            glBegin(GL_TRIANGLE_FAN);
            {
                for (Index_Buffer::const_iterator vertex_index = cap->begin(); vertex_index != cap->end(); ++vertex_index)
                {
                    glNormal3fv(normals[*vertex_index].values);
                    glVertex3fv(vertices[*vertex_index].values);
                }
            }
            glEnd();
        }

        // Se dibujan los triangle strips de todas las bandas:

        for (Index_Buffer_Set::const_iterator band = bands.begin(); band != bands.end(); ++band)
        {
            glBegin(GL_TRIANGLE_STRIP);
            {
                for (Index_Buffer::const_iterator vertex_index = band->begin(); vertex_index != band->end(); ++vertex_index)
                {
                    glNormal3fv(normals[*vertex_index].values);
                    glVertex3fv(vertices[*vertex_index].values);
                }
            }
            glEnd();
        }
    }

    void Sphere::cache_geometry()
    {
        // Se cachea el vértice de un polo:

        cache_point(0.f, 0.f);

        // Se cachean los vértices de los anilos paralelos al ecuador que forman las bandas:

        float delta = pi / features.number_of_bands;
        float beta = delta;

        for (int index = 0, end = features.number_of_bands - 1; index < end; index++, beta += delta)
        {
            cache_ring(beta);
        }

        // Se cachea el vértice del otro polo:

        cache_point(0.f, pi);

        // Se cachean las normales unitarias (a partir del centro, los vértices y el radio):

        cache_normals();

        // Se reserva memoria para los bufers de índices:

        caps.reserve(2);
        bands.reserve(features.number_of_bands);

        // Se teje la tapa de uno de los polos con un triangle fan:

        weave_cap(0, 1, +1);

        // Se tejen todas las bandas (cada banda tiene su propio triangle strip):

        int band_a_start_index = 1;
        int band_b_start_index = 1 + features.number_of_slices;

        for (int band_index = 0, end = features.number_of_bands - 2; band_index < end; band_index++)
        {
            weave_band(band_a_start_index, band_b_start_index);

            band_a_start_index += features.number_of_slices;
            band_b_start_index += features.number_of_slices;
        }

        // Se teje la tapa del otro polo con un triangle fan:

        weave_cap(vertices.size() - 1, vertices.size() - features.number_of_slices - 1, -1);
    }

    void Sphere::cache_point(const float alpha, const float beta)
    {
        // Se calculan y se guardan las coordenadas cartesianas (x,y,z) de un vértice
        // a partir de sus coordenadas polares (alpha,beta,radius):

        const float radius_sin_beta = features.radius * std::sinf(beta);
        const float radius_cos_beta = features.radius * std::cosf(beta);

        vertices.push_back
        (
            Coordinates
            (
                radius_sin_beta * std::cosf(alpha),
                radius_sin_beta * std::sinf(alpha),
                radius_cos_beta
            )
        );
    }

    void Sphere::cache_ring(const float beta)
    {
        // Se calculan los puntos de un anillo paralelo al ecuador modificando
        // sólo uno de los ángulos:

        float alpha = 0.f;
        float delta = pi_x_2 / features.number_of_slices;

        for (int index = 0, end = features.number_of_slices; index < end; index++, alpha += delta)
        {
            cache_point(alpha, beta);
        }
    }

    void Sphere::cache_normals()
    {
        // Las normales unitarias de una esfera son fáciles de calcular: (punto - centro) / radio

        normals.resize(vertices.size());

        Coordinates_Buffer::iterator normal = normals.begin();

        const float divisor = 1.f / features.radius;

        for (Coordinates_Buffer::const_iterator vertex = vertices.begin(); vertex != vertices.end(); ++vertex, ++normal)
        {
            normal->values[0] = vertex->values[0] * divisor;
            normal->values[1] = vertex->values[1] * divisor;
            normal->values[2] = vertex->values[2] * divisor;
        }
    }

    void Sphere::weave_cap(int tip_index, int ring_start_index, int step)
    {
        caps.push_back(Index_Buffer());

        Index_Buffer& cap = caps.back();

        // Uno de los polos se teje en sentido horario y el otro al revés para
        // que los triángulos sean siempre front faces:

        int ring_end_index = ring_start_index + features.number_of_slices;

        if (step < 0)
        {
            std::swap(--ring_start_index, --ring_end_index);
        }

        // Se añade el punto origen del triangle fan:

        cap.push_back(tip_index);

        // Se guardan los índices del anillo más cercano al polo:

        for (int ring_vertex_index = ring_start_index; ring_vertex_index != ring_end_index; ring_vertex_index += step)
        {
            cap.push_back(ring_vertex_index);
        }

        // Se cierra el anilo:

        cap.push_back(ring_start_index);
    }

    void Sphere::weave_band(int band_a_start_index, int band_b_start_index)
    {
        bands.push_back(Index_Buffer());

        Index_Buffer& band = bands.back();

        // Se van añadiendo los índices de vértices del anillo superior e inferiror a pares:

        int band_a_index = band_a_start_index;
        int band_b_index = band_b_start_index;

        while (band_a_index < band_b_start_index)
        {
            band.push_back(band_a_index++);
            band.push_back(band_b_index++);
        }

        // Se cierra la banda:

        band.push_back(band_a_start_index);
        band.push_back(band_b_start_index);
    }
}
