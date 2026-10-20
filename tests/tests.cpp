// Автотесты
// Каждая проверка печатает [OK] или [FAIL]. Если хоть одна не прошла, программа возвращает 1
// Запускать из корня проекта: пути к картинкам относительные

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

bool same_image(const BmpImage& a, const BmpImage& b) {
    if (a.width != b.width || a.height != b.height) {
        return false;
    }

    for (int y = 0; y < a.height; y++) {
        for (int x = 0; x < a.width; x++) {
            if (!same_color(a.at(x, y), b.at(x, y))) {
                return false;
            }
        }
    }

    return true;
}

// Создаём красную картинку 10x10, сохраняем и сравниваем с эталоном, нарисованным в Paint
void test_10_10_red() {
    const Pixel red{0, 0, 255};

    BmpImage testing;
    testing.width = 10;
    testing.height = 10;
    testing.pixels.assign(10 * 10, red);
    const std::string testing_path = "tests/bmps/test1/testing.bmp";
    check(testing.save(testing_path), "10x10 red: image is saved");

    BmpImage loaded;
    check(loaded.load(testing_path), "10x10 red: saved image is loaded back");
    check(same_image(loaded, testing), "10x10 red: loaded image equals saved one");

    BmpImage reference;
    check(reference.load("tests/bmps/test1/10_10_red.bmp"), "10x10 red: reference image is loaded");
    check(same_image(reference, testing), "10x10 red: image equals reference from Paint");
}

// Накладываем чёрный знак 3x3 на белую картинку 10x10 и сравниваем с эталоном из Paint
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

    BmpImage testing = apply_watermark(white_picture, black_watermark);

    BmpImage reference;
    check(reference.load("tests/bmps/test2/test_add_black_square_on_white_picture.bmp"),
          "black square: reference image is loaded");
    check(same_image(reference, testing), "black square: 3x3 square in the corner of white picture");
}

int main() {
    test_10_10_red();
    test_add_black_square_on_white_picture();

    if (failed_tests > 0) {
        std::cout << failed_tests << " check(s) failed\n";
        return 1;
    }

    std::cout << "All checks passed\n";
    return 0;
}
