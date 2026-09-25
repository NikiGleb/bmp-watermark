#pragma once

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

#pragma pack(push, 1)

struct BmpFileHeader {
    std::uint16_t type;
    std::uint32_t file_size;   
    std::uint16_t reserved1;     
    std::uint16_t reserved2;     
    std::uint32_t pixel_offset;
};


struct BmpInfoHeader {
    std::uint32_t header_size;       
    std::int32_t width;             
    std::int32_t height;             
    std::uint16_t planes;            
    std::uint16_t bits_per_pixel;    
    std::uint32_t compression;       
    std::uint32_t image_size;        
    std::int32_t x_pixels_per_meter; 
    std::int32_t y_pixels_per_meter; 
    std::uint32_t colors_used;       
    std::uint32_t colors_important; 
};

#pragma pack(pop)

struct Pixel {
    std::uint8_t blue = 0;
    std::uint8_t green = 0;
    std::uint8_t red = 0;

    bool operator==(const Pixel& other) const {
        return blue == other.blue && green == other.green && red == other.red;
    }

    bool operator!=(const Pixel& other) const {
        return !(*this == other);
    }
};

constexpr Pixel rgb(std::uint8_t red, std::uint8_t green, std::uint8_t blue) {
    return Pixel{blue, green, red};
}

class BmpImage {
    public:
        BmpImage() = default;
        BmpImage(int width, int height, Pixel fill = Pixel{});

        void load(const std::string& path);
        void save(const std::string& path) const;

        int width() const { return width_; }
        int height() const { return height_; }
        int bit_depth() const { return 24; }
        bool empty() const { return pixels_.empty(); }

        Pixel& at(int x, int y);
        const Pixel& at(int x, int y) const;

        static std::size_t row_stride(int width);

    private:
        std::size_t index_of(int x, int y) const;

        int width_ = 0;
        int height_ = 0;
        std::vector<Pixel> pixels_;
};