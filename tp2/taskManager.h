#include <string>
#include <vector>
#include "protectedQueue.h"
#include "partialResults.h"
#include <map>
#ifndef TASKMANAGER_H_
#define TASKMANAGER_H_

class TaskManager {
    private:
    /*Splits a line*/
    const std::vector<std::string> split_line(std::string line);
    void print_results(const std::map<int, std::string>& id_op,
                         uint16_t result_max,
                            uint16_t result_min,
                                uint16_t result,
                                    uint16_t numbers,
                                        unsigned int n);

    public:
    TaskManager();
    void create_partitions(int number_columns, int workers, ProtectedQueue& protectedQueue);
    /*returns task from the queue*/
    Task get_task(ProtectedQueue& tasksQueue);

    void solve(PartialResults &results);

    ~TaskManager();
};

#endif  //  TASKMANAGER_H_
