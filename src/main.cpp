#include <iostream>

#include <bmp_image.hpp>
#include <watermark.hpp>

int main(int argc, char* argv[]) {
    BmpImage original;
    BmpImage watermark;
    BmpImage result;

    original.load(argv[1]);
    watermark.load(argv[2]);
    result.save(argv[3]);

    std::cout << "Done.\n";
}
