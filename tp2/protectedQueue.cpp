#include "protectedQueue.h"
#include <utility> 

void ProtectedQueue::push(Task task) {
    std::lock_guard<std::mutex> lock(mutex);
    this->internal.push(task);
    this->cond.notify_all();
}

Task ProtectedQueue::get_front_if_posibble() {
    std::unique_lock<std::mutex> lock(mutex);
    while (this->internal.empty()) {
        this->cond.wait(lock);
    }

    Task task = std::move(internal.front());
    internal.pop();
    return task;
}
