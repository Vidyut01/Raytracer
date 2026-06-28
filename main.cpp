#include "color.h"
#include "vector3.h"

#include <iostream>

int main(int argc, char const *argv[])
{
    int height = 256;
    int width = 256;

    std::cout << "P3\n" << width << ' ' << height << "\n255\n";
    
    for (int j = 0; j < height; ++j) {
        std::clog << "\rScanlines remaining: " << (height - j) << ' ' << std::flush;
        for (int i = 0; i < width; ++i) {
            auto px_color = color((float)i / (width - 1), 0.0, (float)j / (height - 1));
            write_color(std::cout, px_color);
        }
    }
    std::clog << "\rDone.                 \n";

    return 0;
}
