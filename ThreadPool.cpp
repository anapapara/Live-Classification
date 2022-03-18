#include "ThreadPool.h"

void ThreadPool::AddTask(std::function<void()>&& task)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	m_taskList.emplace_back(std::move(task));

}

void ThreadPool::ExecuteTasks()
{
	for (int i = 0;i < m_numberOfThreads;++i) {
		
		std::thread worker([this]() 
			{
				while (true) {
					std::function<void()> currentTask;
					{
						std::lock_guard<std::mutex> lock(m_mutex);
						if (m_taskList.empty()) {
							break;
						}
						else {
							currentTask = m_taskList.front();
							m_taskList.pop_front();
						}
					}
					currentTask();
				}
				
			});
		worker.detach();
	}
}
