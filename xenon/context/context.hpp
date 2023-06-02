#ifndef XENON_CONTEXT
    #define XENON_CONTEXT

    #include "window/window.hpp"
    #include "input/event_data.hpp"
    #include "camera/camera.hpp"
    #include "audio/audio.hpp"
    #include "gfx/renderer.hpp"
    #include <map>


    namespace xenon {
        // Used to store the context that allows the player to interface with the engine
        class Context {
            struct WindowContext {
                private:
                    EventData* event_data;
                    Window* window;
                public:
                    inline void set(Window& window) {this->window = &window;}
                    inline void set_event_data(EventData& events) {event_data = &events;}

                    inline bool was_resized() {return event_data->windowData.wasResized;} // Was the window resized last frame?
                    inline bool was_moved() {return event_data->windowData.wasMoved;} // Was the window moved last frame?
                    inline bool is_minimized() {return event_data->windowData.isMinimized;} // Is the window minimized?
                    inline bool is_maxmized() {return event_data->windowData.isMaximized;} // Is the window maximized?
                    inline bool is_in_focus() {return event_data->windowData.inFocus;}
                    inline Vector2 get_pos() {return event_data->windowData.windowPos;} // Gets the window position
                    inline Vector2 get_size() {return window->get_window_size();}
                    inline Vector2 get_frame_size() {return window->get_framebuffer_size();}
                    inline void set_min_window_size(int min_width, int min_height) {window->set_min_size(Vector2(min_width, min_height));}
                    inline void set_max_window_size(int max_width, int max_height) {window->set_max_size(Vector2(max_width, max_height));}
                    inline void set_pos(Vector2 pos) {window->set_window_pos(pos);}
                    inline void set_pos(int x, int y) {set_pos(Vector2(x, y));}
                    inline void restore() {window->restore();}
                    inline void minimize() {window->minimize();}
                    inline void maximize() {window->maximize();}
                    inline void update_title(const char* title) {window->update_title(title);}
                
                    inline void close() {window->close();}

            };

            struct TimerContext {
                private:
                    float dtime;
                public: 
                    TimerContext() {dtime = 0.0f;}
                    inline void set(float dtime) {this->dtime = dtime;}
                    inline float dt() {return dtime;}
                    inline int fps() {return (int)1.0f/dtime;}
            };

            struct CameraContext {
                private:
                    Camera* camera;
                public: 
                    inline void set(Camera& camera) {this->camera = &camera;}
                    inline Camera* get() {return camera;}

            };

            struct KeyboardContext {
                private:  
                    EventData* event_data;
                public:
                    inline void set_event_data(EventData& events) {event_data = &events;}
                    inline bool is_pressed(Key key) {
                    if (event_data->keyboardData.keyPressed[key - 1] && !event_data->keyboardData.keyLastPressed[key - 1]) {
                        return true;
                    }
                    return false;
                    }

                    // If the key was just released
                    inline bool is_released(Key key) {
                        if (!event_data->keyboardData.keyPressed[key - 1] && event_data->keyboardData.keyLastPressed[key - 1]) {
                            return true;
                        }
                        return false;
                    }

                    // If the key is being held down
                    inline bool is_held(Key key) {
                        if (event_data->keyboardData.keyPressed[key - 1] && event_data->keyboardData.keyLastPressed[key - 1]) {
                            return true;
                        }
                        return false;
                    }

                    // If the key isn't being pressed at all
                    inline bool is_up(Key key) {
                        if (!event_data->keyboardData.keyPressed[key - 1] && !event_data->keyboardData.keyLastPressed[key - 1]) {
                            return true;
                        }
                        return false;
                    }

                    // Get typed characters one at a time
                    inline unsigned char get_char_pressed() {
                        if (event_data->keyboardData.charQueue.size() > 0) {
                            unsigned char val = event_data->keyboardData.charQueue.front();
                            event_data->keyboardData.charQueue.pop();
                            return val;
                        }
                        else {
                            return 0;
                        }
                    }
            };

            struct MouseContext {
                private:  
                    EventData* event_data;
                public:
                    inline void set_event_data(EventData& events) {event_data = &events;} 
                    inline bool is_pressed(MouseButton button) {
                    if (event_data->mouseData.buttonPressed[button - 1] && !event_data->mouseData.buttonLastPressed[button - 1]) {
                        return true;
                    }
                    return false;
                    }

                    // If the mouse button was just released
                    inline bool is_released(MouseButton button) {
                        if (!event_data->mouseData.buttonPressed[button - 1] && event_data->mouseData.buttonLastPressed[button - 1]) {
                            return true;
                        }
                        return false;
                    }

                    // If the mouse button was being held
                    inline bool is_held(MouseButton button) {
                        if (event_data->mouseData.buttonPressed[button - 1] && event_data->mouseData.buttonLastPressed[button - 1]) {
                            return true;
                        }
                        return false;
                    }

                    // If the mouse button is up
                    inline bool is_up(MouseButton button) {
                        if (!event_data->mouseData.buttonPressed[button - 1] && !event_data->mouseData.buttonLastPressed[button - 1]) {
                            return true;
                        }
                        return false;
                    }

                    // Get mouse position 
                    inline Vector2 get_pos() {return event_data->mouseData.mousePos;}

                    // Get mouse delta
                    inline Vector2 get_delta_pos() {return Vector2(event_data->mouseData.mousePos.x - event_data->mouseData.mouseLastPos.x, 
                                                    event_data->mouseData.mousePos.y - event_data->mouseData.mouseLastPos.y);}

                    // Get vertical scroll
                    inline float get_vertical_croll() {return event_data->mouseData.mScrollV;}

                    // Get scroll vector
                    inline Vector2 get_scroll() {return Vector2(event_data->mouseData.mScrollH, event_data->mouseData.mScrollV);}
            };

            struct EventContext {
                private:
                    EventData events;
                public:
                    inline EventData& get() {return events;}
                    inline void reload() {events.reload();}
            };

            struct RenderContext {
                private: 
                    Renderer* renderer;
                    bool is_locked;
                public:
                    void init(Renderer* renderer);

                    // Setting shaders and cameras
                    void set_default_camera(Camera& camera);
                    void set_default_shader(Shader& shader);
                    
                    void set_current_camera(Camera& camera);
                    void set_current_shader(Shader& shader);

                    void use_default_camera();
                    void use_default_shader();

                    void set_surface(Surface& surface);
                    void exit_surface();

                    void set_window(Window& window);

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
                    void draw(Surface& surface, Vector2 pos = {0.0, 0.0}, Vector2 scale = {1.0, 1.0}, float rotation = 0.0, Color color = Color::RGB(255, 255, 255));
                    void draw(Surface& surface, Rectangle targetRect, Vector2 pos = {0.0, 0.0}, Vector2 scale = {1.0, 1.0}, float rotation = 0.0, Color color = Color::RGB(255, 255, 255));

                    // Used to render text
                    void print(Font& font, std::string message, Vector2 pos = {0.0, 0.0}, Color color = Color::RGB(255, 255, 255), int padding = 4);
                    void draw_batch(); 

                    // Used to lock/unlock access to the renderer 
                    void lock() {is_locked = true;};
                    void unlock() {is_locked = false;};
            };

            struct UserDataContext {
                private:
                    std::map<std::string, void*> udata;
                public:
                    // Set user data under a given alias
                    inline void set_data(std::string name, void* data) { udata[name] = data; }
                    // Get user data stored at a certain alias
                    inline void* get_data(std::string name) { 
                        void* ptr = nullptr;
                        auto it = udata.find(name); 
                        if (it != udata.end()) {
                            ptr = it->second;
                        }
                        return ptr;
                    }
            };

            private:
            public:
                WindowContext window;
                TimerContext timer;
                CameraContext camera;
                KeyboardContext keyboard;
                MouseContext mouse;
                EventContext events;
                AudioContext audio;
                UserDataContext userdata;
                RenderContext renderer;

                Context();
                ~Context();
        };
    }

#endif