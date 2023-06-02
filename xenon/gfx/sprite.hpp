#ifndef XENON_SPRITE
    #define XENON_SPRITE
    
    #include "utils/color.hpp"
    #include "geom/geometry.hpp"
    #include "res/image.hpp"

    namespace xenon {
        // Used to store the data for a sprite
        struct SpriteData {
            Vector2 pos;
            Vector2 scale;
            Rectangle targetRect;
            Color color;
            float rotation;
            SpriteData();
        };

        // Used to create a texture 
        struct Texture {
            unsigned int id;
            int width;
            int height;

            // Constructors
            Texture();
            Texture(const char* path);
            Texture(unsigned char* data, size_t size);
            Texture(const Image& image);
            Texture(int width, int height);
            // Desturctors
            ~Texture();
            
            // Loading functions
            void load(const char* path);
            void load(unsigned char* data, size_t size);
            void load(const Image& image);
            void load(int width, int height);

            bool is_loaded();
        };


        // Used to create a sprite
        class Sprite : public SpriteData {
            private:
                Texture tex;
            public:
                // Constructors
                Sprite();
                Sprite(const char* path);
                Sprite(unsigned char* data, size_t size);
                Sprite(const Image& image);
                // Destructors
                ~Sprite();

                // Loading functions
                void load(const char* path);
                void load(unsigned char* data, size_t size);
                void load(const Image& image);

                bool is_loaded();

                // Get the texture pointer
                inline Texture* get_texture_ptr() {return &tex;}
        };
    }
#endif