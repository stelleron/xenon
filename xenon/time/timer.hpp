#ifndef XENON_TIMER
    #define XENON_TIMER
    #include <chrono>

    namespace xenon {
        using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
        // Used to create a timer object
        class Timer {
            private:
                TimePoint startTime;
            public:
                // Constructor
                Timer();

                // Reset the timer
                void reset();

                // Get the elapsed time
                float get_elapsed();

                // Get the elapsed time in milliseconds
                float get_elapsed_millis();
        };
    }
#endif