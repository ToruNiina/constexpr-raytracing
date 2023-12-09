#include <array>
#include <string_view>

#include <iostream>
#include <fstream>

#include <cstdint>

#include "math.hpp"
#include "vector.hpp"

#include "camera.hpp"
#include "color.hpp"
#include "ray.hpp"
#include "world.hpp"


#define STRINGIZE(x) STRINGIZE_AUX(x)
#define STRINGIZE_AUX(x) #x

#include "config.hpp"

namespace conray
{

template<std::size_t N>
constexpr color ray_color(const ray& r, const world<N>& w)
{
    if(const auto hit = collides(r, w, 0, std::numeric_limits<double>::max()))
    {
        return color {
            .r = 0.5 * (hit->normal.x + 1.0),
            .g = 0.5 * (hit->normal.y + 1.0),
            .b = 0.5 * (hit->normal.z + 1.0),
        };
    }
    const double a = 0.5 * (r.direction.y + 1.0);
    return (1.0 - a) * color{1.0, 1.0, 1.0} + a * color{0.5, 0.7, 1.0};
}

template<std::size_t N>
constexpr std::array<pixel, IMAGE_SIZE_X * IMAGE_SIZE_Y>
make_image(const camera& cam, const world<N>& w)
{
    std::array<pixel, IMAGE_SIZE_X * IMAGE_SIZE_Y> image;

    for(std::size_t y=0; y<IMAGE_SIZE_Y; ++y)
    {
        const std::size_t offset = IMAGE_SIZE_X * y;

        const auto v_offset = cam.pixel_width_v * y;
        const auto pixel_v_coord = cam.viewport_upper_left + v_offset;
        for(std::size_t x=0; x<IMAGE_SIZE_X; ++x)
        {
            const auto u_offset = cam.pixel_width_u * x;
            const auto pixel_upper_left = pixel_v_coord + u_offset;

            // anti-alias by using 2x2 = 4 points
            color col{0.0, 0.0, 0.0};
            for(std::size_t sx=0; sx<2; ++sx)
            {
                for(std::size_t sy=0; sy<2; ++sy)
                {
                    const auto target_pixel = pixel_upper_left +
                        cam.pixel_width_u * sx / 3.0 +
                        cam.pixel_width_v * sy / 3.0 ;
                    const auto ray_direction = math::normalize(target_pixel - cam.position);
                    const auto r = ray{ cam.position, ray_direction };
                    col += ray_color(r, w);
                }
            }
            col *= 0.25;

            image[offset+x] = to_pixel(col);
        }
    }
    return image;
}

constexpr auto
make_ppm(const std::array<pixel, IMAGE_SIZE_X * IMAGE_SIZE_Y>& image)
{
    constexpr auto header_string =
        "P6\n" STRINGIZE(IMAGE_SIZE_X) " " STRINGIZE(IMAGE_SIZE_Y) "\n255\n";
    constexpr auto header_size = std::string_view(header_string).size();
    constexpr auto pixel_size = 3; // [byte]
    constexpr auto ppm_size = header_size +
        (IMAGE_SIZE_X * IMAGE_SIZE_Y * pixel_size);

    std::array<std::uint8_t, ppm_size> retval;
    for(std::size_t i=0; i<header_size; ++i) // -1 for null char
    {
        retval[i] = static_cast<std::uint8_t>(header_string[i]);
    }
    std::size_t idx = header_size;
    for(std::size_t y=0; y<IMAGE_SIZE_Y; ++y)
    {
        const std::size_t offset = IMAGE_SIZE_X * y;
        for(std::size_t x=0; x<IMAGE_SIZE_X; ++x)
        {
            const auto [r, g, b] = image[offset + x];
            retval[idx] = r; idx++;
            retval[idx] = g; idx++;
            retval[idx] = b; idx++;
        }
    }
    return retval;
}
} // conray

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        std::cerr << "usage: ray [filename.ppm]" << std::endl;
        return 1;
    }

    constexpr auto ppm = conray::make_ppm(conray::make_image(conray::cam, conray::w));

    std::ofstream ofs(argv[1]);
    if(!ofs.good())
    {
        std::cerr << "failed to open " << argv[1] << std::endl;
        return 1;
    }

    ofs.write(reinterpret_cast<const char*>(ppm.data()), ppm.size());

    return 0;
}
