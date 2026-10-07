#include <watermark.hpp>

uint8_t average(uint8_t a, uint8_t b) {
    int sum = static_cast<int>(a) + static_cast<int>(b);
    
    return static_cast<uint8_t>(sum / 2);
}

Pixel blend_pixels(const Pixel& original, const Pixel& mark) {
    Pixel result;

    result.red = average(original.red, mark.red);
    result.green = average(original.green, mark.green);
    result.blue = average(original.blue, mark.blue);

    return result;
}