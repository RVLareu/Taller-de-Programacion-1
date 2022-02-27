#include <vector>
#include <tuple>
#include <string>
#include <utility>
#include "worker.h"


Worker::Worker(PartialResults& results,
                 TaskManager& taskManager,
                  BinaryReader& binaryReader,
                  ProtectedQueue& tasksQueue) : 
                    results(results),
                        taskManager(taskManager),
                             binaryReader(binaryReader),
                             tasksQueue(tasksQueue) {}


void Worker::run(){
        while (1) {
            Task task = std::move(taskManager.get_task(tasksQueue));
            if (task.is_end_token()) {
                break;
            }
            task.solve(binaryReader);
            std::tuple<int, uint16_t, int, std::string> r = std::move(task.get_result());
            results.push_back(std::move(r));
        } 
}
