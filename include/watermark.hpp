#pragma once

#include <bmp_image.hpp>

// Смешивает два пикселя по каждому каналу (R, G, B) с непрозрачностью kAlpha:
// new = original * (1 - kAlpha) + watermark * kAlpha.
Pixel blend_pixels(const Pixel& original, const Pixel& watermark);

// Алгоритм наложения водяного знака на исходное изображение
BmpImage apply_watermark(const BmpImage& original, const BmpImage& watermark);