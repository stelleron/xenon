#define STBTT_STATIC
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h" 

#include "utils/vector.hpp"
#include "res/image.hpp"
#include "res/font.hpp"
#include "res/filesystem.hpp"
#include "utils/logger.hpp"

namespace xenon {
    Font::Font() {
        glyphs = nullptr;
    }

    Font::Font(const char* path, int fontsize) {
        glyphs = nullptr;
        load(path, fontsize);
    }

    Font::Font(unsigned char* data, size_t size, int fontsize) {
        glyphs = nullptr;
        load(data, size, fontsize);
    }

    Font::~Font() {
        unload();
    }

    void Font::load(const char* path, int fontsize) {
        size_t fsize;
        // Load file

        // Load file data
        unsigned char* data = filesystem::load_file_data(path, fsize);
        std::string extension = filesystem::get_file_extension(path);
        if (extension == "otf" || extension == "ttf")
            load(data, fsize, fontsize);
        else 
            ERROR("Font: Font type not supported!");
        delete[] data;
    }

    void Font::load(unsigned char* data, size_t size, int fontsize) {
        unload();
        
        glyphs = new GlyphData[NUM_CHARS];
        this->fontSize = fontsize;
        int xCharDim = 0, yCharDim = 0, xOffset = 0, yOffset = 0, imgArea = 0;

        // Load the font
        stbtt_fontinfo ftData = {0};
        if (!stbtt_InitFont(&ftData, data, 0)) {
            ERROR("Font: Could not process the font data!");
            return;
        }

        // Now create the font atlas
        // First fetch font data
        float scale = stbtt_ScaleForPixelHeight(&ftData, fontSize);
        int ascent, descent, lineGap;
        stbtt_GetFontVMetrics(&ftData, &ascent, &descent, &lineGap);

        // Now get the data for each glyph
        for (int i = START_CHAR; i <= END_CHAR; i++) {
            int index = i - START_CHAR;
            // Loading the glyph data
            glyphs[index].image.format = GRAYSCALE;
            stbtt_GetCodepointHMetrics(&ftData, i, &glyphs[index].advance, NULL);
            glyphs[index].advance = (int)((float)glyphs[index].advance*scale);

            if (i != 32) {
                glyphs[index].image.data = 
                stbtt_GetCodepointBitmap(&ftData, scale, scale, i, 
                                        &glyphs[index].image.width, 
                                        &glyphs[index].image.height, 
                                        &glyphs[index].xOffset, 
                                        &glyphs[index].yOffset);
                glyphs[index].yOffset += (int)((float)ascent*scale);
            }
            else {
                glyphs[index].image.data = new unsigned char[fontSize * glyphs[index].advance];
                memset(glyphs[index].image.data, 0, glyphs[index].advance * fontSize);
                glyphs[index].image.width = glyphs[index].advance;
                glyphs[index].image.height = fontSize;
            }
            imgArea += glyphs[index].image.width * glyphs[index].image.height;
        }
        
        // Now generate an atlas
        // First calculate an image size
        float guessSize = sqrtf(imgArea * 2);
        int imageSize = (int)powf(2, ceilf(logf((float)guessSize)/logf(2)));
        
        // Set the font atlas
        Image fontAtlas;
        fontAtlas.data = new unsigned char[imageSize * imageSize];
        memset(fontAtlas.data, 0, imageSize * imageSize);
        fontAtlas.width = imageSize;
        fontAtlas.height = imageSize;
        fontAtlas.format = GRAYSCALE;

        // Now copy the data for each glyph
        int dataPtrX = 0, dataPtrY = 0;
        for (int i = 0; i < NUM_CHARS; i++) {
            for (int y = 0; y < glyphs[i].image.height; y++)
            {
                for (int x = 0; x < glyphs[i].image.width; x++)
                {
                    fontAtlas.data[(y + dataPtrY) * fontAtlas.width + (x + dataPtrX)] = 
                            glyphs[i].image.data[y * glyphs[i].image.width + x];
                }
            }
            // Set the rectangles
            fontRecs[i].pos = {dataPtrX, dataPtrY};
            fontRecs[i].width = glyphs[i].image.width;
            fontRecs[i].height = glyphs[i].image.height;

            dataPtrX += glyphs[i].image.width;

            if (dataPtrX + glyphs[i].image.width >= fontAtlas.width) {
                dataPtrX = 0;
                dataPtrY += fontSize;
            }
        }

        // Convert GRAYSCALE to GRAY_ALPHA
        unsigned char *dataGrayAlpha = new unsigned char[fontAtlas.width * fontAtlas.height * 2]; 

        for (int i = 0, k = 0; i < fontAtlas.width*fontAtlas.height; i++, k += 2)
        {
            dataGrayAlpha[k] = 255;
            dataGrayAlpha[k + 1] = fontAtlas.data[i];
        }

        delete[] fontAtlas.data;
        fontAtlas.data = dataGrayAlpha;
        fontAtlas.format = GRAY_ALPHA;

        // And finally convert it to a texture
        fontTex.load(fontAtlas);
        
    }

    bool Font::is_loaded() {
        if (glyphs) {
            return true;
        }
        else {
            return false;
        }
    }

    void Font::unload() {
        if (is_loaded()) {
            delete[] glyphs;
        }
    }

    int Font::measure_text(Font& font, std::string& str) {
        return measure_text(font, str.c_str(), font.get_size(), DEFAULT_SPACING);
    }

    int Font::measure_text(Font& font, std::string& str, float spacing) {
        return measure_text(font, str.c_str(), font.get_size(), spacing);
    }

    int Font::measure_text(Font& font, std::string& str, int font_size, float spacing) {
        return (int)get_text_size(font, str.c_str(), font_size, spacing).x;
    }

    int Font::measure_text(Font& font, const char* str) {
        return measure_text(font, str, font.get_size(), DEFAULT_SPACING);
    }

    int Font::measure_text(Font& font, const char* str, float spacing) {
        return measure_text(font, str, font.get_size(), spacing);
    }

    int Font::measure_text(Font& font, const char* str, int font_size, float spacing) {
        return (int)get_text_size(font, str, font_size, spacing).x;
    }

    Vector2 Font::get_text_size(Font& font, const char* str, int font_size, float spacing) {
        std::string message = str;
        return get_text_size(font, message, font_size, spacing);
    }

    Vector2 Font::get_text_size(Font& font, std::string& str, int font_size, float spacing) {
        Vector2 text_size;
        float scale_factor = (float)font_size/(float)font.get_size();

        float text_width = 0.0f;
        float text_max_width = 0.0f;
        float text_height = (float)font.get_size();

        for (int x = 0; x < str.size(); x++) {
            if ( (int)str[x] != '\n') {
                if (font.glyphs[(int)str[x] - START_CHAR].advance == 0) text_width += (font.fontRecs[(int)str[x] - START_CHAR].width * scale_factor) + spacing;
                else text_width += (font.glyphs[(int)str[x] - START_CHAR].advance * scale_factor) + spacing;
            }
            else {
                if (text_max_width < text_width) 
                    text_max_width = text_width;
                text_width = 0.0f;
                text_height +=  (float)font.get_size() * LINE_SPACING_FACTOR;
            }
        }


        if (text_max_width < text_width) 
            text_max_width = text_width;

        text_size = {text_width, text_height * scale_factor};

        return text_size;
    }
}