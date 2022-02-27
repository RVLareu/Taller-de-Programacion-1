#include <vector>
#include <string>
#include "task.h"
#include <algorithm>
#include <utility>

Task::Task(int start_range,
                 int end_range,
                    int column,
                         int number_columns,
                             std::string op, 
                             int id,
                             int end_token) : start_range(start_range),
                             end_range(end_range),
                             column(column),
                             number_columns(number_columns),
                              op(std::move(op)),
                             id(id), end_token(end_token) { 
}

Task::Task(Task&& other) {
    if (this != &other) {
        this->op = std::move(other.op);
        this->start_range = std::move(other.start_range);
        this->end_range =  std::move(other.end_range);
        this->column =  std::move(other.column);
        this->number_columns =  std::move(other.number_columns);
        this->id =  std::move(other.id);
        this->end_token =  std::move(other.end_token);
    }
}


Task &Task::operator=(Task &&other) {
    if (this != &other) {
        this->op = std::move(other.op);
        this->start_range = std::move(other.start_range);
        this->end_range =  std::move(other.end_range);
        this->column =  std::move(other.column);
        this->number_columns =  std::move(other.number_columns);
        this->id =  std::move(other.id);
        this->end_token =  std::move(other.end_token);
    }
    return *this;
}


bool Task::is_end_token() {
    return this->end_token;
} 



const std::tuple<int, int> Task::sum(std::vector<uint16_t>const &values) {
    std::tuple<int, int> result;
    int sum = 0;
    int numbers = 0;
    for (uint16_t number : values) {
        sum += number;
        numbers += 1;    
    }
    std::get<0>(result) = numbers;
    std::get<1>(result) = sum;
    return result;
}

const std::tuple<int, int> Task::min(std::vector<uint16_t> const &values) {
    std::tuple<int, int> result;
    uint16_t min = 32768;
    int numbers = 0;
    for (uint16_t number : values) {
        if (number < min) {
            min = number;
            numbers += 1;
        }
    }
    std::get<0>(result) = numbers;
    std::get<1>(result) = min;
    return result;
}

const std::tuple<int, int> Task::max(std::vector<uint16_t> const &values) {
    std::tuple<int, int> result;
    uint16_t max = 0;
    int numbers = 0;
    for (uint16_t number : values) {
        if (number > max) {
            max = number;
            numbers += 1;
        }
    }
    std::get<0>(result) = numbers;
    std::get<1>(result) = max;
    return result;
}






/*solves a partial task*/
void Task::solve(BinaryReader& binaryReader) {
    std::vector<uint16_t> read_values = std::move(binaryReader.read_range(this->column,
                                                             this->start_range,
                                                            this->end_range,
                                                         this->number_columns));
    std::tuple<int, int> utils_result;

    typedef const std::tuple<int, int> (Task::*task_method)
                (const std::vector<uint16_t> &read_values);
    typedef std::map<std::string,task_method> task_map;
    task_map functions;
    functions["sum"] = &Task::sum;
    functions["mean"] = &Task::sum;
    functions["min"] = &Task::min;
    functions["max"] = &Task::max;
    task_map::iterator it = functions.find(this->op);

    utils_result = (this->*it->second)(read_values);

    std::get<0>(this->result) = std::get<0>(utils_result);
    std::get<1>(this->result) = std::get<1>(utils_result);
    std::get<2>(this->result) = this->id;
    std::get<3>(this->result) = this->op;
}

std::tuple<int, uint16_t, int, std::string> Task::get_result() {
    return std::move(this->result);
}

Task::~Task() {
}

