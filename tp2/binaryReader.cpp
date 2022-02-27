#include <string>
#include <vector>
#include <utility>
#include <arpa/inet.h>
#include  <exception>

#include "binaryReader.h"


BinaryReader::BinaryReader(std::string &name) {
    try {
        this->file.open(name, std::ios::binary);
        
        if (!this->file.is_open()) {
                throw std::exception();
        }
    } catch(std::invalid_argument &e) {
        std::cout << e.what();
    }
}

BinaryReader::BinaryReader(BinaryReader&& other) {
    if (this == &other) {
        this->file = std::move(other.file);
    }
}

BinaryReader &BinaryReader::operator=(BinaryReader &&other) {
    if (this != &other) {
        this->file = std::move(other.file);
    }
    return *this;
}

/*turns binary number in uint16_t number*/
uint16_t BinaryReader::read() {
    uint16_t value;
    this->file.read(reinterpret_cast<char*>(&value), sizeof(value)); 
    value = ntohs(value);
    return value;
}

/*reads binarys number based on range, returning a vector with uint16_t*/
std::vector<uint16_t> BinaryReader::read_range(int column,
                                            int start_range,
                                                int end_range,
                                                 int cols) {
    std::vector<uint16_t> read_values;
    std::lock_guard<std::mutex> lock(mutex);
    for (int i = 0; i < end_range - start_range; i++) {
        this->file.seekg((column) * 2 + ((cols * 2) * (start_range + i)));
        read_values.push_back(this->read());
    }
    return read_values;
}

BinaryReader::~BinaryReader() {
}


