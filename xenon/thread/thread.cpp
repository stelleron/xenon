#include <thread/thread.hpp>

namespace xenon {
    // Thread class
    Thread::Thread() {
        id = 0;
    }

    Thread::Thread(ThreadFunc func) {
        id = 0;
        init(func);
    }

    Thread::~Thread() {

    }

    void Thread::init(ThreadFunc func) {
        this->fn = func;
    }

    void Thread::start(void* args) {
        // Call the function
        id = SDL_CreateThread(fn, "Thread", args);
    }

    void Thread::wait() {
        SDL_WaitThread(id, NULL);
    }
    
    // Mutex class
    Mutex::Mutex() {
        mutex = NULL;
    }

    Mutex::~Mutex() {
        if (mutex) 
            SDL_DestroyMutex(mutex);
    }

    void Mutex::init() {
        mutex = SDL_CreateMutex();
    }

    void Mutex::lock() {
        SDL_LockMutex(mutex);
    }

    void Mutex::unlock() {
        SDL_UnlockMutex(mutex);
    }
}