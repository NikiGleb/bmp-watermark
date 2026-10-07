#include <watermark.hpp>

uint8_t average(uint8_t a, uint8_t b) {
    int sum = static_cast<int>(a) + static_cast<int>(b);

    return static_cast<uint8_t>(sum / 2);
}

Pixel blend_pixels(const Pixel& original, const Pixel& watermark) {
    Pixel result;

    result.red = average(original.red, watermark.red);
    result.green = average(original.green, watermark.green);
    result.blue = average(original.blue, watermark.blue);

    return result;
}

BmpImage apply_watermark(const BmpImage& original, const BmpImage& watermark) {
    BmpImage result = original;

    for (int y = 0; y < original.height; y++) {
        for (int x = 0; x < original.width; x++) {
            Pixel mixed = blend_pixels(original.at(x, y), watermark.at(x, y));
        }
    }

    return result;
}