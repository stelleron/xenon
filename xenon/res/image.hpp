#ifndef XENON_IMAGE
    #define XENON_IMAGE
    namespace xenon {
        // Enumerate the image formats
        enum ImageFormat {
            RGB,
            RGBA,
            GRAYSCALE,
            GRAY_ALPHA
        };
        // Struct for loading images
        struct Image {
            unsigned char* data;
            int width;
            int height;
            ImageFormat format;

            // Constructor
            Image();
            Image(const char* path);
            Image(unsigned char* data, size_t size);
            // Destructor 
            ~Image();

            void load(const char* path);
            void load(unsigned char* data, size_t size);
            void unload();
            bool is_loaded(); // Check if the image has been loaded
        };
    }
#endif