#include<iostream>
#include<queue>
#include<cmath>
#include<iomanip>
using namespace std;
class complex
{
public:
	complex(double r = 0, double i = 0) :real(r), imag(i) {};
	friend double dis(complex x, complex y)
	{
		return (x.real - y.real) * (x.real - y.real) + (x.imag - y.imag) * (x.imag - y.imag);
	}
	void show() const
	{
		cout << setiosflags(ios::fixed) << setprecision(6) << real << "\t" << setiosflags(ios::fixed) << setprecision(6) << imag << endl;
	}
	complex operator + (const int x) const
	{
		return complex(real + double(x), imag);
	}
	complex operator + (const double x) const
	{
		return complex(real + x, imag);
	}
	complex operator + (const complex x) const
	{
		return complex(real + x.real, imag + x.imag);
	}
	complex operator - (const int x) const
	{
		return complex(real - double(x), imag);
	}
	complex operator - (const double x) const
	{
		return complex(real - x, imag);
	}
	complex operator - (const complex x) const
	{
		return complex(real - x.real, imag - x.imag);
	}
	complex operator * (const int x) const
	{
		return complex(real * double(x), imag * double(x));
	}
	complex operator * (const double x) const
	{
		return complex(real * double(x), imag * double(x));
	}
	complex operator * (const complex x) const
	{
		return complex(real * x.real - imag * x.imag, real * x.imag + imag * x.real);
	}
	complex operator / (const int x) const
	{
		return complex(real / double(x), imag / double(x));
	}
	complex operator / (const double x) const
	{
		return complex(real / double(x), imag / double(x));
	}
	complex operator / (const complex x) const
	{
		return complex((real * x.real + imag * x.imag) / (x.real * x.real + x.imag * x.imag), (-real * x.imag + imag * x.real) / (x.real * x.real + x.imag * x.imag));
	}
	bool operator < (const complex z) const
	{
		if (real != z.real) return real < z.real;
		else if (abs(imag) != abs(z.imag)) return abs(imag) < abs(z.imag);
		else return imag < z.imag;
	}
	double real;
	double imag;
};
const double pi = 3.1415926;
const double min_dis = 25e-4;
const double ep = 1e-6;
const int N_max = 105;
int iter_aberth = 300;
int iter_newton = 500;
int N;
double a[N_max];
double r[2];
complex w[N_max];
complex z[N_max];
int cnt = 1;
complex temp[2];
priority_queue<complex>q;
vector<int>idx;
vector<complex>v;
inline complex f(complex z)
{
	complex res(a[N]);
	for (int i = N - 1; i >= 0; i--)
	{
		res = res * z + a[i];
	}
	return res;
}
inline complex df(complex z, int k)
{
	complex res;
	complex z0(1);
	double m = 1;
	for (int i = 1; i <= k; i++)
	{
		m = m * i;
	}
	for (int i = k; i <= N; i++)
	{
		res = res + z0 * (m * a[i]);

		z0 = z0 * z;
		m = m * ((i + 1.0) / (i + 1.0 - k));
	}
	return res;
}
inline void init()
{
	double zc;
	complex z0;
	double r = 10;
	double theta;
	if (N > 90)
	{
		for (int k = 0; k < N; k++)
			{
				theta = 2 * k * pi / N;
				z[k] = complex(r * cos(theta), r * sin(theta));
			}
	}
	else
	{
		for (int k = 0; k < N; k++)
		{
			zc = a[N - 1] / (N * a[N]);
			theta = (2 * k - 1.5) * pi / N;
			z0 = complex(r * cos(theta), r * sin(theta));
			z[k] = z0 - zc;
		}
	}
}
inline void aberth()
{
	for (int i = 0; i < iter_aberth; i++)
	{
		for (int k = 0; k < N; k++)
		{
			temp[0] = f(z[k]) / df(z[k], 1);
			temp[1] = complex(0);
			for (int j = 0; j < N; j++)
			{
				if (j == k) continue;
				temp[1] = temp[1] + complex(1) / (z[k] - z[j]);
			}
			w[k] = temp[0] / (complex(1) - temp[0] * temp[1]);
		}
		for (int k = 0; k < N; k++)
		{
			z[k] = z[k] - w[k];
        }
	}
	for (int k = 0; k < N; k++)
	{
		if (abs(z[k].imag) < ep) z[k].imag = 0;
	}
}
inline void judge()
{
	bool flag[N_max];
	for (int i = 0; i < N; i++)
	{
		flag[i] = false;
	}
	for (int i = 0; i < N; i++)
	{
		if (flag[i]) continue;
		flag[i] = true;
		for (int j = 0; j < N; j++)
		{
			if (flag[j]) continue;
			if (dis(z[i], z[j]) < min_dis)
			{
				cnt++;
				flag[j] = true;
			}
		}
		v.push_back(z[i]);
		idx.push_back(cnt);
		cnt = 1;
	}
}
inline void newton()
{
	int l = v.size();
	complex O;
	complex dv;
	double ep = 10;
	for (int k = 0; k < l; k++)
	{
		if (idx[k] == 1) continue;
		for (int i = 0; i < iter_newton; i++)
		{
			dv = df(v[k], idx[k] - 1) / df(v[k], idx[k]);
			v[k] = v[k] - dv;
		}
	}
}
inline void print()
{
	for (int k = 0; k < v.size(); k++)
	{
		if (abs(v[k].imag) < ep) v[k].imag = 0;
		if (v[k].imag >= 0)
		{
			for (int j = 0; j < idx[k]; j++)
			{
				q.push(v[k]);
			}
		}
	}
	while (!q.empty())
	{
		temp[0] = q.top();
		q.pop();
		temp[0].show();
		if (temp[0].imag > 0)
		{
			complex(temp[0].real, -temp[0].imag).show();
		}
	}
}
int main()
{
	std::ios::sync_with_stdio(false);
	cin >> N;
	for (int i = N; i >= 0; i--)
	{
		cin >> a[i];
	}
	init();
	aberth();
	judge();
	newton();
	print();
	return 0;
}