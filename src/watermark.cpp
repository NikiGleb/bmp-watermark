#include <cmath>

#include <watermark.hpp>

const double kAlpha = 0.5;

uint8_t mix(uint8_t a, uint8_t b) {
    double value = a * (1.0 - kAlpha) + b * kAlpha;

    return static_cast<uint8_t>(std::round(value));
}

Pixel blend_pixels(const Pixel& original, const Pixel& watermark) {
    Pixel result;

    result.red = mix(original.red, watermark.red);
    result.green = mix(original.green, watermark.green);
    result.blue = mix(original.blue, watermark.blue);

    return result;
}

bool is_white(const Pixel& pixel) {
    return pixel.red == 255 && pixel.green == 255 && pixel.blue == 255;
}

void pass_watermark_border(const BmpImage& watermark, int& x, int y, int step) {
    while (x >= 0 && x < watermark.width && is_white(watermark.at(x, y))) {
        x += step;
    }
}

BmpImage apply_watermark(const BmpImage& original, const BmpImage& watermark) {
    BmpImage result = original;

    const int translocation_x = original.width - watermark.width;
    const int translocation_y = original.height - watermark.height;

    for (int y = 0; y < watermark.height; y++) {
        int first_x = 0;
        pass_watermark_border(watermark, first_x, y, 1);

        int last_x = watermark.width - 1;
        pass_watermark_border(watermark, last_x, y, -1);
        
        for (int x = first_x; x <= last_x; x++) {
            Pixel& pixel = result.at(translocation_x + x, translocation_y + y);
            pixel = blend_pixels(pixel, watermark.at(x, y));
        }
    }

    return result;
}