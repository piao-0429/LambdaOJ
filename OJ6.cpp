#include<stdio.h>
#include<cmath>
const int n_max = 1000;
const int M_max = 10;
int S[M_max][n_max];
int t[M_max][n_max];
int x[n_max];
int free_x[n_max];
int A[n_max][n_max + 1];
int M, n[M_max];
int temp;
void init_A(int m)
{
	for (int i = 0; i < n[m]; i++)
	{
		for (int j = 0; j < n[m]; j++)
		{
			A[i][j] = S[m][(i + j) % n[m]];
		}
		A[i][n[m]] = t[m][i];
	}
}
int Gauss_xor(int m)
{
    int max_r, col, k;
    int free_num = 0;
    for (k = 0, col = 0; k < n[m] && col < n[m]; k++, col++) {
        max_r = k;
        for (int i = k + 1; i < n[m]; i++) {
            if (A[i][col] > A[max_r][col])
                max_r = i;
        }
        if (A[max_r][col] == 0) {
            k--;
            free_x[free_num++] = col;
            continue;
        }
        if (max_r != k) {
            for (int j = col; j < n[m] + 1; j++)
            {
                temp = A[k][j];
                A[k][j] = A[max_r][j];
                A[max_r][j] = temp;
            }     
        }
        for (int i = k + 1; i < n[m]; i++) {
            if (A[i][col] != 0) {
                for (int j = col; j < n[m] + 1; j++)
                    A[i][j] ^= A[k][j];
            }
        }
    }
    for (int i = k; i < n[m]; i++)
        if (A[i][col] != 0)
            return -1;  
    for (int i = k - 1; i >= 0; i--) 
    {
        x[i] = A[i][n[m]];
        for (int j = i + 1; j < k; j++)
            x[i] ^= (A[i][j] && x[j]);
    }
    for (int i = k; i < n[m]; i++) x[i] = 0;
    return n[m]-k;
}
int main()
{
	char ch;
    int flag;
	scanf("%d", &M);
    for (int m = 0; m < M; m++)
    {
        scanf("%d", &n[m]);
        while ((ch = getchar()) == ' ');
        for (int i = 0; i < n[m]; i++)
        {
            S[m][i] = ch - 48;
            ch = getchar();
        }
        while ((ch = getchar()) == ' ');
        for (int i = 0; i < n[m]; i++)
        {
            t[m][i] = ch - 48;   
            ch = getchar();
        }
    }
    for (int m = 0; m < M; m++)
    {
        init_A(m);
        flag = Gauss_xor(m);
        if (flag == -1) printf("N\n");
        else
        {
            for (int i = 0; i < n[m]; i++)
            {
                if (x[i] == 0) printf("A");
                else
                {
                    printf("BA"); 
                }
            }
            printf("\n");
        }
    }
	return 0;
}