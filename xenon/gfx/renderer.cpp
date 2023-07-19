#include <glad/glad.h>
#include <cmath>
#include "gfx/renderer.hpp"
#include "geom/vertex.hpp"
#include "utils/logger.hpp"

#define MAX_BATCH_SIZE 8000

#define DRAW_OBJECT(type, vnum, obj) do { \
    RenderMode rmode = rBatch.vertexArray.get_render_type(); \
    if (rmode == type && rBatch.vertexArray.check_space(rBatch.vertexPointer, vnum) && currentTextureID == defaultTextureID) { \
        rBatch.add(obj); \
    } \
    else { \
        if (rmode != None) { \
            draw(rBatch.vertexArray); \
        } \
        currentTextureID = defaultTextureID; \
        rBatch.vertexArray.reset(type, MAX_BATCH_SIZE); \
        rBatch.vertexPointer = 0; \
        rBatch.add(obj); \
    } \
} while (false); \

namespace xenon {
    // RENDER BATCH IMPL.
    Renderer::RenderBatch::RenderBatch() {
        vertexPointer = 0;
    }

    Renderer::RenderBatch::~RenderBatch() {

    }

    void Renderer::RenderBatch::add(const Point& point) {
        vertexArray.add( drawable::make(point, Color::HexRGB(0xFFFFFF)) , vertexPointer);
        vertexPointer += 1;
    }

    void Renderer::RenderBatch::add(const DrawPoint& point) {
        vertexArray.add(point, vertexPointer);
        vertexPointer += 1;
    }

    void Renderer::RenderBatch::add(const Line& line) {
        vertexArray.add(drawable::make(line, Color::HexRGB(0xFFFFFF)), vertexPointer);
        vertexPointer += 2;
    }

    void Renderer::RenderBatch::add(const DrawLine& line) {
        vertexArray.add(line, vertexPointer);
        vertexPointer += 2;
    }

    void Renderer::RenderBatch::add(const Triangle& triangle) {
        vertexArray.add(drawable::make(triangle, Color::HexRGB(0xFFFFFF)), vertexPointer);
        vertexPointer += 3;
    }

    void Renderer::RenderBatch::add(const DrawTriangle& triangle) {
        vertexArray.add(triangle, vertexPointer);
        vertexPointer += 3;
    }

    void Renderer::RenderBatch::add(const Rectangle& rectangle) {
        vertexArray.add(drawable::make(rectangle, Color::HexRGB(0xFFFFFF)), vertexPointer);
        vertexPointer += 4;
    }

    void Renderer::RenderBatch::add(const Quadrilateral& quad) {
        vertexArray.add(drawable::make(quad, Color::HexRGB(0xFFFFFF)), vertexPointer);
        vertexPointer += 4;
    }

    void Renderer::RenderBatch::add(const DrawQuad& quad) {
        vertexArray.add(quad, vertexPointer);
        vertexPointer += 4;
    }

    void Renderer::RenderBatch::add(Sprite& sprite) {
        Texture* tex = sprite.get_texture_ptr();
        // First set the color of all vertices
        vertexArray[vertexPointer].color = sprite.color;
        vertexArray[vertexPointer + 1].color = sprite.color;
        vertexArray[vertexPointer + 2].color = sprite.color;
        vertexArray[vertexPointer + 3].color = sprite.color;
        // Now set the tex coords
        vertexArray[vertexPointer].texCoords = {sprite.targetRect.pos.x/tex->width, sprite.targetRect.pos.y/tex->height};
        vertexArray[vertexPointer + 1].texCoords = {(sprite.targetRect.pos.x + sprite.targetRect.width)/tex->width, sprite.targetRect.pos.y/tex->height};
        vertexArray[vertexPointer + 2].texCoords = {sprite.targetRect.pos.x/tex->width, (sprite.targetRect.pos.y + sprite.targetRect.height)/tex->height};
        vertexArray[vertexPointer + 3].texCoords = {(sprite.targetRect.pos.x + sprite.targetRect.width)/tex->width, (sprite.targetRect.pos.y + sprite.targetRect.height)/tex->height};
        // And finally positions
        if (sprite.rotation != 0.0f) {
            float radius = sqrt((sprite.targetRect.width * sprite.targetRect.width *  sprite.scale.x *  sprite.scale.x) + (sprite.targetRect.height * sprite.targetRect.height * sprite.scale.y * sprite.scale.y))/2; 
            float topRightAngle = atan( (sprite.targetRect.height * sprite.scale.y) / (sprite.targetRect.width *  sprite.scale.x) ) * 180/M_PI;
            float bottomRightAngle = 180 - topRightAngle;
            float bottomLeftAngle = 180 + topRightAngle;
            float topLeftAngle = 180 + bottomRightAngle;

            vertexArray[vertexPointer].pos = {
                sprite.pos.x + sinf(glm::radians(topLeftAngle + sprite.rotation)) * radius, 
                sprite.pos.y - cosf(glm::radians(topLeftAngle + sprite.rotation)) * radius 
                };
            vertexArray[vertexPointer + 1].pos = {
                sprite.pos.x + sinf(glm::radians(topRightAngle + sprite.rotation)) * radius, 
                sprite.pos.y - cosf(glm::radians(topRightAngle + sprite.rotation)) * radius  
                };
            vertexArray[vertexPointer + 2].pos = {
                sprite.pos.x + sinf(glm::radians(bottomLeftAngle + sprite.rotation)) * radius, 
                sprite.pos.y - cosf(glm::radians(bottomLeftAngle + sprite.rotation)) * radius 
                };
            vertexArray[vertexPointer + 3].pos = {
                sprite.pos.x + sinf(glm::radians(bottomRightAngle + sprite.rotation)) * radius, 
                sprite.pos.y - cosf(glm::radians(bottomRightAngle + sprite.rotation)) * radius
                };
        }
        else {
            vertexArray[vertexPointer].pos = {
                sprite.pos.x - (sprite.scale.x * sprite.targetRect.width)/2, 
                sprite.pos.y - (sprite.scale.y * sprite.targetRect.height)/2
                };
            vertexArray[vertexPointer + 1].pos = {
                sprite.pos.x + (sprite.scale.x * sprite.targetRect.width)/2, 
                sprite.pos.y - (sprite.scale.y * sprite.targetRect.height)/2 
                };
            vertexArray[vertexPointer + 2].pos = {
                sprite.pos.x - (sprite.scale.x * sprite.targetRect.width)/2, 
                sprite.pos.y + (sprite.scale.y * sprite.targetRect.height)/2 
                };
            vertexArray[vertexPointer + 3].pos = {
                sprite.pos.x + (sprite.scale.x * sprite.targetRect.width)/2, 
                sprite.pos.y + (sprite.scale.y * sprite.targetRect.height)/2 
                };
        }

        vertexPointer += 4;
    }

    void Renderer::RenderBatch::add(Texture& tex, Vector2 pos, Vector2 scale, float rotation, Color color, Rectangle targetRect) {
        // Set color
        vertexArray[vertexPointer].color = color;
        vertexArray[vertexPointer + 1].color = color;
        vertexArray[vertexPointer + 2].color = color;
        vertexArray[vertexPointer + 3].color = color; 

        // Calc. some values
        float absWidth = abs(targetRect.width);
        float absHeight = abs(targetRect.height);

        // Set positions 
        if (rotation != 0.0f) {
            float line_dist = sqrt((absWidth * absWidth *  scale.x *  scale.x) + (absHeight * absHeight * scale.y * scale.y));
            vertexArray[vertexPointer].pos = {
                pos.x, 
                pos.y
            };
            vertexArray[vertexPointer + 1].pos = {
                pos.x + sinf(glm::radians(90.0 + rotation)) * absWidth * scale.x,
                pos.y - cosf(glm::radians(90.0 + rotation)) * absWidth * scale.x
                
            };
            vertexArray[vertexPointer + 2].pos = {
                pos.x + sinf(glm::radians(180.0 + rotation)) * absHeight * scale.y,
                pos.y - cosf(glm::radians(180.0 + rotation)) * absHeight * scale.y
                
            };
            vertexArray[vertexPointer + 3].pos = {
                pos.x + sinf(glm::radians(135.0 + rotation)) * line_dist,
                pos.y - cosf(glm::radians(135.0 + rotation)) * line_dist
            };
            
        }
        else {
            vertexArray[vertexPointer].pos = {
                pos.x, 
                pos.y 
                };
            vertexArray[vertexPointer + 1].pos = {
                pos.x + (absWidth * scale.x), 
                pos.y 
                };
            vertexArray[vertexPointer + 2].pos = {
                pos.x, 
                pos.y + (absHeight * scale.y) 
                };
            vertexArray[vertexPointer + 3].pos = {
                pos.x + (absWidth * scale.x),  
                pos.y + (absHeight * scale.y)  
                };
        }
        
        // Check for flipping
        bool flipX = false;
        bool flipY = false;
        if (targetRect.width < 0) {flipX = true;}
        if (targetRect.height < 0) {flipY = true;}

        Vector2 tlTexCoord = {targetRect.pos.x/tex.width, targetRect.pos.y/tex.height}; 
        Vector2 trTexCoord = {(targetRect.pos.x + absWidth)/tex.width, targetRect.pos.y/tex.height};
        Vector2 blTexCoord = {targetRect.pos.x/tex.width, (targetRect.pos.y + absHeight)/tex.height};
        Vector2 brTexCoord = {(targetRect.pos.x + absWidth)/tex.width, (targetRect.pos.y + absHeight)/tex.height};

        // Set tex coords
        if (flipX == false && flipY == false) {
            vertexArray[vertexPointer].texCoords = tlTexCoord;
            vertexArray[vertexPointer + 1].texCoords = trTexCoord;
            vertexArray[vertexPointer + 2].texCoords = blTexCoord;
            vertexArray[vertexPointer + 3].texCoords = brTexCoord;
        }
        else if (flipX == false && flipY == true) {
            vertexArray[vertexPointer].texCoords = blTexCoord;
            vertexArray[vertexPointer + 1].texCoords = brTexCoord;
            vertexArray[vertexPointer + 2].texCoords = tlTexCoord;
            vertexArray[vertexPointer + 3].texCoords = trTexCoord;
        }
        else if (flipX == true && flipY == false) {
            vertexArray[vertexPointer].texCoords = trTexCoord;
            vertexArray[vertexPointer + 1].texCoords = tlTexCoord;
            vertexArray[vertexPointer + 2].texCoords = brTexCoord;
            vertexArray[vertexPointer + 3].texCoords = blTexCoord;
        }
        else {
            vertexArray[vertexPointer].texCoords = brTexCoord;
            vertexArray[vertexPointer + 1].texCoords = blTexCoord;
            vertexArray[vertexPointer + 2].texCoords = trTexCoord;
            vertexArray[vertexPointer + 3].texCoords = tlTexCoord;
        }
                
        /*
        // Set positions 
        if (rotation != 0.0f) {
            float line_dist = sqrt((targetRect.width * targetRect.width *  scale.x *  scale.x) + (targetRect.height * targetRect.height * scale.y * scale.y));
            vertexArray[vertexPointer].pos = {
                pos.x, 
                pos.y
            };
            vertexArray[vertexPointer + 1].pos = {
                pos.x + sinf(glm::radians(90.0 + rotation)) * targetRect.width * scale.x,
                pos.y - cosf(glm::radians(90.0 + rotation)) * targetRect.width * scale.x
                
            };
            vertexArray[vertexPointer + 2].pos = {
                pos.x + sinf(glm::radians(180.0 + rotation)) * targetRect.height * scale.y,
                pos.y - cosf(glm::radians(180.0 + rotation)) * targetRect.height * scale.y
                
            };
            vertexArray[vertexPointer + 3].pos = {
                pos.x + sinf(glm::radians(135.0 + rotation)) * line_dist,
                pos.y - cosf(glm::radians(135.0 + rotation)) * line_dist
            };
            
        }
        else {
            vertexArray[vertexPointer].pos = {
                pos.x, 
                pos.y 
                };
            vertexArray[vertexPointer + 1].pos = {
                pos.x + (targetRect.width * scale.x), 
                pos.y 
                };
            vertexArray[vertexPointer + 2].pos = {
                pos.x, 
                pos.y + (targetRect.height * scale.y) 
                };
            vertexArray[vertexPointer + 3].pos = {
                pos.x + (targetRect.width * scale.x),  
                pos.y + (targetRect.height * scale.y)  
                };
        }
        */

        // Increment vertex pointer
        vertexPointer += 4;
    }

    void Renderer::RenderBatch::add(const Circle& circle) {
        vertexArray.add(drawable::make(circle, Color::HexRGB(0xFFFFFF)), vertexPointer);
        vertexPointer += 37; 
    }

    void Renderer::RenderBatch::add(const DrawCircle& circle) {
        DrawCircle mod_circle = circle;
        vertexArray.add(mod_circle, vertexPointer);
        vertexPointer += 37;
    }

    // RENDER CONTEXT IMPL.
    Renderer::Renderer() {

    }

    Renderer::~Renderer() {
        glDeleteVertexArrays(1, &defaultVAO);
        glDeleteBuffers(1, &defaultVBO);
        glDeleteTextures(1, &defaultTextureID);
        glDeleteBuffers(1, &defaultEBO);
    } 

    void Renderer::init() {
        // Create the default texture here
        unsigned char defaultTexture[4] = { 255, 255, 255, 255 }; 
        glGenTextures(1, &defaultTextureID); 
        glBindTexture(GL_TEXTURE_2D, defaultTextureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);    
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, defaultTexture);
        glGenerateMipmap(GL_TEXTURE_2D);
        glGenVertexArrays(1, &defaultVAO);
        glGenBuffers(1, &defaultVBO);
        glGenBuffers(1, &defaultEBO);
        currentTextureID = defaultTextureID;
    }

    void Renderer::set_vertex_attributes() {
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)8);
        glEnableVertexAttribArray(1);  
         
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)12);
        glEnableVertexAttribArray(2);
    }

    void Renderer::use_shader() {
        currShader->set_mat4("projection", currCamera->get_projection_matrix());
        currShader->use();
    }

    void Renderer::set_surface(Surface& surface) {
        draw_batch();
        glBindFramebuffer(GL_FRAMEBUFFER, surface.id);
        glViewport(0, 0, surface.width, surface.height);
        currCamera->dimensions = {surface.width, surface.height};
        fill({0, 0, 0, 0});
        
    }

    void Renderer::exit_surface() {
        draw_batch();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, currWindow->get_framebuffer_size().x, currWindow->get_framebuffer_size().y);
        currCamera->dimensions = {currWindow->get_window_size().x, currWindow->get_window_size().y};
    }

    void Renderer::fill(Color color) {
        glClearColor(COLOR_TO_FLOAT(color));
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::draw(VertexArray& vArray) {
        RenderMode rMode = vArray.get_render_type();
        if (rMode == None) {
            ERROR("Error: Cannot draw a vertex array with type None!");
        }
        else if (rMode == Quads || rMode == Circles) {
            // Bind all vertex objects
            glBindVertexArray(defaultVAO);
            glBindBuffer(GL_ARRAY_BUFFER, defaultVBO); 
            glBufferData(GL_ARRAY_BUFFER, vArray.get_array_size(), vArray.get_vertex_array(), GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, defaultEBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, vArray.get_index_array_size(), vArray.get_index_array(), GL_STATIC_DRAW);
            set_vertex_attributes();
            glBindBuffer(GL_ARRAY_BUFFER, 0);  
            GLenum drawType;
            switch (rMode) {
                case Circles: drawType = GL_TRIANGLES; break;
                case Quads: drawType = GL_TRIANGLES; break;
                default: break;
            }

            use_shader();
            glBindTexture(GL_TEXTURE_2D, currentTextureID);
            glBindVertexArray(defaultVAO); 
            glDrawElements(drawType, vArray.get_index_array_size()/sizeof(unsigned int), GL_UNSIGNED_INT, 0);
        }
        else {
            // Bind all vertex objects
            glBindVertexArray(defaultVAO);
            glBindBuffer(GL_ARRAY_BUFFER, defaultVBO); 
            glBufferData(GL_ARRAY_BUFFER, vArray.get_array_size(), vArray.get_vertex_array(), GL_STATIC_DRAW);
            set_vertex_attributes();
            glBindBuffer(GL_ARRAY_BUFFER, 0);  
            GLenum drawType;
            switch (rMode) {
                case Points: drawType = GL_POINTS; break;
                case Lines: drawType = GL_LINES; break;
                case Triangles: drawType = GL_TRIANGLES; break;
                default: break;
            }

            use_shader();
            glBindTexture(GL_TEXTURE_2D, currentTextureID);
            glBindVertexArray(defaultVAO);
            glDrawArrays(drawType, 0, vArray.get_num_vertices());
        }
    }

    void Renderer::draw_point(float x, float y, Color color) {
        draw(drawable::make(Point({x, y}), color));
    }

    void Renderer::draw_point(Vector2 pos, Color color) {
        draw(drawable::make(Point(pos), color));
    }

    void Renderer::draw(const Point& point) {
        DRAW_OBJECT(Points, 1, point);
    }

    void Renderer::draw(const DrawPoint& point) {
        DRAW_OBJECT(Points, 1, point);
    }

    void Renderer::draw_line(float startX, float startY, float endX, float endY, Color color) {
        draw(drawable::make(Line({startX, startY}, {endX, endY}), color));
    }

    void Renderer::draw_line(Vector2 startPos, Vector2 endPos, Color color) {
        draw(drawable::make(Line(startPos, endPos), color));
    }

    void Renderer::draw(const Line& line) {
        DRAW_OBJECT(Lines, 2, line);
    }

    void Renderer::draw(const DrawLine& line) {
        DRAW_OBJECT(Lines, 2, line);
    }

    void Renderer::draw_triangle(Vector2 point1, Vector2 point2, Vector2 point3, Color color) {
        draw(drawable::make(Triangle(point1, point2, point3), color));
    }

    void Renderer::draw(const Triangle& triangle) {
        DRAW_OBJECT(Triangles, 3, triangle);
    }

    void Renderer::draw(const DrawTriangle& triangle) {
        DRAW_OBJECT(Triangles, 3, triangle);
    }

    void Renderer::draw_square(float x, float y, float size, Color color) {
        draw(drawable::make(Rectangle{{x, y}, size}, color));
    }

    void Renderer::draw_square(Vector2 pos, float size, Color color) {
        draw(drawable::make(Rectangle{pos, size}, color));
    }
    
    void Renderer::draw_rect(float x, float y, float width, float height, Color color) {
        draw(drawable::make(Rectangle{{x, y}, width, height}, color));
    }

    void Renderer::draw_rect(Vector2 pos, float width, float height, Color color) {
        draw(drawable::make(Rectangle{pos, width, height}, color));
    }

    void Renderer::draw_quad(Vector2 point1, Vector2 point2, Vector2 point3, Vector2 point4, Color color) {
        draw(drawable::make(Quadrilateral{point1, point2, point3, point4}, color));
    }

    void Renderer::draw(const Rectangle& rectangle) {
        DRAW_OBJECT(Quads, 4, rectangle);
    }

    void Renderer::draw(const Quadrilateral& quad) {
        DRAW_OBJECT(Quads, 4, quad);
    }

    void Renderer::draw(const DrawQuad& quad) {
        DRAW_OBJECT(Quads, 4, quad);
    }

    void Renderer::draw_circle(float x, float y, float radius, Color color) {
        draw(drawable::make(Circle{{x, y}, radius}, color));
    }

    void Renderer::draw_circle(Vector2 pos, float radius, Color color) {
        draw(drawable::make(Circle{pos, radius}, color));
    }

    void Renderer::draw(const Circle& circle) {
        DRAW_OBJECT(Circles, 37, circle);
    }

    void Renderer::draw(const DrawCircle& circle) {
        DRAW_OBJECT(Circles, 37, circle);
    }

    void Renderer::draw(Sprite& sprite) {
        Texture* tex = sprite.get_texture_ptr();
        RenderMode rmode = rBatch.vertexArray.get_render_type(); 
        if (rmode == Quads && rBatch.vertexArray.check_space(rBatch.vertexPointer, 4) && currentTextureID == tex->id) { 
            rBatch.add(sprite); 
        } 
        else { 
            if (rmode != None) { 
                draw(rBatch.vertexArray); 
            } 
            currentTextureID = tex->id; 
            rBatch.vertexArray.reset(Quads, MAX_BATCH_SIZE); 
            rBatch.vertexPointer = 0; 
            rBatch.add(sprite); 
        } 
    }

    void Renderer::draw(Texture& tex, Vector2 pos, Vector2 scale, float rotation, Color color) {
        draw(tex, Rectangle({0.0, 0.0}, tex.width, tex.height), pos, scale, rotation, color);
    } 

    void Renderer::draw(Texture& tex, Rectangle targetRect, Vector2 pos, Vector2 scale, float rotation, Color color) {
        RenderMode rmode = rBatch.vertexArray.get_render_type();
        if (rmode == Quads && rBatch.vertexArray.check_space(rBatch.vertexPointer, 4) && currentTextureID == tex.id) { 
            rBatch.add(tex, pos, scale, rotation, color, targetRect); 
        } 
        else { 
            if (rmode != None) { 
                draw(rBatch.vertexArray); 
            } 
            currentTextureID = tex.id; 
            rBatch.vertexArray.reset(Quads, MAX_BATCH_SIZE); 
            rBatch.vertexPointer = 0; 
            rBatch.add(tex, pos, scale, rotation, color, targetRect); 
        }
    }

    void Renderer::draw(Surface& tex, Vector2 pos, Vector2 scale, float rotation, Color color) {
        draw(tex.color_tex, (Rectangle){{0.0, 0.0}, (float)tex.width, -(float)tex.height}, pos, scale, rotation, color);
    }

    void Renderer::draw(Surface& tex, Rectangle targetRect, Vector2 pos, Vector2 scale, float rotation, Color color) {
        draw(tex.color_tex, targetRect, pos, scale, rotation, color);
    }

    void Renderer::print(Font& font, std::string message, Vector2 pos, Vector2 scale, Color color, float spacing) {
        float xOffset = 0.0f;
        int yOffset = 0;

        for (int x = 0; x < message.size(); x++) {
            if (message[x] == '\n') {
                yOffset = (int)(font.get_size() * LINE_SPACING_FACTOR * scale.y);
                xOffset = 0.0f;
            }
            else {
                RenderMode rmode = rBatch.vertexArray.get_render_type();
                if (rmode == Quads && rBatch.vertexArray.check_space(rBatch.vertexPointer, 4) && currentTextureID == font.fontTex.id) { 
                    rBatch.add(font.fontTex, {pos.x + xOffset + font.glyphs[(int)message[x] - START_CHAR].xOffset*scale.x , pos.y + yOffset + font.glyphs[(int)message[x] - START_CHAR].yOffset*scale.y}, scale, 0, color, font.fontRecs[(int)message[x] - START_CHAR]); 
                } 
                else { 
                    if (rmode != None) { 
                        draw(rBatch.vertexArray); 
                    } 
                    currentTextureID = font.fontTex.id; 
                    rBatch.vertexArray.reset(Quads, MAX_BATCH_SIZE); 
                    rBatch.vertexPointer = 0; 
                    rBatch.add(font.fontTex, {pos.x + xOffset + font.glyphs[(int)message[x] - START_CHAR].xOffset*scale.x , pos.y + yOffset + font.glyphs[(int)message[x] - START_CHAR].yOffset*scale.y}, scale, 0, color, font.fontRecs[(int)message[x] - START_CHAR]);
                }
                if (font.glyphs[(int)message[x] - START_CHAR].advance == 0) xOffset += (font.fontRecs[(int)message[x] - START_CHAR].width * scale.x) + spacing;
                else xOffset += (font.glyphs[(int)message[x] - START_CHAR].advance * scale.x) + spacing; 
            }           
        }
    }

    void Renderer::draw_batch() {
        // Reset the draw batch
        RenderMode rmode = rBatch.vertexArray.get_render_type();
        if (rmode != None) {
            draw(rBatch.vertexArray);
        }
        rBatch.vertexArray.reset();
        rBatch.vertexPointer = 0;
    }

}