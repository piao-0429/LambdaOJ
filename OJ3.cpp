#include<iostream>
using namespace std;
int max(int a, int b, int c,int d)
{
	return (a > b ? a : b) > (c > d ? c : d) ? (a > b ? a : b) : (c > d ? c : d);
}
int main()
{
	int N;
	int* w;
	int* sum;
	int* temp;
	int i, j;
	cin >> N;
	w = new int[N + 1];
	sum = new int[N];
	temp = new int[N];
	w[0] = temp[0] = sum[0] = 0;
	for (i = 1; i <= N; i++)
	{
		cin >> w[i];
	}	
	for (i = 1; i < N; i++)
		sum[i] = w[i] > w[i + 1] ? w[i] : w[i + 1];
	for (i = 1; i < N / 2; i++)
	{
		for (j = 1; j < N - 2 * i; j++)
		{
			temp[j] = max(sum[j] + w[2 * i + j + 1], sum[j + 1] + w[j], sum[j + 1] + w[2 * i + j + 1], sum[j + 2] + w[j]);
			sum[j] = temp[j];
		}
	}
	cout << sum[1];
	return 0;
}