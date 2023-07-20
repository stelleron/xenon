#include "glad/glad.h"
#include "window/window.hpp"
#include "utils/logger.hpp"

namespace xenon {
    Window::Window() {
        SDL_Init(SDL_INIT_VIDEO);
    }

    Window::~Window() {
        //Destroy window
        SDL_DestroyWindow( window );
        //Quit SDL subsystems
        SDL_Quit();
    }

    void Window::init(const AppConfig& config) {
        // First get window flags
        Uint32 window_flags = SDL_WINDOW_OPENGL;
        if (config.resizable) window_flags = window_flags | SDL_WINDOW_RESIZABLE;
        if (config.maximized) window_flags = window_flags | SDL_WINDOW_MAXIMIZED;
        if (config.fullscreen) window_flags = window_flags | SDL_WINDOW_FULLSCREEN;
        if (config.desktop_fullscreen) window_flags = window_flags | SDL_WINDOW_FULLSCREEN_DESKTOP;
        if (!config.decorated) window_flags = window_flags | SDL_WINDOW_BORDERLESS;
        if (config.focused) window_flags = window_flags | SDL_WINDOW_INPUT_FOCUS;

        // Then create window
        int window_pos_x = SDL_WINDOWPOS_UNDEFINED;
        int window_pos_y = SDL_WINDOWPOS_UNDEFINED;
        if (config.window_pos.x != -1) window_pos_x = config.window_pos.x;
        if (config.window_pos.y != -1) window_pos_y = config.window_pos.y;
        window = SDL_CreateWindow(config.title.c_str(), window_pos_x, window_pos_y,
                                  config.width, config.height, window_flags);

        // Initialise GLAD
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GLContext ctx = SDL_GL_CreateContext(window);
        gladLoadGLLoader(SDL_GL_GetProcAddress);

        // Set viewport
        int w,h;
        SDL_GetWindowSize(window, &w, &h);
        glViewport(0, 0, w, h);

        // Enable alpha blending  
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
        

        // And set the background color
        background_color = config.background_color;
        // And some other variables
        halt_while_hidden = config.halt_while_hidden;
        should_window_close = false;


        // And set window size limits
        Vector2 min_size = config.min_size;
        Vector2 max_size = config.max_size;
        if (min_size.x == -1 || min_size.y == -1) SDL_SetWindowMinimumSize(window, config.min_size.x, config.min_size.y);
        if (max_size.x == -1 || max_size.y == -1) SDL_SetWindowMaximumSize(window, config.max_size.x, config.max_size.y);

        // And opacity
        SDL_SetWindowOpacity(window, config.opacity);

        // Finally sent vsync
        if (config.vsync) SDL_GL_SetSwapInterval(1);
    } 

    void Window::poll_events() {
        SDL_Event event;
        while( SDL_PollEvent(&event) ) {} 
    }

    void Window::close() {
        should_window_close = true;
        LOG("Window: Closing window!");
    }

    bool Window::should_close() {
        return should_window_close;
    }

    bool Window::is_active() {
        #ifdef ENABLE_XENON_LOGGER
            static bool loggedActive = false;
            static bool loggedInactive = false;
        #endif

        if (halt_while_hidden) {
            if (SDL_GetWindowFlags(window) & SDL_WINDOW_HIDDEN) {
                #ifdef ENABLE_XENON_LOGGER
                    if (!loggedActive) {
                        loggedActive = true;
                        loggedInactive = false;
                        LOG("Window: Is currently hidden and inactive!");
                    }
                #endif
                return false;
            }
            else {
                #ifdef ENABLE_XENON_LOGGER
                    if (!loggedInactive) {
                        loggedInactive = true;
                        loggedActive = false;
                        LOG("Window: Is currently active!");
                    }
                #endif
                return true;
            }
        }
        return true;
    }

    void Window::fill() {
        glClearColor(COLOR_TO_FLOAT(background_color));
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Window::swap_buffer() {
        SDL_GL_SwapWindow(window);
    }

    void Window::set_data(void* data) {
        SDL_SetWindowData(window, "userdata", data);
    }

    void* Window::get_data() {
        return SDL_GetWindowData(window, "userdata");
    }

    void Window::update_title(const char* title) {SDL_SetWindowTitle(window, title);}
    Vector2 Window::get_window_size() {int width, height; SDL_GetWindowSize(window, &width, &height); return Vector2(width, height);}
    Vector2 Window::get_framebuffer_size() {
        int width, height;  
        SDL_GL_GetDrawableSize(window, &width, &height); 
        return Vector2(width, height);
    }
    void Window::set_min_size(Vector2 minDim) {SDL_SetWindowMinimumSize(window, minDim.x, minDim.y);}
    void Window::set_max_size(Vector2 maxDim) {SDL_SetWindowMaximumSize(window, maxDim.x, maxDim.y);}
    void Window::set_window_pos(Vector2 windowPos) {SDL_SetWindowPosition(window, windowPos.x, windowPos.y);}
    void Window::set_window_size(Vector2 windowSize) {SDL_SetWindowSize(window, windowSize.x, windowSize.y);}
    void Window::restore() {SDL_RestoreWindow(window);}
    void Window::minimize() {SDL_MinimizeWindow(window);}; 
    void Window::maximize() {SDL_MaximizeWindow(window);}
}