#ifndef XENON_FONT
    #define XENON_FONT
    #include "geom/geometry.hpp"
    #include "gfx/sprite.hpp"

    #define START_CHAR 32
    #define END_CHAR 126
    #define NUM_CHARS END_CHAR - START_CHAR + 1
    
    #define DEFAULT_FONT_SIZE 32

    namespace xenon {
        // Used to store glyph data
        struct GlyphData {
            int charValue;
            int xOffset;
            int yOffset;
            int advance;
            Image image;
        };

        // Used to create a font object
        struct Font {
            private:
                int fontSize;
            public:
                Rectangle fontRecs[NUM_CHARS];
                Texture fontTex;
                GlyphData* glyphs;

                // Constructor
                Font();
                Font(const char* path, int fontsize = DEFAULT_FONT_SIZE);
                Font(unsigned char* data, size_t size, int fontsize = DEFAULT_FONT_SIZE);
                // Destructor 
                ~Font();

                void load(const char* path, int fontsize = DEFAULT_FONT_SIZE);
                void load(unsigned char* data, size_t size, int fontsize = DEFAULT_FONT_SIZE);
                void unload();
                bool is_loaded(); // Check if the font has been loaded

                int get_size() {return fontSize;}
        };
    }
#endif