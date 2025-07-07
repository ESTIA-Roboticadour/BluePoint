#include "RobotThread.h"
#include "IRobot.h"
#include <thread>

RobotThread::RobotThread(IRobot* robot) :
	m_robot(robot),
	m_running(false) 
{
}

RobotThread::~RobotThread() {
	stop();
}

void RobotThread::start() {
	if (!m_running)
	{
		m_running = true;
		m_thread = std::thread(&RobotThread::run, this);
	}
}

void RobotThread::stop() {
	if (m_running)
	{
		m_running = false;
		if (m_thread.joinable())
			m_thread.join();
	}
}

bool RobotThread::setPriorityClass(DWORD priorityClass)
{
	HANDLE processHandle = GetCurrentProcess();
	return SetPriorityClass(processHandle, priorityClass) != 0;
}

bool RobotThread::setPriority(int priority)
{
	if (!m_thread.joinable()) return false;
	HANDLE handle = (HANDLE)m_thread.native_handle();
	return SetThreadPriority(handle, priority) != 0;
}

bool RobotThread::setAffinity(int coreIndex)
{
	if (!m_thread.joinable()) return false;
	HANDLE handle = (HANDLE)m_thread.native_handle();
	DWORD_PTR mask = 1ULL << coreIndex;
	return SetThreadAffinityMask(handle, mask) != 0;
}

void RobotThread::run()
{
	while (m_running) {
		if (m_robot)
			m_robot->controlLoop();
		// Optionally: std::this_thread::sleep_for(std::chrono::milliseconds(1));
		std::this_thread::sleep_for(std::chrono::microseconds(500));
	}
}
