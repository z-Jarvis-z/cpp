#include<bitset>
#include<iostream>
const int maxn = 1e7 + 10;
std::bitset<maxn> pri;
int primes[maxn], pp = 0;
inline bool check_is_prime(int x)
{
	for (int i = 2; i <= x / i; ++ i)
	{
		if (x % i == 0)
			return 0;
	}
	return 1;
}
//°£ÊÏÉ¸·¨
void Eratosthenes()
{
	int N = 1e7;
	for (int i = 2; i <= N / i; ++ i)
	{
		if (!pri[i])
			for (int j = i * i; j <= N; j += i)
				pri[j] = 1;
	}
	int cnt = 0;
	for (int i = 2; i <= N; ++i)
		if (!pri[i])
			cnt++;
	std::cout << cnt << std::endl;
}
//Å·À­É¸·¨
void ola()
{
	int N = 1e7;
	int cnt = 0;
	for (int i = 2; i <= N; ++i)
	{
		if (!pri[i])
		{
			primes[++pp] = i;
			cnt++;
		}
		for (int j = 1; primes[j] * i <= N; ++j)
		{
			pri[primes[j] * i] = 1;
			if (i % primes[j] == 0)
				break;
		}
	}
	std::cout << cnt << std::endl;
}