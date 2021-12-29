#include<iostream>
#include<cmath>
#include<iomanip>
#include<random>
using namespace std;
const int N_max = 1005;
double A[N_max][N_max];
double B[N_max][N_max];
double x[N_max], y[N_max];
double m = 10.0;
double lamda = 0.0;
int N;
double temp;
double episilon = 6e-8;
void find_max_feature(double M[N_max][N_max])
{
    while (fabs(m - lamda) > episilon)
	{
		lamda = m;
		for (int i = 0; i < N; i++)
		{
			y[i] = 0;
			for (int j = 0; j < N; j++)
			{
				y[i] += M[i][j] * x[j];
			}
		}
		m = fabs(y[0]);
		for (int i = 1; i < N; i++)	
			m = fabs(y[i]) > m ? fabs(y[i]) : m;
		for (int i = 0; i < N; i++)
		{
			x[i] = y[i] / m;
		}
	}
}
int main()
{
	std::ios::sync_with_stdio(false);
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> A[i][j];		
		}	
	}
	x[0] = 1.0;
	for (int i = 1; i < N; i++)
	{
		x[i] = 0.0;
	}
	episilon = (rand() % 100 > 50) ? 3e-8 : 4e-8;
	find_max_feature(A);
	cout << setprecision(4) << lamda << " ";
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			B[i][j] = 0;
		}
		B[i][i] = 1;
	}
	for (int i = N - 1; i > 0; i--)
	{
		if (A[i - 1][0] < A[i][0])
		{
			for (int j = 0; j < N; j++)
			{
				temp = A[i][j];
				A[i][j] = A[i - 1][j];
				A[i - 1][j] = temp;
				temp = B[i][j];
				B[i][j] = B[i - 1][j];
				B[i - 1][j] = temp;
			}
		}
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (j != i)
			{
				temp = A[j][i] / A[i][i];
				for (int k = 0; k < N; k++)
				{
					A[j][k] -= A[i][k] * temp;
					B[j][k] -= B[i][k] * temp;
				}
			}
		}
	}
	for (int i = 0; i < N; i++)
	{
		temp = A[i][i];
		for (int j = 0; j < N; j++)
		{
			A[i][j] = A[i][j] / temp;
			B[i][j] = B[i][j] / temp;
		}
	}
	m = 10.0;
	lamda = 0.0;
	x[0] = 1.0;
	for (int i = 1; i < N; i++)
	{
		x[i] = 0.0;
	}
	find_max_feature(B);
	cout << setprecision(4) << 1.0 / lamda << endl;
	return 0;
}