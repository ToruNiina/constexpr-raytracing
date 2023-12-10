#include <array>
#include <string_view>

#include <iostream>
#include <fstream>

#include <cstdint>

#include "math.hpp"
#include "vector.hpp"

#include "camera.hpp"
#include "color.hpp"
#include "random.hpp"
#include "ray.hpp"
#include "world.hpp"

#define STRINGIZE(x) STRINGIZE_AUX(x)
#define STRINGIZE_AUX(x) #x

#include "config.hpp"

namespace conray
{

template<std::size_t N>
constexpr std::pair<color, xorshift64>
ray_color(const ray& r, const world<N>& w, const xorshift64 rng, const std::size_t depth)
{
    if(depth > RAYTRACE_RECURSION_LIMIT)
    {
        return std::make_pair(color{0, 0, 0}, rng);
    }
    if(const auto hit = collides(r, w, 0.001, std::numeric_limits<double>::max()))
    {
        const auto& [collision, obj] = *hit;

        const auto [nray, nrng] = std::visit([&r, &collision, rng](const auto& mat) {
                return scatter(r, collision, mat, rng);
            }, obj.material);

        const auto [c, nrng2] = ray_color(nray, w, nrng, depth + 1);
        return std::make_pair(c * obj.attenuation, nrng2);
    }
    const double a = 0.5 * (r.direction.y + 1.0);
    const color bg = (1.0 - a) * color{1.0, 1.0, 1.0} + a * color{0.5, 0.7, 1.0};
    return std::make_pair(bg, rng);
}

template<std::size_t N>
constexpr std::array<pixel, IMAGE_SIZE_X * IMAGE_SIZE_Y>
make_image(const camera& cam, const world<N>& w)
{
    xorshift64 rng(1234567890);
    std::array<pixel, IMAGE_SIZE_X * IMAGE_SIZE_Y> image;

    for(std::size_t y=0; y<IMAGE_SIZE_Y; ++y)
    {
        const std::size_t offset = IMAGE_SIZE_X * y;

        const auto v_offset = cam.pixel_width_v * (y+0.5);
        const auto pixel_v_coord = cam.viewport_upper_left + v_offset;
        for(std::size_t x=0; x<IMAGE_SIZE_X; ++x)
        {
            const auto u_offset = cam.pixel_width_u * (x+0.5);
            const auto target_pixel = pixel_v_coord + u_offset;

            // anti-alias by using 2x2 = 4 points
            const auto pixel_upper_left = pixel_v_coord + u_offset;
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
                    const auto [c, nrng] = ray_color(r, w, rng, 0);
                    col += c;
                    rng = nrng;
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
    for(std::size_t i=0; i<header_size; ++i)
    {
        retval[i] = static_cast<std::uint8_t>(header_string[i]);
    }
    std::size_t idx = header_size;
    for(std::size_t pxl=0; pxl<IMAGE_SIZE_Y * IMAGE_SIZE_X; ++pxl)
    {
        const auto [r, g, b] = image[pxl];
        retval[idx++] = r;
        retval[idx++] = g;
        retval[idx++] = b;
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
