#include <glad/glad.h>
#include "gfx/shader.hpp"
#include "utils/logger.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace xenon {
    // Default shaders
    const char* vShaderSrc ="#version 330\n"
        "layout (location = 0) in vec2 aPos;\n"
        "layout (location = 1) in vec4 aColor;\n"
        "layout (location = 2) in vec2 aTexCoords;\n"
        "uniform mat4 projection;\n"
        "out vec4 fColor;\n"
        "out vec2 fTexCoords;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = projection * vec4(aPos, 0.0, 1.0);\n"
        "   fColor = aColor;\n"
        "   fTexCoords = aTexCoords;\n"
        "}\0";

    const char* fShaderSrc = "#version 330\n"
        "in vec4 fColor;\n"
        "in vec2 fTexCoords;\n"
        "out vec4 color;\n"
        "uniform sampler2D tex;\n"
        "void main()\n"
        "{\n"
        "   color = fColor * texture(tex, fTexCoords);\n"
        "}\n\0";

    // Shader compile functions
    void printErrors(unsigned int id, GLenum cmdType) {
        int success;
        char infoLog[512];
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(id, 512, NULL, infoLog);
            ERROR(infoLog);
        }
    }

    inline unsigned int compileShader(const char* source, GLenum sType) {
        unsigned int shaderid = glCreateShader(sType);
        glShaderSource(shaderid, 1, &source, NULL);
        glCompileShader(shaderid);
        printErrors(shaderid, GL_COMPILE_STATUS);
        return shaderid;   
    }

    inline unsigned int compileProgram(unsigned int vShader, unsigned int fShader) {
        unsigned int shaderid = glCreateProgram();
        glAttachShader(shaderid, vShader);
        glAttachShader(shaderid, fShader);
        glLinkProgram(shaderid);
        printErrors(shaderid, GL_LINK_STATUS);
        return shaderid;
    }

    // Impl. for shaders
    Shader::Shader() {
        is_init = false;
    }

    Shader::Shader(int exclude1, int exclude2) {
        load(vShaderSrc, fShaderSrc);
    }

    Shader::Shader(int exclude, const char* fSource) {
        load(vShaderSrc, fSource);
    } 

    Shader::Shader(const char* vSource, int exclude) {
        load(vSource, fShaderSrc);
    }

    Shader::Shader(const char* vSource, const char* fSource) {
        load(vSource, fSource);     
    }

    void Shader::load(int exclude1, int exclude2) {
        load(vShaderSrc, fShaderSrc);
    }

    void Shader::load(const char* vSource, const char* fSource) {
        id = compileProgram(
            compileShader(vSource, GL_VERTEX_SHADER), 
            compileShader(fSource, GL_FRAGMENT_SHADER)
        );
        is_init = true;  
    }

    void Shader::set_bool(const char* name , bool value) {
        if (is_init) {
            glUniform1i(glGetUniformLocation(id, name), (int)value); 
        }
    }

    void Shader::set_int(const char* name, int value)
    { 
        if (is_init) {
            glUniform1i(glGetUniformLocation(id, name), value); 
        } 
    } 

    void Shader::set_float(const char* name , float value) {
        if (is_init) {
            glUniform1f(glGetUniformLocation(id, name), value); 
        }
    }

    void Shader::set_vec2(const char* name, Vector2 vec) {
        if (is_init) {
            glUniform2f(glGetUniformLocation(id, name), vec.x, vec.y);
        }
    }

    void Shader::set_vec3(const char* name, Vector3 vec) {
        if (is_init) {
            glUniform3f(glGetUniformLocation(id, name), vec.x, vec.y, vec.z);
        }
    }

    void Shader::set_vec4(const char* name, Vector4 vec) {
        if (is_init) {
            glUniform4f(glGetUniformLocation(id, name), vec.x, vec.y, vec.z, vec.w);
        }
    }

    void Shader::set_mat4(const char* name, Mat4 matrix) {
        if (is_init) {
            glUniformMatrix4fv(glGetUniformLocation(id, name), 1, false, glm::value_ptr(matrix));
        }
    }

    void Shader::use() {
        if (is_init) {
            glUseProgram(id);
        }
    }

    Shader& Shader::operator=(Shader& shader) {
        if (is_init) {glDeleteProgram(id);} 
        id = shader.get_id();
        shader.de_init();
        is_init = true;
        return *this;
    }

    Shader::~Shader() {
        if (is_init) {
            glDeleteProgram(id);
        }
    }
}