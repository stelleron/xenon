#include "app/application.hpp"
#include "gfx/shader.hpp"
#include "utils/logger.hpp"
#include "time/timer.hpp"
#include "input/event_handler.hpp"
#include <thread>

namespace xenon {
    void build(Application& app) {
        LOG("Xenon: Building the application!");

        // Variable declarations
        AppConfig config;
        Context ctx;
        Timer internalClock;
        float deltatimeCap; // Used for capping frame speed
        Window window;
        Camera camera;
        Shader shader;
        Renderer renderer;

        // Game Loop
        // 1. INIT
        // First have the user modify the app config
        LOG("Xenon: Configuring the application!");
        app.config(config);

        LOG("Xenon: Initialising the application!");
        deltatimeCap = 1.0f/config.fps_cap;
        window.init(config);
        camera.dimensions = window.get_window_size();
        ctx.window.set(window);
        ctx.camera.set(camera);
        window.set_data(&ctx);
        set_event_handler(&ctx);


        ctx.renderer.init(&renderer);
        ctx.renderer.unlock();
            ctx.renderer.set_default_camera(camera);
            ctx.renderer.set_default_shader(shader);
            ctx.renderer.set_window(window);
        ctx.renderer.lock();    
        shader.load(0, 0);

        LOG("Xenon: Initialising the application!");
        app.init(ctx);

         // 2. UPDATE
        LOG("Xenon: Starting game loop!");
        do {
            ctx.events.reload();
            window.poll_events();

            if (window.is_active()) {
                // Update
                ctx.camera.set(camera);
                internalClock.reset();
                app.update(ctx);

                // Render
                window.fill();
                ctx.renderer.unlock();

                ctx.renderer.use_default_camera();
                ctx.renderer.use_default_shader();
                app.render(ctx);
                ctx.renderer.draw_batch();

                ctx.renderer.lock();
                window.swap_buffer();

                // End loop
                // Put thread to sleep to cap framerate
                if (internalClock.get_elapsed() < deltatimeCap) {
                    float sleepTime = deltatimeCap - internalClock.get_elapsed();
                    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long int>(sleepTime * 1000.0f)));
                }

                ctx.timer.set(internalClock.get_elapsed());
            }

        } while(!window.should_close());

        // 3. FINISH
        LOG("Xenon: Disposing the application!");
        app.finish();
        
    }
}