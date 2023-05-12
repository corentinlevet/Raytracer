/*
** EPITECH PROJECT, 2022
** PPMtoPNG.cpp
** File description:
** File containing the PPMtoPNG class
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <png.h>

class PPMtoPNG {
    public:
        PPMtoPNG() = default;
        ~PPMtoPNG() = default;
        void convert(std::string &path, std::string &toWrite);
        void createPNG(int width, int height, std::string &filename, std::vector<int> &imageData, std::string &toWrite);
};

void PPMtoPNG::convert(std::string &path, std::string &toWrite)
{
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Error: File not found" << std::endl;
        return;
    }

    constexpr auto fileHeader = "P3";
    std::string line;
    file >> line;
    if (line != fileHeader) {
        std::cerr << "Error: Failed to read \"" << path << "\" bad file header" << std::endl;
        return;
    }

    int width = 0;
    int height = 0;
    file >> width >> height;
    if (width <= 0 || height <= 0) {
        std::cerr << "Error: Failed to read \"" << path << "\" bad width or height" << std::endl;
        return;
    }

    int bpp = 0;
    file >> bpp;
    if (bpp <= 0 || bpp > 255) {
        std::cerr << "Error: Failed to read \"" << path << "\" bad bpp" << std::endl;
        return;
    }

    constexpr auto BPP = 3;
    const std::size_t imageSize = static_cast<std::size_t>(width * height * BPP);

    std::vector<int> imageData(imageSize);

    std::size_t row = 0;
    std::string r, g, b;
    for (row = 0; row < imageSize && file; row += BPP) {
        file >> r >> g >> b;
        imageData[row] = std::stoi(r);
        imageData[row + 1] = std::stoi(g);
        imageData[row + 2] = std::stoi(b);
    }

    std::string fileName = path.substr(path.find_last_of("/") + 1);
    fileName = fileName.substr(0, fileName.find_last_of("."));
    fileName += ".png";

    createPNG(width, height, fileName, imageData, toWrite);
}

void PPMtoPNG::createPNG(int width, int height, std::string &filename, std::vector<int> &imageData, std::string &toWrite)
{
    png_byte color_type = PNG_COLOR_TYPE_RGB;
    png_byte bit_depth = 8;

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) {
        std::cerr << "Error: Failed to create PNG write struct" << std::endl;
        return;
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        std::cerr << "Error: Failed to create PNG info struct" << std::endl;
        return;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        std::cerr << "Error: Failed to set jump" << std::endl;
        return;
    }

    std::ofstream file(toWrite + filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error: Failed to open \"" << filename << "\"" << std::endl;
        return;
    }

    png_set_write_fn(png_ptr, &file, [](png_structp png_ptr, png_bytep data, png_size_t length) {
        auto file = reinterpret_cast<std::ofstream*>(png_get_io_ptr(png_ptr));
        file->write(reinterpret_cast<char*>(data), length);
    }, nullptr);

    png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    png_write_info(png_ptr, info_ptr);

    std::vector<png_byte> row(width * 3);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            row[x * 3 + 0] = static_cast<png_byte>(imageData[(y * width + x) * 3 + 0]);
            row[x * 3 + 1] = static_cast<png_byte>(imageData[(y * width + x) * 3 + 1]);
            row[x * 3 + 2] = static_cast<png_byte>(imageData[(y * width + x) * 3 + 2]);
        }
        png_write_row(png_ptr, row.data());
    }
    png_write_end(png_ptr, nullptr);

    png_destroy_write_struct(&png_ptr, &info_ptr);

    std::cout << "PNG file \"" << filename << "\" created" << std::endl;

    file.close();
}

int main(int ac, char **av)
{
    if (ac < 2 || ac > 3) {
        std::cerr << "Usage: ./PPMtoPNG <file> [outputDestination]" << std::endl;
        return 84;
    }

    std::string path(av[1]);
    std::string toWrite = "./";
    if (av[2]) {
        toWrite = std::string(av[2]) + (std::string(av[2]).back() == '/' ? "" : "/");
    }

    PPMtoPNG converter;
    converter.convert(path, toWrite);

    return 0;
}
