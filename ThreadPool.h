#pragma once
#include<mutex>
#include<vector>
#include<functional>
#include<deque>

class ThreadPool
{
public:
	void AddTask(std::function<void()>&& task);
	void ExecuteTasks();

private:
	std::deque<std::function<void()>> m_taskList;
	uint8_t m_numberOfThreads = 6;
	std::mutex m_mutex;
};