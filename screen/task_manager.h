#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <vector>
#include <string>

class TaskManager {
private:
    std::vector<std::string> backgroundTasks;

public:
    void add_task(const std::string &taskName) {
        backgroundTasks.push_back(taskName);
    }

    void remove_task(const std::string &taskName) {
        backgroundTasks.erase(
            std::remove(backgroundTasks.begin(), backgroundTasks.end(), taskName),
            backgroundTasks.end()
        );
    }

    std::vector<std::string> get_tasks() const {
        return backgroundTasks;
    }
};

#endif // TASK_MANAGER_H
