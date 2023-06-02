#ifndef XENON_COLOR
    #define XENON_COLOR
    
    namespace xenon {
        // Used to create a color object
        struct Color {
            unsigned char r;
            unsigned char g;
            unsigned char b;
            unsigned char a;

            // Constructor options
            Color();
            Color(unsigned char r, unsigned char g, unsigned char b);
            Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

            // Static constructors
            static Color RGB(unsigned char r, unsigned char g, unsigned char b);
            static Color RGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
            static Color HSV(float h, float s, float v);
            static Color HSVA(float h, float s, float v, unsigned char a);
            static Color NormalRGB(float r_normal, float g_normal, float b_normal);
            static Color NormalRGBA(float r_normal, float g_normal, float b_normal, float a_normal);
            static Color HexRGB(int hexValue);
            static Color HexRGBA(int hexValue);
        };

        #define FLOAT_REP(color) (float)color/255
        #define COLOR_TO_FLOAT(color) FLOAT_REP(color.r), FLOAT_REP(color.g), FLOAT_REP(color.b), FLOAT_REP(color.a)

        #define LIGHTGRAY  (Color){ 200, 200, 200, 255 }   // Light Gray
        #define GRAY       (Color){ 130, 130, 130, 255 }   // Gray
        #define DARKGRAY   (Color){ 80, 80, 80, 255 }      // Dark Gray
        #define YELLOW     (Color){ 253, 249, 0, 255 }     // Yellow
        #define GOLD       (Color){ 255, 203, 0, 255 }     // Gold
        #define ORANGE     (Color){ 255, 161, 0, 255 }     // Orange
        #define PINK       (Color){ 255, 109, 194, 255 }   // Pink
        #define RED        (Color){ 230, 41, 55, 255 }     // Red
        #define MAROON     (Color){ 190, 33, 55, 255 }     // Maroon
        #define GREEN      (Color){ 0, 228, 48, 255 }      // Green
        #define LIME       (Color){ 0, 158, 47, 255 }      // Lime
        #define DARKGREEN  (Color){ 0, 117, 44, 255 }      // Dark Green
        #define SKYBLUE    (Color){ 102, 191, 255, 255 }   // Sky Blue
        #define BLUE       (Color){ 0, 121, 241, 255 }     // Blue
        #define DARKBLUE   (Color){ 0, 82, 172, 255 }      // Dark Blue
        #define PURPLE     (Color){ 200, 122, 255, 255 }   // Purple
        #define VIOLET     (Color){ 135, 60, 190, 255 }    // Violet
        #define DARKPURPLE (Color){ 112, 31, 126, 255 }    // Dark Purple
        #define BEIGE      (Color){ 211, 176, 131, 255 }   // Beige
        #define BROWN      (Color){ 127, 106, 79, 255 }    // Brown
        #define DARKBROWN  (Color){ 76, 63, 47, 255 }      // Dark Brown

        #define WHITE      (Color){ 255, 255, 255, 255 }   // White
        #define BLACK      (Color){ 0, 0, 0, 255 }         // Black
        #define BLANK      (Color){ 0, 0, 0, 0 }           // Blank (Transparent)
        #define MAGENTA    (Color){ 255, 0, 255, 255 }     // Magenta
    }
#endif