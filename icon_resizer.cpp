#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <filesystem>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize2.h"

namespace fs = std::filesystem;

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input.png>\n";
        return 1;
    }

    std::string inputFile = argv[1];
    int width, height, channels;
    unsigned char* image = stbi_load(inputFile.c_str(), &width, &height, &channels, 0);
    if (!image) {
        std::cerr << "Failed to open file: " << inputFile << "\n";
        return 1;
    }

    std::vector<int> sizes = {16, 22, 24, 32, 48, 64, 128, 256, 512};

    for (int size : sizes) {
        std::vector<unsigned char> resized(size * size * channels);

        // v2 API: cast channel count to stbir_pixel_layout (1->Y, 2->YA, 3->RGB, 4->RGBA)
        unsigned char* out = stbir_resize_uint8_srgb(
            image, width, height, 0,
            resized.data(), size, size, 0,
            static_cast<stbir_pixel_layout>(channels)
        );

        if (!out) {
            std::cerr << "Failed to resize: " << size << "x" << size << "\n";
            continue;
        }

        fs::path outPath = fs::path("icon_" + std::to_string(size) + ".png");
        if (!stbi_write_png(outPath.string().c_str(), size, size, channels, resized.data(), size * channels)) {
            std::cerr << "Failed to write file: " << outPath << "\n";
        } else {
            std::cout << "Created: " << outPath << "\n";
        }
    }

    stbi_image_free(image);
    return 0;
}
