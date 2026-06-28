#include <iostream>

int main(int argc, char const *argv[])
{
    int height = 256;
    int width = 256;

    std::cout << "P3\n" << width << ' ' << height << "\n255\n";
    
    for (int j = 0; j < height; ++j) {
        std::clog << "\rScanlines remaining: " << (height - j) << ' ' << std::flush;
        for (int i = 0; i < width; ++i) {
            auto r = (double)i / (width - 1);
            auto g = (double)j / (height - 1);
            auto b = 0.0;
            
            int ir = 255.999 * r;
            int ig = 255.999 * g;
            int ib = 255.999 * b;

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    std::clog << "\rDone.                 \n";

    return 0;
}
