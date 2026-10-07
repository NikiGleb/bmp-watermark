#pragma once

#include <bmp_image.hpp>

Pixel blend_pixels(const Pixel& original, const Pixel& watermark);

BmpImage apply_watermark(const BmpImage& original, const BmpImage& watermark);