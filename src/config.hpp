#ifndef CONSTEXPR_RAYTRACING_CONFIG_HPP
#define CONSTEXPR_RAYTRACING_CONFIG_HPP

#include "math.hpp"
#include "vector.hpp"
#include "world.hpp"
#include "camera.hpp"
#include "material.hpp"

#ifndef IMAGE_SIZE_X
#  define IMAGE_SIZE_X 400
#endif

#ifndef IMAGE_SIZE_Y
#  define IMAGE_SIZE_Y 200
#endif

#ifndef RAYTRACE_RECURSION_LIMIT
#  define RAYTRACE_RECURSION_LIMIT 16
#endif

#ifndef SAMPLES_PER_PIXEL_SQRT
#  define SAMPLES_PER_PIXEL_SQRT 2
#endif

namespace conray
{

constexpr inline camera cam(IMAGE_SIZE_X, IMAGE_SIZE_Y,
    /* position        = */ math::vector(0.0, 0.0, 0.0),
    /* focal_length    = */ 1.0,
    /* viewport_height = */ 2.0);

constexpr inline world w = make_world(
        object{
            .attenuation = color{1.0, 1.0, 1.0},
            .material = dielectric{1.5},
            .shape = sphere{math::vector{-1.0,  0.0, -1.0},   0.5}
        },
        object{
            .attenuation = color{1.0, 1.0, 1.0},
            .material = dielectric{1.5},
            .shape = sphere{math::vector{-1.0,  0.0, -1.0},  -0.4}
        },
        object{
            .attenuation = color{0.8, 0.6, 0.2},
            .material = metallic{},
            .shape = sphere{math::vector{1.0,   0.0, -1.0},   0.5}
        },
        object{
            .attenuation = color{0.7, 0.3, 0.3},
            .material = diffusive{},
            .shape = sphere{math::vector{0.0,   0.0, -1.0},   0.5}
        },
        object{
            .attenuation = color{0.8, 0.8, 0.0},
            .material = diffusive{},
            .shape = sphere{math::vector{0.0,-100.5, -1.0}, 100.0}
        }
    );

} // conray
#endif // CONSTEXPR_RAYTRACING_CONFIG_HPP
