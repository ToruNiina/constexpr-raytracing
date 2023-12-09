#ifndef CONSTEXPR_RAYTRACING_CAMERA_HPP
#define CONSTEXPR_RAYTRACING_CAMERA_HPP

#include "collision.hpp"
#include "sphere.hpp"
#include "world.hpp"

namespace conray
{

struct camera
{
    constexpr camera(
        const std::size_t image_size_x, const std::size_t image_size_y,
        const math::vector p, const double f, const double vh)
        : position(p),
          focal_length(f),
          viewport_height(vh),
          viewport_width((viewport_height * image_size_x) / image_size_y),
          viewport_u{viewport_width, 0.0, 0.0},
          viewport_v{0.0, -viewport_height, 0.0},
          pixel_width_u(viewport_u / image_size_x),
          pixel_width_v(viewport_v / image_size_y),
          screen_center(position - math::vector{0, 0, focal_length}),
          viewport_upper_left(screen_center - viewport_u * 0.5 - viewport_v * 0.5)
    {}

    math::vector position;
    double       focal_length;
    double       viewport_height;
    double       viewport_width;
    math::vector viewport_u;
    math::vector viewport_v;
    math::vector pixel_width_u;
    math::vector pixel_width_v;

    math::vector screen_center;
    math::vector viewport_upper_left;
};

} // conray
#endif//CONSTEXPR_RAYTRACING_WORLD_HPP

