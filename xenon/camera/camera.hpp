#ifndef XENON_CAMERA
    #define XENON_CAMERA
    // Includes
    #include "utils/vector.hpp"

    namespace xenon {
        // Used to create a 2D camera
        class Camera { 
            public:
                Vector2 dimensions; // Stores the camera dimensions
                Vector2 offset;
                float zoom; 
                float rotation;

                // Constructor
                Camera();
                // Destructor 
                ~Camera();

                // Get the projection matrix
                Mat4 get_projection_matrix();

                void reset();
        };
    }
#endif