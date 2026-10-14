#include "bmp_image.hpp"
#include <fstream>
#include <iostream>

const std::uint16_t kBmpSignature = 0x4D42;

bool BmpImage::load(const std::string& path) {
    std::ifstream in(path, std::ios::binary);
    if (!in.is_open()) {
        std::cerr << "Error: cannot open file " << path << "\n";
        return false;
    }

    BmpFileHeader file_header;
    BmpInfoHeader info_header;

    in.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));
    in.read(reinterpret_cast<char*>(&info_header), sizeof(info_header));

    if (!in) {
        std::cerr << "Error: " << path << " is too short to be a BMP file\n";
        return false;
    }

    if (file_header.type != kBmpSignature) {
        std::cerr << "Error: " << path << " is not a BMP file\n";
        return false;
    }

    if (info_header.bits_per_pixel != 24 || info_header.compression != 0) {
        std::cerr << "Error: " << path << " must be a 24-bit BMP without compression\n";
        return false;
    }

    if (info_header.width <= 0 || info_header.height <= 0) {
        std::cerr << "Error: " << path << " has upsupported size\n";
        return false;
    }

    width = info_header.width;
    height = info_header.height;
    pixels.resize(width * height);

    int padding = (4 - (width * 3) % 4) % 4;
    in.seekg(file_header.pixel_offset);

    for (int row = 0; row < height; ++row) {
        int y = height - 1 - row;
        in.read(reinterpret_cast<char*>(&pixels[y * width]), width * 3);
        in.ignore(padding);  // пропускаем байты выравнивания
    }

    if (!in) {
        std::cerr << "Error: " << path << " is damaged (not enough pixel data)\n";
        return false;
    }

    return true;
}

bool BmpImage::save(const std::string& path) const {
    std::ofstream out(path, std::ios::binary);
    if (!out.is_open()) {
        std::cerr << "Error: cannot create file " << path << "\n";
        return false;
    }

    int padding = (4 - (width * 3) % 4) % 4;
    int row_size = width * 3 + padding;

    BmpFileHeader file_header{};
    file_header.type = 0x4D42;
    file_header.pixel_offset = sizeof(BmpFileHeader) + sizeof(BmpInfoHeader);
    file_header.file_size = file_header.pixel_offset + row_size * height;

    BmpInfoHeader info_header{};
    info_header.header_size = sizeof(BmpInfoHeader);
    info_header.width = width;
    info_header.height = height;
    info_header.planes = 1;
    info_header.bits_per_pixel = 24;
    info_header.image_size = row_size * height;

    out.write(reinterpret_cast<const char*>(&file_header), sizeof(file_header));
    out.write(reinterpret_cast<const char*>(&info_header), sizeof(info_header));

    const char zeros[3] = {0, 0, 0};
    for (int row = 0; row < height; ++row) {
        int y = height - 1 - row;
        out.write(reinterpret_cast<const char*>(&pixels[y * width]), width * 3);
        out.write(zeros, padding);
    }
}
