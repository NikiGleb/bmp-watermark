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
        for (int x = 0; x < test.width; x++){
            if(!same_color(test.at(x,y), testing.at(x,y))){
                same_pixels = false;
            }
        }
    }

    check(same_pixels, "10x10 red: all pixels are equal");
}

int main() {
    test_10_10_red();
}
