#include "gfx/surface.hpp"
#include "glad/glad.h"
#include "utils/logger.hpp"

namespace xenon {
    Surface::Surface() {
        id = 0;
    }

    Surface::Surface(int width, int height) {
        id = 0;
        load(width, height);
    }

    Surface::~Surface() {
        unload();
    }

    void Surface::unload() {
        if (is_loaded()) {
            glDeleteTextures(1, &id);
        }
        id = 0;
    }

    void Surface::load(int width, int height) {
        // First unload existing data in advance
        unload();

        // First create a framebuffer
        glGenFramebuffers(1, &id);
        glBindFramebuffer(GL_FRAMEBUFFER, id);
        this->width = width;
        this->height = height;

        // Now attach a color texture
        color_tex.load(width, height);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_tex.id, 0);

        // Now attach a depth texture
        glGenRenderbuffers(1, &depth_tex.id);
        glBindRenderbuffer(GL_RENDERBUFFER, depth_tex.id);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_tex.id);
        depth_tex.width = width;
        depth_tex.height = height;
            
        // Unbind framebuffer and texture
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            ERROR("Error: Framebuffer is not complete!");
                
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, 0); 
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

    bool Surface::is_loaded() {
        if (id) {
            return true;
        }
        else {
            return false;
        }
    }
}