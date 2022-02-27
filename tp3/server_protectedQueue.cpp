#include "protectedQueue.h"

void ProtectedQueue::push(std::string msg) {
    std::lock_guard<std::mutex> lock(mutex);
    this->internal.push(msg);
    this->cond.notify_all();
}

std::string ProtectedQueue::get_front_if_posibble() {
    std::unique_lock<std::mutex> lock(mutex);
    while (this->internal.empty()) {
        this->cond.wait(lock);
    }

    std::string msg = std::move(internal.front());
    internal.pop();
    return msg;
}
