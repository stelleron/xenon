#ifndef XENON_SHADER
    #define XENON_SHADER
    
    #include "utils/vector.hpp"

    namespace xenon {
        // Used to create a shader class 
        class Shader {
            private:
                bool is_init;
                unsigned int id;
            public:
                // Different shader constructors 
                Shader();
                Shader(int exclude1, int exclude2);
                Shader(const char* vSource, int exclude);
                Shader(int exclude, const char* fSource);
                Shader(const char* vSource, const char* fSource);
                
                // Load the shader
                void load(int exclude1, int exclude2);
                void load(const char* vSource, const char* fSource);

                // Uniform setting functions
                void set_bool(const char* name, bool value);  
                void set_int(const char* name, int value);   
                void set_float(const char* name, float value);
                void set_vec2(const char* name, Vector2 vec);
                void set_vec3(const char* name, Vector3 vec);
                void set_vec4(const char* name, Vector4 vec);
                void set_mat4(const char* name, Mat4 matrix);

                // Use the shader
                void use();

                // Getters
                inline const unsigned int get_id() {return id;}
                inline const bool is_loaded() {return is_init;}

                // Setters
                void de_init() { is_init = false;}

                // Copy assignment operator
                Shader& operator=(Shader& shader);

                // Destructor
                ~Shader();
        };
    }
#endif