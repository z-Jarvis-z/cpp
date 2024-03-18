#include<iostream>
#include"simple_thread_polol.h"
static void test()
{
	simple_thread_pool pool(4);
	for (int i = 1; i < 10; i++)
	{
		pool.enqueue([i]() {
			std::cout << "task " << i << " is running" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1)); 
			std::cout << "task " << i << " is done" << std::endl;
			});
	}
	
}
