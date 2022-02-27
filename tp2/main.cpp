#include <tuple>
#include <thread>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <cstring>
#include <stdexcept>
#include <climits>


#include "worker.h"


int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("invalid amount argc, %d received", argc);
        return 1;
    }
    std::string dataset = argv[1];
    int columns = (int) (std::stoi(argv[2]));
    int workers = (int) std::stoi(argv[3]);

    PartialResults partialResults;
    TaskManager taskManager;
    ProtectedQueue tasksQueue;
    taskManager.create_partitions(columns, workers, std::ref(tasksQueue));
    BinaryReader binaryReader(dataset);
    std::vector<Thread*> threads;
    threads.reserve(workers);
    
    for (int i = 0; i < workers; i++) {
        Thread *t = new Worker(std::ref(partialResults),
                         std::ref(taskManager),
                        std::ref(binaryReader),
                         std::ref(tasksQueue));
        t->start();
        threads.emplace_back(t);
    }
    for (int i = 0; i < workers; ++i) {
        threads[i]->join();
        delete threads[i];
    }
    taskManager.solve(std::ref(partialResults));
    return 0;
}

