#include <thread/thread.hpp>

namespace xenon {
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
        pthread_create(&id, NULL, this->fn, args);
        pthread_join(id, NULL);
    }
}