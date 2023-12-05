#include <array>
#include <string_view>

#include <iostream>
#include <fstream>

#include <cstdint>

// compile-time arguments

#ifndef IMAGE_SIZE_X
#  define IMAGE_SIZE_X 640
#endif

#ifndef IMAGE_SIZE_Y
#  define IMAGE_SIZE_Y 480
#endif

// code

#define STRINGIZE(x) STRINGIZE_AUX(x)
#define STRINGIZE_AUX(x) #x

struct color
{
    std::uint8_t r;
    std::uint8_t g;
    std::uint8_t b;
};

constexpr std::array<color, IMAGE_SIZE_X * IMAGE_SIZE_Y>
make_image()
{
    std::array<color, IMAGE_SIZE_X * IMAGE_SIZE_Y> image;

    for(std::size_t y=0; y<IMAGE_SIZE_Y; ++y)
    {
        const std::size_t offset = IMAGE_SIZE_X * y;
        for(std::size_t x=0; x<IMAGE_SIZE_X; ++x)
        {
            auto& [r, g, b] = image[offset + x];
            r = static_cast<std::uint8_t>(255.999 * x / IMAGE_SIZE_X);
            g = static_cast<std::uint8_t>(255.999 * y / IMAGE_SIZE_Y);
            b = 0;
        }
    }
    return image;
}

constexpr auto
make_ppm(const std::array<color, IMAGE_SIZE_X * IMAGE_SIZE_Y>& image)
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

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        std::cerr << "usage: ray [filename.ppm]" << std::endl;
        return 1;
    }

    constexpr auto ppm = make_ppm(make_image());

    std::ofstream ofs(argv[1]);
    if(!ofs.good())
    {
        std::cerr << "failed to open " << argv[1] << std::endl;
        return 1;
    }

    ofs.write(reinterpret_cast<const char*>(ppm.data()), ppm.size());

    return 0;
}
