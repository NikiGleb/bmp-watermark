#pragma once

#include <cstdint>
#include <string>
#include <vector>

// #pragma pack(push, 1) запрещает компилятору вставлять пустые байты между полями
#pragma pack(push, 1)

// Заголовок файла (BITMAPFILEHEADER), 14 байт
struct BmpFileHeader {
    std::uint16_t type;          // сигнатура "BM" (число 0x4D42)
    std::uint32_t file_size;     // размер всего файла в байтах
    std::uint16_t reserved1;     // не используется в рамках данного проекта
    std::uint16_t reserved2;     // не используется в рамках данного проекта
    std::uint32_t pixel_offset;  // с какого байта начинаются пиксели 
};

// Информационный заголовок (BITMAPINFOHEADER), 40 байт
struct BmpInfoHeader {
    std::uint32_t header_size;        // размер заголовка
    std::int32_t width;               // ширина в пикселях
    std::int32_t height;              // высота; в рамках данного проекта > 0 — строки в файле идут снизу вверх
    std::uint16_t planes;             // в рамках данного проекта всегда 1
    std::uint16_t bits_per_pixel;     // бит на пиксель, в рамках данного проекта 24
    std::uint32_t compression;        // в рамках данного проекта 0 — без сжатия
    std::uint32_t image_size;         // размер пиксельных данных в байтах
    std::int32_t x_pixels_per_meter;  // разрешение, в рамках данного проекта не используется
    std::int32_t y_pixels_per_meter;  // разрешение, в рамках данного проекта не используется
    std::uint32_t colors_used;        // в рамках данного проекта 0
    std::uint32_t colors_important;   // в рамках данного проекта 0 
};

struct Pixel {
    std::uint8_t blue;
    std::uint8_t green;
    std::uint8_t red;
};

#pragma pack(pop)

// Проверки на этапе компиляции: размеры совпадают со спецификацией BM
static_assert(sizeof(BmpFileHeader) == 14, "BmpFileHeader must be 14 bytes");
static_assert(sizeof(BmpInfoHeader) == 40, "BmpInfoHeader must be 40 bytes");
static_assert(sizeof(Pixel) == 3, "Pixel must be 3 bytes");

class BmpImage {
    public:
        int width = 0;
        int height = 0;
        std::vector<Pixel> pixels;   

        bool load(const std::string& path);
        bool save(const std::string& path) const;

        // Возвращает ссылку на пиксель (x,y)
        Pixel& at(int x, int y) { 
            return pixels[y * width + x]; 
        }
        const Pixel& at(int x, int y) const { 
            return pixels[y * width + x]; 
        }
};