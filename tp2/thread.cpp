#include <iostream>
#include <vector>
#include <thread>

#include "thread.h"


Thread::Thread() {}

void Thread::start() {
    this->thread = std::thread(
                            &Thread::run,
                            this);
}

void Thread::join() {
    thread.join();
}

Thread::Thread(Thread&& other) {
    if (this != &other) {
        this->thread = std::move(other.thread);
    }    
}

Thread& Thread::operator=(Thread&& other) {
    if (this != &other) {
        this->thread = std::move(other.thread);
    }
    return *this;
}


