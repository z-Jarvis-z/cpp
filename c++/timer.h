#include<iostream>
#include<chrono>
#include<thread>
class timer
{
public:
	std::chrono::time_point<std::chrono::steady_clock> start,end;
	timer()
	{
	start=std::chrono::high_resolution_clock::now();//get current time
	}
	~timer()
	{
	end=std::chrono::high_resolution_clock::now();//get current time
	std::chrono::duration<float> duration = end - start;
	float ms = duration.count() * 1000.0f;
	std::cout << "Timer took " << ms << "ms" << std::endl;
	}
};
//static void timer01()
//{
//	using namespace std::literals::chrono_literals;
//	std::this_thread::sleep_for(1s); 
//	
//}