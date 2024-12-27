#ifndef XENON_THREAD
    #define XENON_THREAD

    #include <SDL2/SDL_thread.h>

    namespace xenon {
        // Thread function 
        using ThreadFunc = SDL_ThreadFunction;

        // A class for working with threads
        class Thread {
            private:
                SDL_Thread* id;
                ThreadFunc fn;
            public:
                Thread();
                Thread(ThreadFunc func);
                ~Thread();

                void init(ThreadFunc func);
                void start(void* args); 
                void wait();    
        };

        // Used to lock/unlock critical sections in threads
        class Mutex {
            private:
                SDL_mutex* mutex;
            public:
                Mutex();
                ~Mutex();

                void init();
                void lock();
                void unlock();
        };
    }
#endif