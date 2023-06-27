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
        data = nullptr;
        load(path);
    }

    Image::Image(unsigned char* data, size_t size) {
        data = nullptr;
        load(data, size);
    }

    Image::~Image() {
        unload();
    }

    void Image::load(const char* path) {
        size_t fsize;
        unsigned char* fdata = filesystem::load_file_data(path, fsize);
        load(fdata, fsize);
    }

    void Image::load(unsigned char* data, size_t size) {
        // First unload existing data
        unload();
        
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

    void Image::unload() {
        if (is_loaded())
            stbi_image_free(data);
        data = nullptr;
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