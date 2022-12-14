#include <iostream>
#include <queue>
using namespace std;

long long N;
bool prime_arr[1000000];
queue<long long> prime_queue;

void	eratos(void)
{
	for (long long i = 2; i < 1000000; i++)
		prime_arr[i] = true;
	for (long long i = 2; i * i < 1000000; i++)
	{
		if (!prime_arr[i])
			continue;
		for (long long j = i * 2; j < 1000000; j += i)
			prime_arr[j] = false;
	}
}

void get_prime(void)
{
	int num = 2;

	while (N != 1 && num < 1000000)
	{
		if (!prime_arr[num] || N % num != 0)
		{
			num++;
			continue ;
		}

		prime_queue.push(num);
		N /= num;
	}

	if (N != 1)
		prime_queue.push(N);
}

long long get_composition(void)
{
	long long num1 = prime_queue.front();
	prime_queue.pop();
	long long num2 = prime_queue.front();
	prime_queue.pop();
	if (prime_queue.size() != 1)
		return (num1 * num2);
	long long num3 = prime_queue.front();
	prime_queue.pop();
	return (num1 * num2 * num3);
}

void print_composition(void)
{
	if (prime_queue.size() <= 1)
	{
		cout << -1;
		return;
	}

	while (prime_queue.size() > 3)
		cout << get_composition() << ' ';
	cout << get_composition();
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	eratos();
	get_prime();
	print_composition();
	return (0);
}
