#include <tuple>
#include <string>
#include <map>
#include <algorithm>
#include "binaryReader.h"
#include <vector>
#ifndef TASK_H_ 
#define TASK_H_ 

class Task {
    private:
        int start_range;
        int end_range;
        int column;
        std::tuple<int, uint16_t, int, std::string> result;
        int number_columns;
        std::string op {};
        int id;
        int end_token;
        const std::tuple<int, int> sum(std::vector<uint16_t>const &values);
        const std::tuple<int, int> min(std::vector<uint16_t> const &values);
        const std::tuple<int, int> max(std::vector<uint16_t> const &values);

    public:
        Task(int start_range,
                int end_range,
                    int column,
                        int number_columns,
                            std::string op,
                            int id,
                            int end_token);
        Task(const Task&) = default;
        Task(Task&& other);
        Task& operator=(Task &&other); 
        bool is_end_token();
        void print_task();
        void solve(BinaryReader& binaryReader);
        std::tuple<int, uint16_t, int, std::string> get_result();
    ~Task();
};

#endif //TASK_H_ 
