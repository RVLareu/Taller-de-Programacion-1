#include <string> 
#include <vector>
#include <utility>
#include <map>
#include <sstream>
#include <iostream>
#include "taskManager.h"

/*
    -tasksQueue: queue with tasks made from stdin
    -number_columns: of the dataset (info needed by tasks)
    creates many tasks (based on partition rows) and queues them in a tasks queue.
*/
TaskManager::TaskManager() {}


void TaskManager::create_partitions(int number_columns,
                                     int workers,
                                      ProtectedQueue& tasksQueue) {
    std::string line;
    std::vector<std::string> values;
    int id = 0;
    while (std::getline(std::cin, line)) {
        values = split_line(line);
        int start = std::stoi(values[0]);
        int end = std::stoi(values[1]);
        int partition = std::stoi(values[2]);
        while (start < end) {
            if (start + partition > end) {
                Task task(start,
                        end,
                            std::stoi(values[3]),
                                number_columns,
                                    std::ref(values[4]),
                                    id,
                                    0);
                tasksQueue.push(std::move(task));
                break;
            }
            Task task(start,
                start + partition,
                    std::stoi(values[3]),
                        number_columns,
                            std::ref(values[4]),
                            id,
                            0);
            tasksQueue.push(std::move(task));
            start = start + partition;
        }
        id++;
    }
    for (int i = 0; i < workers; i++) {
        Task task(0, 0, 0, 0, "end", 0, 1);
        tasksQueue.push(std::move(task));
    }
}

/*given a std::string line, it splits it based on the character ' '. Returns an
  array with strings
*/
const std::vector<std::string> TaskManager::split_line(std::string line) {
    std::vector<std::string> tokens;
    std::stringstream ss(std::move(line));
    std::string token;
    while (ss >> token) {
        tokens.push_back(token.c_str());
    }
    return std::ref(tokens);
}

/*  returns task from the front of the queue after checking
.   if queue is empty or not.
    Finally it pops it from the queue.
*/
Task TaskManager::get_task(ProtectedQueue& tasksQueue) {
    return tasksQueue.get_front_if_posibble();
}


void TaskManager::solve(PartialResults& results) {
    std::map<int, std::string> id_op;
    for (unsigned int i = 0; i < results.size(); i++) {
        id_op[std::get<2>(results.at(i))] = std::get<3>(results.at(i));
    }

    for (unsigned int n = 0; n < id_op.size(); n++) {
        uint16_t result_max = 0;
        uint16_t result_min = 32768;
        uint16_t result = 0;
        int numbers = 0;
        for (unsigned int i = 0; i < results.size(); i++) {
            int k = n;
            if (std::get<2>(results.at(i)) == k) {
                if (std::get<3>(results.at(i)) == "max") {
                    result_max = std::get<1>(results.at(i)) > result_max ?
                        std::get<1>(results.at(i)) : result_max;
                } else if (std::get<3>(results.at(i)) == "mean") {
                    result += std::get<1>(results.at(i));
                    numbers += std::get<0>(results.at(i));
                } else if (std::get<3>(results.at(i)) == "min") {
                    result_min = std::get<1>(results.at(i)) < result_min ?
                        std::get<1>(results.at(i)) : result_min;
                } else {
                    result += std::get<1>(results.at(i));
                }
            }
        }
        this->print_results(std::ref(id_op), result_max, result_min, result, numbers, n);  
    }
}
 void TaskManager::print_results(const std::map<int, std::string>& id_op,
                         uint16_t result_max,
                            uint16_t result_min,
                                uint16_t result,
                                    uint16_t numbers,
                                     unsigned int n) {
    if (id_op.at(n) == "max") {
        printf("%d\n",result_max);
    } else if (id_op.at(n) == "min") {
        printf("%d\n",result_min);
    } else if (id_op.at(n) == "sum") {
        printf("%d\n",result);
    } else if (id_op.at(n) == "mean") {
        printf("%d/%d\n", result, numbers);
    }
 }

TaskManager::~TaskManager() {
}
