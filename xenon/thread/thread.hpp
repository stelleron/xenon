#ifndef XENON_THREAD
    #define XENON_THREAD

    #include <pthread.h>

    namespace xenon {
        // Thread function 
        using ThreadFunc = void*(*)(void*);

        // A class for working with threads
        class Thread {
            private:
                pthread_t id;
                ThreadFunc fn;
            public:
                Thread();
                Thread(ThreadFunc func);
                ~Thread();

                void init(ThreadFunc func);
                void start(void* args);      
        };
    }
#endif