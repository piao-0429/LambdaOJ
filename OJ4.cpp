#include<algorithm>
#include<stdio.h>
#include<queue>
#include<utility>
#include<string>
using namespace std;
typedef pair<long long, long long> pll;
const long long MAXN = 100005;
const long long MAXM = 100005;
struct Node 
{
	long long d[2];
};
Node vacancy[MAXN], boss[MAXM];
priority_queue<pll, vector<pll>, greater<pll> >q;
long long N, M, x, y, kk, rt, totN, ptr;
int dim;
long long ls[MAXN], rs[MAXN], Left[MAXN], Right[MAXN], Down[MAXN], Up[MAXN];
long long sz[MAXN], id[MAXN];
long long k[MAXM];
inline long long read()
{
	register long long num = 0;

	register char ch = getchar();
	while (!isdigit(ch))
	{
		ch = getchar();
	}

	while (isdigit(ch))
	{
		num = (num << 3) + (num << 1) + (long long)ch - 48;
		ch = getchar();
	}
	return num;
}
inline void write(long long x)
{
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
inline bool compare(long long x, long long y)
{
	return vacancy[x].d[dim] < vacancy[y].d[dim];
}
inline void update(long long node, long long x)
{
	Left[node] = min(Left[node], Left[x]), Right[node] = max(Right[node], Right[x]);
	Down[node] = min(Down[node], Down[x]), Up[node] = max(Up[node], Up[x]);
}
inline void update(long long node)
{
	sz[node] = sz[ls[node]] + sz[rs[node]] + 1;
	Left[node] = Right[node] = vacancy[node].d[0], Up[node] = Down[node] = vacancy[node].d[1];
	ls[node] ? update(node, ls[node]) : (void)1;
	rs[node] ? update(node, rs[node]) : (void)1;
}
inline long long BuildTree(long long l, long long r, int d)
{
	if (l > r)
	{
		return 0;
	}
	long long mid = (l + r) >> 1;
	dim = d, nth_element(id + l, id + mid, id + r + 1, compare);
	ls[id[mid]] = BuildTree(l, mid - 1, d ^ 1), rs[id[mid]] = BuildTree(mid + 1, r, d ^ 1);
	return update(id[mid]), id[mid];
}
inline long long dist(long long x, long long y, long long kk)
{
	long long dx = max(abs(x - Right[kk]), abs(x - Left[kk])), dy = max(abs(y - Up[kk]), abs(y - Down[kk]));
	return dx * dx + dy * dy;
}
inline long long dist(long long x1, long long y1, long long x2, long long y2)
{
	long long dx = (x1 - x2), dy = (y1 - y2);
	return dx * dx + dy * dy;
}
inline void query(long long x, long long y, long long node)
{
	if (!node)
	{
		return;
	}
	pll d;
	d.first = dist(x, y, vacancy[node].d[0], vacancy[node].d[1]);
	d.second = -node;
	d > q.top() ? q.pop(), q.push(d) : (void)1;
	long long dl = -2, dr = -2, dirl = ls[node], dirr = rs[node];
	ls[node] ? dl = dist(x, y, ls[node]) : 1, rs[node] ? dr = dist(x, y, rs[node]) : 1;
	dl < dr ? swap(dl, dr), swap(dirl, dirr) : (void)1;
	dl >= q.top().first ? query(x, y, dirl) : (void)1;
	dr >= q.top().first ? query(x, y, dirr) : (void)1;
}
int main()
{
	totN = N = read();
	M = read();
	for (register int i = 1; i <= N; i++)
	{
		vacancy[i].d[0] = read(), vacancy[i].d[1] = read(), id[i] = i;
	}
	rt = BuildTree(1, N, 0);
	for (register int i = 1; i <= M; i++)
	{
		boss[i].d[0] = read(), boss[i].d[1] = read(), k[i] = read();
	}
	for (register int i = 1; i <= M; i++)
	{	
		while (!q.empty())
		{
			q.pop();
		}
		for (register int j = 0; j < k[i]; j++)
		{
			pll tmp;
			tmp.first = -1;
			tmp.second = 1;
			q.push(tmp);
		}
		query(boss[i].d[0], boss[i].d[1], rt);
		write(-q.top().second - 1);
		putchar('\n');
	}
}