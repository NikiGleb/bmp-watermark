#include "bmp_image.hpp"
#include <fstream>

void BmpImage::load(const std::string& path) {
    std::ifstream in(path, std::ios::binary);

    BmpFileHeader file_header;
    BmpInfoHeader info_header;

    in.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));
    in.read(reinterpret_cast<char*>(&info_header), sizeof(info_header));

    width = info_header.width;
    height = info_header.height;
    pixels.resize(width * height);

    int padding = (4 - (width * 3) % 4) % 4;
    in.seekg(file_header.pixel_offset);
    
    for (int row = 0; row < height; ++row) {
        int y = height - 1 - row;
        in.read(reinterpret_cast<char*>(&pixels[y * width]), width * 3);
        in.ignore(padding);   // пропускаем байты выравнивания
    }
}

void BmpImage::save(const std::string& path) const {
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

    std::ofstream out(path, std::ios::binary);
    out.write(reinterpret_cast<const char*>(&file_header), sizeof(file_header));
    out.write(reinterpret_cast<const char*>(&info_header), sizeof(info_header));

    const char zeros[3] = {0, 0, 0};
    for (int row = 0; row < height; ++row) {
        int y = height - 1 - row;   
        out.write(reinterpret_cast<const char*>(&pixels[y * width]), width * 3);
        out.write(zeros, padding);
    }
}
