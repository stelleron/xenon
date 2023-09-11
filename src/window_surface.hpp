#pragma once
using namespace xenon;

class WindowSurface {
    private:
        Surface surface;
    public:
        WindowSurface();
        ~WindowSurface();

        void init(Context& ctx);
        void set(Context& ctx);
        void exit(Context& ctx);
        void exit_and_render(Context& ctx);
};