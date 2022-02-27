#include "partialResults.h"



void PartialResults::push_back(std::tuple<int,
                                        uint16_t,
                                            int,
                                                std::string> result) {
    std::lock_guard<std::mutex> lock(mutex);
    this->results.push_back(result);
}
std::tuple<int, uint16_t, int, std::string>& PartialResults::at(size_t i) {
    std::lock_guard<std::mutex> lock(mutex);
    return this->results[i];
}

unsigned int PartialResults::size() {
    std::lock_guard<std::mutex> lock(mutex);
    return this->results.size();
}
