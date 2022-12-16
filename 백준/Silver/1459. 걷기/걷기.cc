#include <stdio.h>

unsigned long long X, Y, W, S;
unsigned long long result;

void init()
{
	scanf("%llu %llu %llu %llu", &X, &Y, &W, &S);
}

void solve()
{
	if (W * 2 <= S)
	{
		result = (X + Y) * W;
	}
	else
	{
		unsigned long long small, large, step;
		if (X < Y)
		{
			small = X;
			large = Y;
			step = Y - X;
		}
		else
		{
			small = Y;
			large = X;
			step = X - Y;
		}

		if (W * 2 <= S * 2)
			result = small * S + step * W;
		else
			result = (small + step - step % 2) * S + (step % 2) * W;
	}
}

int main()
{
	init();
	solve();
	printf("%llu", result);

	return 0;
}