#ifndef XENON_SURFACE
    #define XENON_SURFACE
    #include "gfx/sprite.hpp"

    namespace xenon {
        struct Surface {
            unsigned int id;
            int width;
            int height;
            Texture color_tex;
            Texture depth_tex;

            // Constructors
            Surface();
            Surface(int width, int height);

            // Destructors
            ~Surface();

            void load(int width, int height);
            void unload();
            
            bool is_loaded();
        };
    }
#endif