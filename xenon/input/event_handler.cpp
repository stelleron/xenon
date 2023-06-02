#include "input/event_handler.hpp"
#include "context/context.hpp"
#include <SDL2/SDL.h>
#include "glad/glad.h"

// Macro defines
#define KEYDOWN_MAP_FUNC(sdl_key, xenon_key) case sdl_key: ctx->events.get().keyboardData.keyPressed[xenon_key - 1] = true; break
#define KEYUP_MAP_FUNC(sdl_key, xenon_key) case sdl_key: ctx->events.get().keyboardData.keyPressed[xenon_key - 1] = false; break
#define BUTTONDOWN_MAP_FUNC(sdl_button, xenon_button) case sdl_button: ctx->events.get().mouseData.buttonPressed[xenon_button - 1] = true; break
#define BUTTONUP_MAP_FUNC(sdl_button, xenon_button) case sdl_button: ctx->events.get().mouseData.buttonPressed[xenon_button - 1] = false; break

namespace xenon {
    void window_event_func(Context* ctx, SDL_Event* event) {
        // Handle window events
        switch (event->window.event) {
            case SDL_WINDOWEVENT_RESIZED: 
                ctx->events.get().windowData.wasResized = true;
                (ctx->camera.get())->dimensions = ctx->window.get_size();
                break;
            case SDL_WINDOWEVENT_MOVED:
                ctx->events.get().windowData.windowPos = Vector2(event->window.data1,event->window.data2);
                break;
            case SDL_WINDOWEVENT_MINIMIZED:
                ctx->events.get().windowData.isMinimized = true;
                break;
            case SDL_WINDOWEVENT_MAXIMIZED:
                ctx->events.get().windowData.isMaximized = true;
                break;
            case SDL_WINDOWEVENT_SHOWN:
                ctx->events.get().windowData.isMinimized = false;
                break;
            case SDL_WINDOWEVENT_RESTORED:
                ctx->events.get().windowData.isMinimized = false;
                ctx->events.get().windowData.isMaximized = false;
                break;
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                ctx->events.get().windowData.inFocus = true;
                break;
            case SDL_WINDOWEVENT_FOCUS_LOST:
                ctx->events.get().windowData.inFocus = false;
                break;
            default: break;
        }
    }

    void keydown_event_func(Context* ctx, SDL_Event* event) {
        switch(event->key.keysym.sym) {
            KEYDOWN_MAP_FUNC(SDLK_SPACE, Key::Space);
            KEYDOWN_MAP_FUNC(SDLK_QUOTE, Key::Apostrophe);
            KEYDOWN_MAP_FUNC(SDLK_COMMA, Key::Comma);
            KEYDOWN_MAP_FUNC(SDLK_MINUS, Key::Minus);
            KEYDOWN_MAP_FUNC(SDLK_PERIOD, Key::Period);
            KEYDOWN_MAP_FUNC(SDLK_SLASH, Key::Slash);
            KEYDOWN_MAP_FUNC(SDLK_0, Key::Zero);
            KEYDOWN_MAP_FUNC(SDLK_1, Key::One);
            KEYDOWN_MAP_FUNC(SDLK_2, Key::Two);
            KEYDOWN_MAP_FUNC(SDLK_3, Key::Three);
            KEYDOWN_MAP_FUNC(SDLK_4, Key::Four);
            KEYDOWN_MAP_FUNC(SDLK_5, Key::Five);
            KEYDOWN_MAP_FUNC(SDLK_6, Key::Six);
            KEYDOWN_MAP_FUNC(SDLK_7, Key::Seven);
            KEYDOWN_MAP_FUNC(SDLK_8, Key::Eight);
            KEYDOWN_MAP_FUNC(SDLK_9, Key::Nine);
            KEYDOWN_MAP_FUNC(SDLK_SEMICOLON, Key::Semicolon);
            KEYDOWN_MAP_FUNC(SDLK_EQUALS, Key::Equal);
            KEYDOWN_MAP_FUNC(SDLK_a, Key::A);
            KEYDOWN_MAP_FUNC(SDLK_b, Key::B);
            KEYDOWN_MAP_FUNC(SDLK_c, Key::C);
            KEYDOWN_MAP_FUNC(SDLK_d, Key::D);
            KEYDOWN_MAP_FUNC(SDLK_e, Key::E);
            KEYDOWN_MAP_FUNC(SDLK_f, Key::F);
            KEYDOWN_MAP_FUNC(SDLK_g, Key::G);
            KEYDOWN_MAP_FUNC(SDLK_h, Key::H);
            KEYDOWN_MAP_FUNC(SDLK_i, Key::I);
            KEYDOWN_MAP_FUNC(SDLK_j, Key::J);
            KEYDOWN_MAP_FUNC(SDLK_k, Key::K);
            KEYDOWN_MAP_FUNC(SDLK_l, Key::L);
            KEYDOWN_MAP_FUNC(SDLK_m, Key::M);
            KEYDOWN_MAP_FUNC(SDLK_n, Key::N);
            KEYDOWN_MAP_FUNC(SDLK_o, Key::O);
            KEYDOWN_MAP_FUNC(SDLK_p, Key::P);
            KEYDOWN_MAP_FUNC(SDLK_q, Key::Q);
            KEYDOWN_MAP_FUNC(SDLK_r, Key::R);
            KEYDOWN_MAP_FUNC(SDLK_s, Key::S);
            KEYDOWN_MAP_FUNC(SDLK_t, Key::T);
            KEYDOWN_MAP_FUNC(SDLK_u, Key::U);
            KEYDOWN_MAP_FUNC(SDLK_v, Key::V);
            KEYDOWN_MAP_FUNC(SDLK_w, Key::W);
            KEYDOWN_MAP_FUNC(SDLK_x, Key::X);
            KEYDOWN_MAP_FUNC(SDLK_y, Key::Y);
            KEYDOWN_MAP_FUNC(SDLK_z, Key::Z);
            KEYDOWN_MAP_FUNC(SDLK_LEFTBRACKET, Key::LeftBracket);
            KEYDOWN_MAP_FUNC(SDLK_BACKSLASH, Key::Backslash);
            KEYDOWN_MAP_FUNC(SDLK_RIGHTBRACKET, Key::RightBracket);
            KEYDOWN_MAP_FUNC(SDLK_BACKQUOTE, Key::GraveAccent);
            KEYDOWN_MAP_FUNC(SDLK_ESCAPE, Key::Escape);
            KEYDOWN_MAP_FUNC(SDLK_RETURN, Key::Enter);
            KEYDOWN_MAP_FUNC(SDLK_TAB, Key::Tab);
            KEYDOWN_MAP_FUNC(SDLK_BACKSPACE, Key::Backspace);
            KEYDOWN_MAP_FUNC(SDLK_INSERT, Key::Insert);
            KEYDOWN_MAP_FUNC(SDLK_DELETE, Key::Delete);
            KEYDOWN_MAP_FUNC(SDLK_RIGHT, Key::Right);
            KEYDOWN_MAP_FUNC(SDLK_LEFT, Key::Left);
            KEYDOWN_MAP_FUNC(SDLK_DOWN, Key::Down);
            KEYDOWN_MAP_FUNC(SDLK_UP, Key::Up);
            KEYDOWN_MAP_FUNC(SDLK_PAGEUP, Key::PageUp);
            KEYDOWN_MAP_FUNC(SDLK_PAGEDOWN, Key::PageDown);
            KEYDOWN_MAP_FUNC(SDLK_HOME, Key::Home);
            KEYDOWN_MAP_FUNC(SDLK_END, Key::End);
            KEYDOWN_MAP_FUNC(SDLK_CAPSLOCK, Key::CapsLock);
            KEYDOWN_MAP_FUNC(SDLK_SCROLLLOCK, Key::ScrollLock);
            KEYDOWN_MAP_FUNC(SDLK_NUMLOCKCLEAR, Key::NumLock);
            KEYDOWN_MAP_FUNC(SDLK_PRINTSCREEN, Key::PrintScreen);
            KEYDOWN_MAP_FUNC(SDLK_PAUSE, Key::Pause);
            KEYDOWN_MAP_FUNC(SDLK_F1, Key::F1);
            KEYDOWN_MAP_FUNC(SDLK_F2, Key::F2);
            KEYDOWN_MAP_FUNC(SDLK_F3, Key::F3);
            KEYDOWN_MAP_FUNC(SDLK_F4, Key::F4);
            KEYDOWN_MAP_FUNC(SDLK_F5, Key::F5);
            KEYDOWN_MAP_FUNC(SDLK_F6, Key::F6);
            KEYDOWN_MAP_FUNC(SDLK_F7, Key::F7);
            KEYDOWN_MAP_FUNC(SDLK_F8, Key::F8);
            KEYDOWN_MAP_FUNC(SDLK_F9, Key::F9);
            KEYDOWN_MAP_FUNC(SDLK_F10, Key::F10);
            KEYDOWN_MAP_FUNC(SDLK_F11, Key::F11);
            KEYDOWN_MAP_FUNC(SDLK_F12, Key::F12);
            KEYDOWN_MAP_FUNC(SDLK_F13, Key::F13);
            KEYDOWN_MAP_FUNC(SDLK_F14, Key::F14);
            KEYDOWN_MAP_FUNC(SDLK_F15, Key::F15);
            KEYDOWN_MAP_FUNC(SDLK_F16, Key::F16);
            KEYDOWN_MAP_FUNC(SDLK_F17, Key::F17);
            KEYDOWN_MAP_FUNC(SDLK_F18, Key::F18);
            KEYDOWN_MAP_FUNC(SDLK_F19, Key::F19);
            KEYDOWN_MAP_FUNC(SDLK_F20, Key::F20);
            KEYDOWN_MAP_FUNC(SDLK_F21, Key::F21);
            KEYDOWN_MAP_FUNC(SDLK_F22, Key::F22);
            KEYDOWN_MAP_FUNC(SDLK_F23, Key::F23);
            KEYDOWN_MAP_FUNC(SDLK_F24, Key::F24);
            KEYDOWN_MAP_FUNC(SDLK_KP_0, Key::KP0);
            KEYDOWN_MAP_FUNC(SDLK_KP_1, Key::KP1);
            KEYDOWN_MAP_FUNC(SDLK_KP_2, Key::KP2);
            KEYDOWN_MAP_FUNC(SDLK_KP_3, Key::KP3);
            KEYDOWN_MAP_FUNC(SDLK_KP_4, Key::KP4);
            KEYDOWN_MAP_FUNC(SDLK_KP_5, Key::KP5);
            KEYDOWN_MAP_FUNC(SDLK_KP_6, Key::KP6);
            KEYDOWN_MAP_FUNC(SDLK_KP_7, Key::KP7);
            KEYDOWN_MAP_FUNC(SDLK_KP_8, Key::KP8);
            KEYDOWN_MAP_FUNC(SDLK_KP_9, Key::KP9);
            KEYDOWN_MAP_FUNC(SDLK_KP_DECIMAL, Key::KPDecimal);
            KEYDOWN_MAP_FUNC(SDLK_KP_DIVIDE, Key::KPDivide);
            KEYDOWN_MAP_FUNC(SDLK_KP_MULTIPLY, Key::KPMultiply);
            KEYDOWN_MAP_FUNC(SDLK_KP_MINUS, Key::KPSubtract);
            KEYDOWN_MAP_FUNC(SDLK_KP_PLUS, Key::KPAdd);
            KEYDOWN_MAP_FUNC(SDLK_KP_ENTER, Key::KPEnter);
            KEYDOWN_MAP_FUNC(SDLK_KP_EQUALS, Key::KPEqual);
            KEYDOWN_MAP_FUNC(SDLK_LSHIFT, Key::LeftShift);
            KEYDOWN_MAP_FUNC(SDLK_LCTRL, Key::LeftControl);
            KEYDOWN_MAP_FUNC(SDLK_LALT, Key::LeftAlt);
            KEYDOWN_MAP_FUNC(SDLK_RSHIFT, Key::RightShift);
            KEYDOWN_MAP_FUNC(SDLK_RCTRL, Key::RightControl);
            KEYDOWN_MAP_FUNC(SDLK_RALT, Key::RightAlt);
            KEYDOWN_MAP_FUNC(SDLK_MENU, Key::Menu);
            default: break;
        };
    }

    void keyup_event_func(Context* ctx, SDL_Event* event) {
        switch(event->key.keysym.sym) {
            KEYUP_MAP_FUNC(SDLK_SPACE, Key::Space);
            KEYUP_MAP_FUNC(SDLK_QUOTE, Key::Apostrophe);
            KEYUP_MAP_FUNC(SDLK_COMMA, Key::Comma);
            KEYUP_MAP_FUNC(SDLK_MINUS, Key::Minus);
            KEYUP_MAP_FUNC(SDLK_PERIOD, Key::Period);
            KEYUP_MAP_FUNC(SDLK_SLASH, Key::Slash);
            KEYUP_MAP_FUNC(SDLK_0, Key::Zero);
            KEYUP_MAP_FUNC(SDLK_1, Key::One);
            KEYUP_MAP_FUNC(SDLK_2, Key::Two);
            KEYUP_MAP_FUNC(SDLK_3, Key::Three);
            KEYUP_MAP_FUNC(SDLK_4, Key::Four);
            KEYUP_MAP_FUNC(SDLK_5, Key::Five);
            KEYUP_MAP_FUNC(SDLK_6, Key::Six);
            KEYUP_MAP_FUNC(SDLK_7, Key::Seven);
            KEYUP_MAP_FUNC(SDLK_8, Key::Eight);
            KEYUP_MAP_FUNC(SDLK_9, Key::Nine);
            KEYUP_MAP_FUNC(SDLK_SEMICOLON, Key::Semicolon);
            KEYUP_MAP_FUNC(SDLK_EQUALS, Key::Equal);
            KEYUP_MAP_FUNC(SDLK_a, Key::A);
            KEYUP_MAP_FUNC(SDLK_b, Key::B);
            KEYUP_MAP_FUNC(SDLK_c, Key::C);
            KEYUP_MAP_FUNC(SDLK_d, Key::D);
            KEYUP_MAP_FUNC(SDLK_e, Key::E);
            KEYUP_MAP_FUNC(SDLK_f, Key::F);
            KEYUP_MAP_FUNC(SDLK_g, Key::G);
            KEYUP_MAP_FUNC(SDLK_h, Key::H);
            KEYUP_MAP_FUNC(SDLK_i, Key::I);
            KEYUP_MAP_FUNC(SDLK_j, Key::J);
            KEYUP_MAP_FUNC(SDLK_k, Key::K);
            KEYUP_MAP_FUNC(SDLK_l, Key::L);
            KEYUP_MAP_FUNC(SDLK_m, Key::M);
            KEYUP_MAP_FUNC(SDLK_n, Key::N);
            KEYUP_MAP_FUNC(SDLK_o, Key::O);
            KEYUP_MAP_FUNC(SDLK_p, Key::P);
            KEYUP_MAP_FUNC(SDLK_q, Key::Q);
            KEYUP_MAP_FUNC(SDLK_r, Key::R);
            KEYUP_MAP_FUNC(SDLK_s, Key::S);
            KEYUP_MAP_FUNC(SDLK_t, Key::T);
            KEYUP_MAP_FUNC(SDLK_u, Key::U);
            KEYUP_MAP_FUNC(SDLK_v, Key::V);
            KEYUP_MAP_FUNC(SDLK_w, Key::W);
            KEYUP_MAP_FUNC(SDLK_x, Key::X);
            KEYUP_MAP_FUNC(SDLK_y, Key::Y);
            KEYUP_MAP_FUNC(SDLK_z, Key::Z);
            KEYUP_MAP_FUNC(SDLK_LEFTBRACKET, Key::LeftBracket);
            KEYUP_MAP_FUNC(SDLK_BACKSLASH, Key::Backslash);
            KEYUP_MAP_FUNC(SDLK_RIGHTBRACKET, Key::RightBracket);
            KEYUP_MAP_FUNC(SDLK_BACKQUOTE, Key::GraveAccent);
            KEYUP_MAP_FUNC(SDLK_ESCAPE, Key::Escape);
            KEYUP_MAP_FUNC(SDLK_RETURN, Key::Enter);
            KEYUP_MAP_FUNC(SDLK_TAB, Key::Tab);
            KEYUP_MAP_FUNC(SDLK_BACKSPACE, Key::Backspace);
            KEYUP_MAP_FUNC(SDLK_INSERT, Key::Insert);
            KEYUP_MAP_FUNC(SDLK_DELETE, Key::Delete);
            KEYUP_MAP_FUNC(SDLK_RIGHT, Key::Right);
            KEYUP_MAP_FUNC(SDLK_LEFT, Key::Left);
            KEYUP_MAP_FUNC(SDLK_DOWN, Key::Down);
            KEYUP_MAP_FUNC(SDLK_UP, Key::Up);
            KEYUP_MAP_FUNC(SDLK_PAGEUP, Key::PageUp);
            KEYUP_MAP_FUNC(SDLK_PAGEDOWN, Key::PageDown);
            KEYUP_MAP_FUNC(SDLK_HOME, Key::Home);
            KEYUP_MAP_FUNC(SDLK_END, Key::End);
            KEYUP_MAP_FUNC(SDLK_CAPSLOCK, Key::CapsLock);
            KEYUP_MAP_FUNC(SDLK_SCROLLLOCK, Key::ScrollLock);
            KEYUP_MAP_FUNC(SDLK_NUMLOCKCLEAR, Key::NumLock);
            KEYUP_MAP_FUNC(SDLK_PRINTSCREEN, Key::PrintScreen);
            KEYUP_MAP_FUNC(SDLK_PAUSE, Key::Pause);
            KEYUP_MAP_FUNC(SDLK_F1, Key::F1);
            KEYUP_MAP_FUNC(SDLK_F2, Key::F2);
            KEYUP_MAP_FUNC(SDLK_F3, Key::F3);
            KEYUP_MAP_FUNC(SDLK_F4, Key::F4);
            KEYUP_MAP_FUNC(SDLK_F5, Key::F5);
            KEYUP_MAP_FUNC(SDLK_F6, Key::F6);
            KEYUP_MAP_FUNC(SDLK_F7, Key::F7);
            KEYUP_MAP_FUNC(SDLK_F8, Key::F8);
            KEYUP_MAP_FUNC(SDLK_F9, Key::F9);
            KEYUP_MAP_FUNC(SDLK_F10, Key::F10);
            KEYUP_MAP_FUNC(SDLK_F11, Key::F11);
            KEYUP_MAP_FUNC(SDLK_F12, Key::F12);
            KEYUP_MAP_FUNC(SDLK_F13, Key::F13);
            KEYUP_MAP_FUNC(SDLK_F14, Key::F14);
            KEYUP_MAP_FUNC(SDLK_F15, Key::F15);
            KEYUP_MAP_FUNC(SDLK_F16, Key::F16);
            KEYUP_MAP_FUNC(SDLK_F17, Key::F17);
            KEYUP_MAP_FUNC(SDLK_F18, Key::F18);
            KEYUP_MAP_FUNC(SDLK_F19, Key::F19);
            KEYUP_MAP_FUNC(SDLK_F20, Key::F20);
            KEYUP_MAP_FUNC(SDLK_F21, Key::F21);
            KEYUP_MAP_FUNC(SDLK_F22, Key::F22);
            KEYUP_MAP_FUNC(SDLK_F23, Key::F23);
            KEYUP_MAP_FUNC(SDLK_F24, Key::F24);
            KEYUP_MAP_FUNC(SDLK_KP_0, Key::KP0);
            KEYUP_MAP_FUNC(SDLK_KP_1, Key::KP1);
            KEYUP_MAP_FUNC(SDLK_KP_2, Key::KP2);
            KEYUP_MAP_FUNC(SDLK_KP_3, Key::KP3);
            KEYUP_MAP_FUNC(SDLK_KP_4, Key::KP4);
            KEYUP_MAP_FUNC(SDLK_KP_5, Key::KP5);
            KEYUP_MAP_FUNC(SDLK_KP_6, Key::KP6);
            KEYUP_MAP_FUNC(SDLK_KP_7, Key::KP7);
            KEYUP_MAP_FUNC(SDLK_KP_8, Key::KP8);
            KEYUP_MAP_FUNC(SDLK_KP_9, Key::KP9);
            KEYUP_MAP_FUNC(SDLK_KP_DECIMAL, Key::KPDecimal);
            KEYUP_MAP_FUNC(SDLK_KP_DIVIDE, Key::KPDivide);
            KEYUP_MAP_FUNC(SDLK_KP_MULTIPLY, Key::KPMultiply);
            KEYUP_MAP_FUNC(SDLK_KP_MINUS, Key::KPSubtract);
            KEYUP_MAP_FUNC(SDLK_KP_PLUS, Key::KPAdd);
            KEYUP_MAP_FUNC(SDLK_KP_ENTER, Key::KPEnter);
            KEYUP_MAP_FUNC(SDLK_KP_EQUALS, Key::KPEqual);
            KEYUP_MAP_FUNC(SDLK_LSHIFT, Key::LeftShift);
            KEYUP_MAP_FUNC(SDLK_LCTRL, Key::LeftControl);
            KEYUP_MAP_FUNC(SDLK_LALT, Key::LeftAlt);
            KEYUP_MAP_FUNC(SDLK_RSHIFT, Key::RightShift);
            KEYUP_MAP_FUNC(SDLK_RCTRL, Key::RightControl);
            KEYUP_MAP_FUNC(SDLK_RALT, Key::RightAlt);
            KEYUP_MAP_FUNC(SDLK_MENU, Key::Menu);
            default: break;
        }
    }

    void mousemove_event_func(Context* ctx, SDL_Event* event) {
        ctx->events.get().mouseData.mousePos = Vector2(event->motion.x, event->motion.y);
    } 

    void mousebtndown_event_func(Context* ctx, SDL_Event* event) {
        switch (event->button.button) {
            BUTTONDOWN_MAP_FUNC(SDL_BUTTON_LEFT, MouseButton::LeftButton);
            BUTTONDOWN_MAP_FUNC(SDL_BUTTON_MIDDLE, MouseButton::MiddleButton);
            BUTTONDOWN_MAP_FUNC(SDL_BUTTON_RIGHT, MouseButton::RightButton);
            break;
        }
    }

    void mousebtnup_event_func(Context* ctx, SDL_Event* event) {
        switch (event->button.button) {
            BUTTONUP_MAP_FUNC(SDL_BUTTON_LEFT, MouseButton::LeftButton);
            BUTTONUP_MAP_FUNC(SDL_BUTTON_MIDDLE, MouseButton::MiddleButton);
            BUTTONUP_MAP_FUNC(SDL_BUTTON_RIGHT, MouseButton::RightButton);
            break;
        }
    }

    void mousewheel_event_func(Context* ctx, SDL_Event* event) {
        (ctx->events.get()).mouseData.mScrollH = event->wheel.x;
        (ctx->events.get()).mouseData.mScrollV = event->wheel.y;
    }

    void textinput_event_func(Context* ctx, SDL_Event* event) {
        ctx->events.get().keyboardData.charQueue.push(event->text.text[0]);
    }


    int event_handler_func(void *userdata, SDL_Event *event) {
        Context* ctx = (Context*)userdata;
        // Handle all event types
        switch (event->type) {
            case SDL_QUIT: ctx->window.close(); break;
            case SDL_WINDOWEVENT: window_event_func(ctx, event); break;
            case SDL_KEYDOWN: keydown_event_func(ctx, event); break;
            case SDL_KEYUP: keyup_event_func(ctx, event); break;
            case SDL_TEXTINPUT: textinput_event_func(ctx, event); break;
            case SDL_MOUSEMOTION: mousemove_event_func(ctx, event); break;
            case SDL_MOUSEBUTTONDOWN: mousebtndown_event_func(ctx, event); break;
            case SDL_MOUSEBUTTONUP: mousebtnup_event_func(ctx, event); break;
            case SDL_MOUSEWHEEL: mousewheel_event_func(ctx, event); break;
            default: break;
        }

        // Also resize glViewport no matter what
        Vector2 size = ctx->window.get_frame_size();
        int w = size.x;
        int h = size.y;
        glViewport(0, 0, w, h);
        return 0;
    }

    void set_event_handler(void* userdata) {
        SDL_AddEventWatch(event_handler_func, userdata);
    }
}