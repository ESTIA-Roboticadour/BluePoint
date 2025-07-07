#pragma once
#include <thread>
#include <atomic>
#include <windows.h>

class IRobot;

class RobotThread
{
public:
    explicit RobotThread(IRobot* robot);
    ~RobotThread();

    void start();
    void stop();

    bool setPriorityClass(DWORD priorityClass);
    bool setPriority(int priority);
    bool setAffinity(int coreIndex);

private:
    void run();
    IRobot* m_robot;
    std::thread m_thread;
    std::atomic<bool> m_running;
};
