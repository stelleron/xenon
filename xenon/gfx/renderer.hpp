#ifndef XENON_RENDERER
    #define XENON_RENDERER

    #include <string>
    #include "camera/camera.hpp"
    #include "window/window.hpp"
    #include "gfx/shader.hpp"
    #include "gfx/sprite.hpp"
    #include "gfx/surface.hpp"
    #include "gfx/vertex_array.hpp"
    #include "res/font.hpp"


    namespace xenon {
        // Implemenets the renderer
        class Renderer {
            // Creates an internal render batch
            struct RenderBatch {
                VertexArray vertexArray;
                int vertexPointer;

                RenderBatch();
                ~RenderBatch();

                // Used to add objects to the render batch
                void add(const Point& point);
                void add(const DrawPoint& point);

                void add(const Line& line);
                void add(const DrawLine& line);

                void add(const Triangle& triangle);
                void add(const DrawTriangle& triangle);

                void add(const Rectangle& rectangle);
                void add(const Quadrilateral& quad);
                void add(const DrawQuad& quad);

                void add(const Circle& circle);
                void add(const DrawCircle& circle);

                void add(Sprite& sprite);
                void add(Texture& tex, Vector2 pos, Vector2 scale, float rotation, Color color, Rectangle targetRect);
            };

            private:
                Shader* currShader;
                Camera* currCamera;
                Shader* defaultShader;
                Camera* defaultCamera;  
                Window* currWindow;
                RenderBatch rBatch;

                unsigned int defaultVBO;
                unsigned int defaultVAO;
                unsigned int defaultEBO;
                unsigned int defaultTextureID;
                unsigned int currentTextureID;

                void set_vertex_attributes();
                void use_shader();
                void draw_batch_and_reset();
            public:
                // Constructor
                Renderer();
                // Destructor
                ~Renderer();
                void init();

                // Setting shaders and cameras
                void set_default_camera(Camera& camera) {defaultCamera = &camera;}
                void set_default_shader(Shader& shader) {defaultShader = &shader;}
                
                void set_current_camera(Camera& camera) {currCamera = &camera;}
                void set_current_shader(Shader& shader) {currShader = &shader;}

                void use_default_camera() {currCamera = defaultCamera;}
                void use_default_shader() {currShader = defaultShader;}

                void set_surface(Surface& surface);
                void exit_surface();

                void set_window(Window& window) {currWindow = &window;}

                // Fill the screen
                void fill(Color color);

                // Draw functions
                void draw(VertexArray& vArray);

                // Used to add objects to the render batch
                void draw_point(float x, float y, Color color);
                void draw_point(Vector2 pos, Color color);
                void draw(const Point& point);
                void draw(const DrawPoint& point);

                void draw_line(float startX, float startY, float endX, float endY, Color color);
                void draw_line(Vector2 startPos, Vector2 endPos, Color color);
                void draw(const Line& line);
                void draw(const DrawLine& line);

                void draw_triangle(Vector2 point1, Vector2 point2, Vector2 point3, Color color);
                void draw(const Triangle& triangle);
                void draw(const DrawTriangle& triangle);

                void draw_square(float x, float y, float size, Color color);
                void draw_square(Vector2 pos, float size, Color color);
                void draw_rect(float x, float y, float width, float height, Color color);
                void draw_rect(Vector2 pos, float width, float height, Color color);
                void draw_quad(Vector2 point1, Vector2 point2, Vector2 point3, Vector2 point4, Color color);
                void draw(const Rectangle& rectangle);
                void draw(const Quadrilateral& quad);
                void draw(const DrawQuad& quad);

                void draw_circle(float x, float y, float radius, Color color);
                void draw_circle(Vector2 pos, float radius, Color color);
                void draw(const Circle& circle);
                void draw(const DrawCircle& circle);

                // Used to render textures and sprites
                void draw(Sprite& sprite);

                void draw(Texture& tex, Vector2 pos = {0.0, 0.0}, Vector2 scale = {1.0, 1.0}, float rotation = 0.0, Color color = Color::RGB(255, 255, 255));
                void draw(Texture& tex, Rectangle targetRect, Vector2 pos = {0.0, 0.0}, Vector2 scale = {1.0, 1.0}, float rotation = 0.0, Color color = Color::RGB(255, 255, 255));
                void draw(Surface& tex, Vector2 pos = {0.0, 0.0}, Vector2 scale = {1.0, 1.0}, float rotation = 0.0, Color color = Color::RGB(255, 255, 255));
                void draw(Surface& tex, Rectangle targetRect, Vector2 pos = {0.0, 0.0}, Vector2 scale = {1.0, 1.0}, float rotation = 0.0, Color color = Color::RGB(255, 255, 255));

                // Used to render text
                void print(Font& font, std::string message, Vector2 pos = {0.0, 0.0}, Vector2 scale = {1.0, 1.0}, Color color = Color::RGB(255, 255, 255), int padding = 4);

                void draw_batch();
        };
    }

#endif