#include <vector>
#include <tuple>
#include <string>
#include "taskManager.h"
#include "binaryReader.h"
#include "thread.h"

class Worker : public Thread {
    private:
        PartialResults& results;
        TaskManager& taskManager;
        BinaryReader& binaryReader;
        ProtectedQueue& tasksQueue;
    public:
        Worker(PartialResults& results,
                TaskManager& taskManager,
                    BinaryReader& binaryReader,
                    ProtectedQueue& tasksQueue);

    virtual void run() override;
};

