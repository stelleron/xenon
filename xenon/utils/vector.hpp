#ifndef XENON_VECTOR
    #define XENON_VECTOR
    #include "glm/glm.hpp"
    
    namespace xenon {
        // Used to define vectors
        using Vector2 = glm::vec2;
        using Vector3 = glm::vec3;
        using Vector4 = glm::vec4;

        // Used to define matrices
        using Mat2 = glm::mat2;
        using Mat3 = glm::mat3;
        using Mat4 = glm::mat4;
    }
#endif