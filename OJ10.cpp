#include<iostream>
#include<vector>
#include<queue>
using namespace std;
struct node
{
	short x, y, d;

	node(short xx=0, short yy=0, short dd=0)
	{
		x = xx;
		y = yy;
		d = dd;
	}
	bool operator==(const node a)
	{
		return (x == a.x && y == a.y && d == a.d);
	}
	bool operator!=(const node a)
	{
		return (x != a.x || y != a.y || d != a.d);
	}
}Start, End, temp;
short Lx, Ly;
char*** a;
vector<char>path;
queue<node>q;
short cnt = 0;
short tx, ty, td;
void print()
{
	for (short k = 0; k < 4; k++)
	{
		for (short j = 0; j < Ly; j++)
		{
			for (short i = 0; i < Lx; i++)
			{
				cout << a[i][j][k] << " ";
			}
			cout << endl;
		}
	}
	cout << endl;
}
int main()
{
	std::ios::sync_with_stdio(false);
	cin >> Lx >> Ly;
	a = new char** [Lx];
	for (short i = 0; i < Lx; i++)
	{
		a[i] = new char* [Ly];
	}
	for (short i = 0; i < Lx; i++)
	{
		for (short j = 0; j < Ly; j++)
		{
			a[i][j] = new char[4];
		}
	}
	for (short j = 0; j < Ly; j++)
	{
		for (short i = 0; i < Lx; i++)
		{
			cin >> a[i][j][0];
			a[i][j][1] = a[i][j][2] = a[i][j][3] = a[i][j][0];
		}
	}
	cin >> Start.x >> Start.y >> Start.d;
	cin >> End.x >> End.y >> End.d;
	Start.d--;
	End.d--;
	temp = Start;
	q.push(temp);
	while (temp != End)
	{
		
		q.pop();
		if (a[temp.x][temp.y][(temp.d + 1) % 4] == '0')
		{
			q.push(node(temp.x, temp.y, (temp.d + 1) % 4));
			a[temp.x][temp.y][(temp.d + 1) % 4] = 'L';

		}
		if (a[temp.x][temp.y][(temp.d + 3) % 4] == '0')
		{
			q.push(node(temp.x, temp.y, (temp.d + 3) % 4));
			a[temp.x][temp.y][(temp.d + 3) % 4] = 'R';
		}
		switch (temp.d)
		{
		case 0:
		{
			if (((temp.y - 1) >= 0) && (a[temp.x][temp.y - 1][temp.d] == '0'))
			{
				q.push(node(temp.x, temp.y - 1, temp.d));
				a[temp.x][temp.y - 1][temp.d] = 'F';
				if (((temp.y - 2) >= 0) && (a[temp.x][temp.y - 2][temp.d] == '0'))
				{
					q.push(node(temp.x, temp.y - 2, temp.d));
					a[temp.x][temp.y - 2][temp.d] = 'J';
				}
			}
			break;
		}
		case 1:
		{
			if (((temp.x - 1) >= 0) && (a[temp.x - 1][temp.y][temp.d] == '0'))
			{
				q.push(node(temp.x - 1, temp.y, temp.d));
				a[temp.x - 1][temp.y][temp.d] = 'F';
				if (((temp.x - 2) >= 0) && (a[temp.x - 2][temp.y][temp.d] == '0'))
				{
					q.push(node(temp.x - 2, temp.y, temp.d));
					a[temp.x - 2][temp.y][temp.d] = 'J';
				}
			}
			break;
		}
		case 2:
		{
			if (((temp.y + 1) < Ly) && (a[temp.x][temp.y + 1][temp.d] == '0'))
			{
				q.push(node(temp.x, temp.y + 1, temp.d));
				a[temp.x][temp.y + 1][temp.d] = 'F';
				if (((temp.y + 2) < Ly) && (a[temp.x][temp.y + 2][temp.d] == '0'))
				{
					q.push(node(temp.x, temp.y + 2, temp.d));
					a[temp.x][temp.y + 2][temp.d] = 'J';
				}
			}
			break;
		}
		case 3:
		{
			if (((temp.x + 1) < Lx) && (a[temp.x + 1][temp.y][temp.d] == '0'))
			{
				q.push(node(temp.x + 1, temp.y, temp.d));
				a[temp.x + 1][temp.y][temp.d] = 'F';
				if (((temp.x + 2) < Lx) && (a[temp.x + 2][temp.y][temp.d] == '0'))
				{
					q.push(node(temp.x + 2, temp.y, temp.d));
					a[temp.x + 2][temp.y][temp.d] = 'J';
				}
			}
			break;
		}
		}
		temp = q.front();
	}
	temp = End;
	while (temp != Start)
	{
		path.push_back(a[temp.x][temp.y][temp.d]);
		switch (a[temp.x][temp.y][temp.d])
		{
		case 'L':
		{
			temp = node(temp.x, temp.y, (temp.d + 3) % 4);
			break;
		}
		case 'R':
		{
			temp= node(temp.x, temp.y, (temp.d + 1) % 4);
			break;
		}
		case 'F':
		{
			switch (temp.d)
			{
			case 0:
			{
				temp = node(temp.x, temp.y + 1, temp.d);
				break;
			}
			case 1:
			{
				temp = node(temp.x + 1, temp.y, temp.d);
				break;
			}
			case 2:
			{
				temp = node(temp.x, temp.y - 1, temp.d);
				break;
			}
			case 3:
			{
				temp = node(temp.x - 1, temp.y, temp.d);
				break;
			}
			}
			break;
		}
		case 'J':
		{
			switch (temp.d)
			{
			case 0:
			{
				temp = node(temp.x, temp.y + 2, temp.d);
				break;
			}
			case 1:
			{
				temp = node(temp.x + 2, temp.y, temp.d);
				break;
			}
			case 2:
			{
				temp = node(temp.x, temp.y - 2, temp.d);
				break;
			}
			case 3:
			{
				temp = node(temp.x - 2, temp.y, temp.d);
				break;
			}
			}
			break;
		}
		}
	}
	cout << path.size() << endl;
	for (int i = path.size() - 1; i >= 0; i--)
	{
		if (path[i] == 'J')
			cout << 'F' << '2' << endl;
		else cout << path[i] << endl;
	}
	return 0;
}