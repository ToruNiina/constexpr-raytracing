#include <array>
#include <string_view>
#include <format>
#include <iostream>

#include <cstdint>

#define STRINGIZE(x) STRINGIZE_AUX(x)
#define STRINGIZE_AUX(x) #x

// compile-time argument
#define IMAGE_SIZE_X 640
#define IMAGE_SIZE_Y 480

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

constexpr std::array<char, 3>
to_string(std::uint8_t x)
{
    const auto dig0 = (x / 100) % 10;
    const auto dig1 = (x / 10 ) % 10;
    const auto dig2 = (x      ) % 10;

    std::array<char, 3> retval;
    switch(dig0)
    {
        case  0: {retval[0] = ' '; break;}
        case  1: {retval[0] = '1'; break;}
        case  2: {retval[0] = '2'; break;}
        default: {retval[0] = 'x'; break;}
    }
    switch(dig1)
    {
        case  0:
        {
            if(dig0 == 0) {retval[1] = ' ';} else {retval[1] = '0';} break;
        }
        case  1: {retval[1] = '1'; break;}
        case  2: {retval[1] = '2'; break;}
        case  3: {retval[1] = '3'; break;}
        case  4: {retval[1] = '4'; break;}
        case  5: {retval[1] = '5'; break;}
        case  6: {retval[1] = '6'; break;}
        case  7: {retval[1] = '7'; break;}
        case  8: {retval[1] = '8'; break;}
        case  9: {retval[1] = '9'; break;}
        default: {retval[1] = 'x'; break;}
    }
    switch(dig2)
    {
        case  0: {retval[2] = '0'; break;}
        case  1: {retval[2] = '1'; break;}
        case  2: {retval[2] = '2'; break;}
        case  3: {retval[2] = '3'; break;}
        case  4: {retval[2] = '4'; break;}
        case  5: {retval[2] = '5'; break;}
        case  6: {retval[2] = '6'; break;}
        case  7: {retval[2] = '7'; break;}
        case  8: {retval[2] = '8'; break;}
        case  9: {retval[2] = '9'; break;}
        default: {retval[2] = 'x'; break;}
    }
    return retval;
}

constexpr auto
make_ppm(const std::array<color, IMAGE_SIZE_X * IMAGE_SIZE_Y>& image)
{
    constexpr auto header_string =
        "P3\n" STRINGIZE(IMAGE_SIZE_X) " " STRINGIZE(IMAGE_SIZE_Y) "\n255\n";
    constexpr auto header_size = std::string_view(header_string).size();
    constexpr auto pixel_size = 4 + 4 + 4; // {:3d} {:3d} {:3d}\n
    constexpr auto ppm_size = header_size +
        (IMAGE_SIZE_X * IMAGE_SIZE_Y * pixel_size);

    std::array<char, ppm_size> retval;
    retval.back() = '\0';
    auto head = retval.data();

    for(std::size_t i=0; i<header_size; ++i) // -1 for null char
    {
        *head = header_string[i];
        head++;
    }

    for(std::size_t y=0; y<IMAGE_SIZE_Y; ++y)
    {
        const std::size_t offset = IMAGE_SIZE_X * y;

        for(std::size_t x=0; x<IMAGE_SIZE_X; ++x)
        {
            const auto [r, g, b] = image[offset + x];
            const auto rs = to_string(r);
            *head = rs[0]; head++;
            *head = rs[1]; head++;
            *head = rs[2]; head++;
            *head = ' ';   head++;

            const auto gs = to_string(g);
            *head = gs[0]; head++;
            *head = gs[1]; head++;
            *head = gs[2]; head++;
            *head = ' ';   head++;

            const auto bs = to_string(b);
            *head = bs[0]; head++;
            *head = bs[1]; head++;
            *head = bs[2]; head++;
            *head = '\n';  head++;
        }
    }
    return retval;
}

int main()
{
    constexpr auto ppm = make_ppm(make_image());
    std::cout << ppm.data();
    return 0;
}
