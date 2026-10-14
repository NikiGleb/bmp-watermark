#include <iostream>
#include <string>

#include "bmp_image.hpp"
#include "watermark.hpp"

int failed_tests = 0;

void check(bool condition, const std::string name) {
    if (condition) {
        std::cout << "[OK] " << name << "\n";
    }
    else {
        std::cout << "[FAIL] " << name << "\n";
        failed_tests++;
    }
}

bool same_color(const Pixel p1, const Pixel p2) {
    return p1.red == p2.red && p1.blue == p2.blue && p1.green == p2.green;
}

void test_10_10_red() {
    const Pixel red{0, 0, 255};

    BmpImage testing;
    testing.width = 10;
    testing.height = 10;
    testing.pixels.assign(10 * 10, red);
    const std::string testing_path = "tests/bmps/test1/testing.bmp";
    testing.save(testing_path);

    BmpImage test;
    const std::string test_path = "tests/bmps/test1/10_10_red.bmp";
    test.load(test_path);

    bool same_size = test.width == testing.width && test.height == testing.height;
    check(same_size, "10x10 red: sizes are equal");

    bool same_pixels = true;
    for (int y = 0; y < test.height; y++) {
        for (int x = 0; x < test.width; x++) {
            if (!same_color(test.at(x, y), testing.at(x, y))) {
                same_pixels = false;
            }
        }
    }

    check(same_pixels, "10x10 red: all pixels are equal");
}

void test_add_black_square_on_white_picture() {
    const Pixel white{255, 255, 255};
    const Pixel black{0, 0, 0};

    BmpImage white_picture;
    white_picture.width = 10;
    white_picture.height = 10;
    white_picture.pixels.assign(white_picture.height * white_picture.width, white);

    BmpImage black_watermark;
    black_watermark.width = 3;
    black_watermark.height = 3;
    black_watermark.pixels.assign(black_watermark.height * black_watermark.width, black);

    BmpImage testing;
    testing = apply_watermark(white_picture, black_watermark);

    BmpImage test;
    const std::string test_path = "tests/bmps/test2/test_add_black_square_on_white_picture.bmp";
    test.load(test_path);

    bool same_pixels = true;
    for (int y = 0; y < test.height; y++) {
        for (int x = 0; x < test.width; x++) {        
            if (!same_color(test.at(x, y), testing.at(x, y))) {
                same_pixels = false;
            }
        }
    }

    check(same_pixels, "add black square on white picture: black square 3x3 on corner of white picture");
}

int main() {
    test_10_10_red();
    test_add_black_square_on_white_picture();

    if(failed_tests>0){
        std::cout << failed_tests << " check(s) failed\n";
        return 1;
    }

    std::cout << "All checks passed\n";
    return 0;
}
