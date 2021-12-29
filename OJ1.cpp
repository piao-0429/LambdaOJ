#include <iostream>
using namespace std;
int main()
{
    std::ios::sync_with_stdio(false);
    long n;
    int cnt[8];
    for (int i = 0; i < 8; i++)
    {
        cnt[i] = 0;
    }
    cin >> n;
    if (n == 0)
        cout << 10 << endl;
    else if (n == 1)
        cout << 1 << endl;
    else
    {
        while (n % 2 == 0)
        {
            cnt[0] ++;
            n /= 2;
        }
        while (n % 3 == 0)
        {
            cnt[1] ++;
            n /= 3;
        }
        while (n % 5 == 0)
        {
            cnt[2] ++;
            n /= 5;
        }
        while (n % 7 == 0)
        {
            cnt[3] ++;
            n /= 7;
        }
        if (n > 1)
            cout << -1 << endl;
        else
        {
            cnt[4] = cnt[1] / 2;
            cnt[5] = cnt[0] / 3;
            cnt[6] = ((cnt[0] - 3 * cnt[5]) < (cnt[1] - 2 * cnt[4])) ? (cnt[0] - 3 * cnt[5]) : (cnt[1] - 2 * cnt[4]);
            cnt[7] = (cnt[0] - 3 * cnt[5] - cnt[6]) / 2;
            cnt[0] = cnt[0] - 3 * cnt[5] - cnt[6] - 2 * cnt[7];
            cnt[1] = cnt[1] - 2 * cnt[4] - cnt[6];
            while (cnt[0] > 0)
            {
                cout << 2;
                cnt[0] --;
            }
            while (cnt[1] > 0)
            {
                cout << 3;
                cnt[1] --;
            }
            while (cnt[7] > 0)
            {
                cout << 4;
                cnt[7] --;
            }
            while (cnt[2] > 0)
            {
                cout << 5;
                cnt[2] --;
            }
            while (cnt[6] > 0)
            {
                cout << 6;
                cnt[6] --;
            }
            while (cnt[3] > 0)
            {
                cout << 7;
                cnt[3] --;
            }
            while (cnt[5] > 0)
            {
                cout << 8;
                cnt[5] --;
            }
            while (cnt[4] > 0)
            {
                cout << 9;
                cnt[4] --;
            }
        }
    }
    return 0;
}