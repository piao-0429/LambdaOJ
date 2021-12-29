#include <iostream>
using namespace std;
int main()
{
	std::ios::sync_with_stdio(false);
	struct nodes
	{
		int before;
		int next;
	};
	struct nodes* node;
	struct nodes temp;
	int N, M;
	int K, L;
	int l;
	int i, j, k;
	int choice, flag, flag_right = 1;
	cin >> N >> M >> K >> L;
	l = N + M + K + L;
	node = new struct nodes[N + 2];
	node[0].before = -1;
	node[0].next = N + 1;
	node[N + 1].before = 0;
	node[N + 1].next = -1;
	while (l > 0)
	{
		cin >> choice;
		l--;
		switch (choice)
		{
		case(1):
		{
			cin >> i >> j >> flag;
			if (flag == flag_right)
			{
				node[node[j].next].before = i;
				node[i].next = node[j].next;
				node[i].before = j;
				node[j].next = i;
			}
			else if(flag == 1 - flag_right)
			{
				node[node[j].before].next = i;
				node[i].before = node[j].before;
				node[i].next = j;
				node[j].before = i;
			}
			else
			{
				node[i].before = 0;
				node[i].next = N + 1;
				node[0].next = i;
				node[N + 1].before = i;
			}
			break;
		}
		case(0):
		{
			cin >> i;
			node[node[i].before].next = node[i].next;
			node[node[i].next].before = node[i].before;
			node[i].before = node[i].next = -1;
			break;
		}
		case(-1):
		{
			cin >> i >> j;
			if (node[i].next == j)
			{
				node[node[i].before].next = j;
				node[node[j].next].before = i;
				node[i].next = node[j].next;
				node[j].before = node[i].before;
				node[i].before = j;
				node[j].next = i;
			}
			else if (node[j].next == i)
			{
				node[node[j].before].next = i;
				node[node[i].next].before = j;
				node[j].next = node[i].next;
				node[i].before = node[j].before;
				node[j].before = i;
				node[i].next = j;
			}
			else
			{
				node[node[i].before].next = j;
				node[node[i].next].before = j;
				node[node[j].before].next = i;
				node[node[j].next].before = i;
				temp = node[i];
				node[i] = node[j];
				node[j] = temp;
			}

			break;
		}
		case(-2):
		{
			flag_right = 1 - flag_right;
			break;
		}
		}
	}
	if (L % 2 == 0)
	{
		k = node[0].next;
		for (i = 1; i <= N - M; i++)
		{
			cout << k << " ";
			k = node[k].next;
		}
	}
	else
	{
		k = node[N + 1].before;
		for (i = 1; i <= N - M; i++)
		{
			cout << k << " ";
			k = node[k].before;
		}
	}
	cout << -1 << endl;
	delete[]node;
	return 0;
}