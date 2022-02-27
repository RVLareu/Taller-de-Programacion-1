#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>

#ifndef PROTECTEDQUEUE_H_
#define PROTECTEDQUEUE_H_


class ProtectedQueue {
    private:
    std::queue<std::string> internal;
    std::mutex mutex;
    std::condition_variable cond;

    public:
    void push(std::string msg);
    std::string get_front_if_posibble(); 
};

#endif //PROTECTEDQUEUE_H_
