#include <mutex>
#include <string>
#include <tuple>
#include <vector>

class PartialResults {
    private:
        std::vector<std::tuple<int, uint16_t, int, std::string>> results;
        std::mutex mutex;
    public:
        void push_back(std::tuple<int, uint16_t, int, std::string> result);
        std::tuple<int, uint16_t, int, std::string>&  at(size_t i); 
        unsigned int size();
};
