#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <string.h>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include <algorithm>

using namespace std;

int** map;
int*** dp;
int m, n;


int main() {
    cin >> m >> n;


    map = new int* [m];
    dp = new int** [m + n - 1];

    for (int i = 0; i < m; i++)
    {
        map[i] = new int[n];
        memset(map[i], 0, n * sizeof(int));
    }

    for (int i = 0; i < m + n - 1; i++)
    {
        dp[i] = new int* [m];
        for (int j = 0; j < m; j++)
        {
            dp[i][j] = new int[m];
            memset(dp[i][j], 0, m * sizeof(int));
        }
    }


    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            cin >> map[i][j];
    }

    for (int s = 1; s < m + n - 1; s++)
    {
        for (int i = max(0, s - n + 1); i < min(m, s + 1); i++)
        {
            for (int j = max(0, s - n + 1); j < min(m, s + 1); j++)
            {
                //(i, s - i) (j, s - j)
                if (i == j)
                    if (s != m + n - 2)
                        continue;


                dp[s][i][j] += (map[i][s - i] + map[j][s - j]);
                
                if (i != 0 && j == 0)
                    dp[s][i][j] += max({ dp[s - 1][i][j], dp[s - 1][i - 1][j] });
                else if (i == 0 && j != 0)
                    dp[s][i][j] += max({ dp[s - 1][i][j - 1], dp[s - 1][i][j] });
                else if (i != 0 && j != 0)
                    dp[s][i][j] += max({ dp[s - 1][i][j - 1], dp[s - 1][i][j] ,dp[s - 1][i - 1][j - 1], dp[s - 1][i - 1][j] });

            }
        }
    }

    cout << dp[m + n - 2][m - 1][m - 1];

    return 0;
}