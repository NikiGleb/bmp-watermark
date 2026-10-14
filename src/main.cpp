#include <iostream>

#include <bmp_image.hpp>
#include <watermark.hpp>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <image.bmp> <watermark.bmp> <output.bmp>\n";
        return 1;
    }

    BmpImage original;
    BmpImage watermark;
    BmpImage result;

    if (!original.load(argv[1])) {
        return 1;
    }

    if (!watermark.load(argv[2])) {
        return 1;
    }

    if (watermark.width > original.width || watermark.height > original.height) {
        std::cout << "Watermark is bigger than image\n";
    }

    result = apply_watermark(original, watermark);
    if (!result.save(argv[3])) {
        return 1;
    }

    std::cout << "Done.\n";
    return 0;
}
