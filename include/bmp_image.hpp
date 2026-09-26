#pragma once

#include <cstdint>
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

struct Pixel {
    std::uint8_t blue;
    std::uint8_t green;
    std::uint8_t red;
};

#pragma pack(pop)

class BmpImage {
    public:
        int width = 0;
        int height = 0;
        std::vector<Pixel> pixels;   

        void load(const std::string& path);
        void save(const std::string& path) const;

        Pixel& at(int x, int y) { 
            return pixels[y * width + x]; 
        }
        const Pixel& at(int x, int y) const { 
            return pixels[y * width + x]; 
        }
};