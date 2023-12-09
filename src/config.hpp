#ifndef CONSTEXPR_RAYTRACING_CONFIG_HPP
#define CONSTEXPR_RAYTRACING_CONFIG_HPP

#include "math.hpp"
#include "vector.hpp"

#ifndef IMAGE_SIZE_X
#  define IMAGE_SIZE_X 640
#endif

#ifndef IMAGE_SIZE_Y
#  define IMAGE_SIZE_Y 480
#endif

namespace conray
{

constexpr inline math::vector camera_position{0, 0, 0};

constexpr inline double focal_length    = 1.0;
constexpr inline double viewport_height = 2.0;
constexpr inline double viewport_width  = (viewport_height * IMAGE_SIZE_X) / IMAGE_SIZE_Y;

constexpr inline auto viewport_u = math::vector(viewport_width, 0, 0);
constexpr inline auto viewport_v = math::vector(0, -viewport_height, 0);

constexpr inline auto pixel_width_u = viewport_u / IMAGE_SIZE_X;
constexpr inline auto pixel_width_v = viewport_v / IMAGE_SIZE_Y;

constexpr inline auto screen_center = camera_position - math::vector(0, 0, focal_length);
constexpr inline auto viewport_upper_left = screen_center - viewport_u*0.5 - viewport_v*0.5;

} // conray
#endif // CONSTEXPR_RAYTRACING_CONFIG_HPP
