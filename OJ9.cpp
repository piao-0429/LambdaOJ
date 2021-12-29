#include<stdio.h>
const int inf = 0x3f3f3f3f;
const int N_max = 1000005;
int N;
int a[N_max];
int ans[2];
int f[2][N_max];
int sum = 0;
int max(int x, int y)
{
	return x > y ? x : y;
}
void condition_1()
{
	ans[0] = -inf;
	int tmp;
	for (int i = 1; i <= N; i++)
	{
		f[0][i] = f[1][i] = 0;
	}
	for (int i = 1; i <= 3; i++)
	{
		tmp = f[(i - 1) % 2][i - 1];
		f[i % 2][i] = f[(i - 1) % 2][i - 1] + a[i];
		for (int j = i + 1; j <= N - 3 + i; j++)
		{
			tmp = max(tmp, f[(i - 1) % 2][j - 1]);
			f[i % 2][j] = f[i % 2][j - 1] + a[j];
			f[i % 2][j] = max(tmp + a[j], f[i % 2][j]);
		}
	}
	for (int i = 3; i <= N; i++)
	{
		ans[0] = max(ans[0], f[1][i]);
	}
}
void condition_2()
{
	ans[1] = -inf;
	int tmp;
	for (int i = 1; i <= N; i++)
	{
		f[0][i] = f[1][i] = 0;
		a[i] = -a[i];
	}
	for (int i = 1; i <= 3; i++)
	{
		tmp = f[(i - 1) % 2][i - 1];
		f[i % 2][i] = f[(i - 1) % 2][i - 1] + a[i];
		for (int j = i + 1; j <= N - 3 + i; j++)
		{
			tmp = max(tmp, f[(i - 1) % 2][j - 1]);
			f[i % 2][j] = f[i % 2][j - 1] + a[j];
			f[i % 2][j] = max(tmp + a[j], f[i % 2][j]);
		}
	}
	for (int i = 3; i <= N; i++)
	{
		ans[1] = max(ans[1], f[1][i]);
	}
	ans[1] += sum;
}
int main()
{
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &a[i]);
		sum += a[i];
	}
	condition_1();
	condition_2();
	printf("%d", max(ans[0], ans[1]));
	return 0;
}