#pragma once
#include<mutex>
#include<queue>
#include<thread>
#include<vector>
#include<chrono>
#include<functional>
#include<condition_variable>
class simple_thread_pool
{
public:
	simple_thread_pool(unsigned int threadnumber) :stop(false)
	{
		for (unsigned int i = 0; i < threadnumber; i++)
		{
			threads.emplace_back([this]()
				{
					while (true)
					{
						std::unique_lock<std::mutex> lock(mtx);
						condition.wait(lock, [this]()
							{
								return !tasks.empty() || stop;
							});
						if (stop && tasks.empty())
							return;
						std::function<void()> task = tasks.front();
						tasks.pop();
						lock.unlock();
						task();
					}
				}
			);
		}

	}
	~simple_thread_pool()
	{
		{
			std::unique_lock<std::mutex> lock(mtx);
			stop = true;
		}
		for (auto& thread : threads)
		{
			thread.join();
		}
	}
	template<typename F, typename... Args>
	void enqueue(F&& function, Args&&... args)
	{
		std::function<void()>task=std::bind(std::forward<F>(function), std::forward<Args>(args)...);
		{
			std::unique_lock<std::mutex> lock(mtx);
			tasks.emplace(std::move(task));
		}
		condition.notify_one();
	}
private:
	std::mutex mtx;
	std::condition_variable condition;

	std::vector<std::thread> threads;
	std::queue<std::function<void()>> tasks;
	bool stop;
};