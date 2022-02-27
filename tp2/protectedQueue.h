#include <queue>
#include <mutex>
#include <condition_variable>

#include "task.h"
#ifndef PROTECTEDQUEUE_H_
#define PROTECTEDQUEUE_H_


class ProtectedQueue {
    private:
    std::queue<Task> internal;
    std::mutex mutex;
    std::condition_variable cond;

    public:
    void push(Task task);
    Task get_front_if_posibble(); 
};

#endif //PROTECTEDQUEUE_H_
