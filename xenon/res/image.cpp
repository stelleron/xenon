#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "res/filesystem.hpp"
#include "res/image.hpp"
#include "utils/logger.hpp"

namespace xenon {
    Image::Image() {
        data = nullptr;
    }

    Image::Image(const char* path) {
        load(path);
    }

    Image::Image(unsigned char* data, size_t size) {
        load(data, size);
    }

    Image::~Image() {
        if (data)
            stbi_image_free(data);
    }

    void Image::load(const char* path) {
        size_t fsize;
        unsigned char* data = filesystem::load_file_data(path, fsize);
        load(data, fsize);
    }

    void Image::load(unsigned char* data, size_t size) {
        stbi_set_flip_vertically_on_load(0);
        int colorChannels;
        this->data = stbi_load_from_memory(data, size, &width, &height, &colorChannels, 0);
        switch (colorChannels) {
            case 1: format = GRAYSCALE; break;
            case 2: format = GRAY_ALPHA; break;
            case 3: format = RGB; break;
            case 4: format = RGBA; break;
            default: break;
        }
    }

    bool Image::is_loaded() {
        if (data) {
            return true;
        }
        else {
            return false;
        }
    }
}