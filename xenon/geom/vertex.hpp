#ifndef XENON_VERTEX
    #define XENON_VERTEX
    // Includes
    #include "utils/color.hpp"
    #include "utils/vector.hpp"

    // Macro defines
    #define VERTEX_SIZE 9

    namespace xenon {
        // Used to create a vertex object
        struct Vertex {
            Vector2 pos;
            Color color;
            Vector2 texCoords;
        
            // Constructor
            Vertex();
            Vertex(Vector2 pos);
            Vertex(Vector2 pos, Color color);
            Vertex(Vector2 pos, Color color, Vector2 texCoords);
        };
    }
#endif