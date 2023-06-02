#ifndef XENON_APPLICATION
    #define XENON_APPLICATION

    #include "app/app_config.hpp"
    #include "context/context.hpp"

    namespace xenon {
        // Used to create an application
        class Application {
            public:
                virtual void config(AppConfig& config) = 0;
                virtual void init(Context& ctx) = 0;
                virtual void update(Context& ctx) = 0;
                virtual void render(Context& ctx) = 0;
                virtual void finish() = 0; 
        };

        // Build the application
        void build(Application& app);
    }
#endif