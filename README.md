# BMP Watermark

Проект на C++, разработанный для наложения водяного знака на изображение в формате BMP.

Учебный проект по дисциплине «Инструментальные средства разработки ПО», ИТМО.

## Технологии

- CMake — сборка;
- Git и GitHub — контроль версий;
- GitHub Actions — автоматическая сборка и запуск тестов.


## Сборка

Требуется компилятор с поддержкой C++17 и CMake 3.10 или новее.

```bash
cmake -S . -B build
cmake --build build
```

Собираются две программы: `build/watermark` и `build/watermark_tests`.

## Запуск

```bash
./build/watermark <image.bmp> <watermark.bmp> <output.bmp>
```

- `image.bmp` — исходное изображение;
- `watermark.bmp` — водяной знак, не больше исходного изображения;
- `output.bmp` — куда сохранить результат.

Пример:

```bash
./build/watermark photo.bmp logo.bmp result.bmp
```