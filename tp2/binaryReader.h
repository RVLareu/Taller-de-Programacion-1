#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <mutex>
#include <map>
#ifndef BINARYREADER_H_
#define BINARYREADER_H_

class BinaryReader {
    private:
        std::ifstream file;
        std::mutex mutex;
        uint16_t read();

    public:
        explicit BinaryReader(std::string &name);
        BinaryReader(BinaryReader&& other);
        BinaryReader& operator=(BinaryReader &&other);
        std::vector<uint16_t> read_range(int column,
                                            int start_range,
                                                int end_range,
                                                    int number_columns);
    ~BinaryReader();
};
#endif
