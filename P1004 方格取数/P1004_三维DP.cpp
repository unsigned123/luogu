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
int n;




int main() {
    cin >> n;


    map = new int* [n];
    dp = new int** [2 * n - 1];

    for (int i = 0; i < n; i++)
    {
        map[i] = new int[n];
        memset(map[i], 0, n * sizeof(int));
    }

    for (int i = 0; i < 2 * n - 1; i++)
    {
        dp[i] = new int*[n];
        for (int j = 0; j < n; j++)
        {
            dp[i][j] = new int[n];
            memset(dp[i][j], 0, n * sizeof(int));
        }
    }

    while(1){
        int x, y, v;
        cin >> x >> y >> v;

        if (x == 0 && y == 0 && v == 0)
            break;

        x--;
        y--;


        map[x][y] = v;

    }

    dp[0][0][0] = map[0][0];

    for (int s = 1; s < 2 * n - 1; s++)
    {
        for (int i = max(0, s - n + 1); i <= min(s, n - 1); i++)
        {
            for (int j = max(0, s - n + 1); j <= min(s, n - 1); j++)
            {
                if (i == 0 && j == 0)
                    dp[s][i][j] = dp[s - 1][i][j];
                else if (i != 0 && j == 0)
                    dp[s][i][j] = max({ dp[s - 1][i - 1][j],
                    dp[s - 1][i][j] });
                else if (i == 0 && j != 0)
                    dp[s][i][j] = max({ dp[s - 1][i][j - 1],
                    dp[s - 1][i][j] });
                else
                    dp[s][i][j] = max({ dp[s - 1][i - 1][j - 1],
                        dp[s - 1][i][j - 1],
                        dp[s - 1][i - 1][j],
                        dp[s - 1][i][j] });
                if (i != j)
                {
                    dp[s][i][j] += (map[i][s - i] + map[j][s - j]);
                }
                else
                {
                    dp[s][i][j] += map[i][s - i];
                }
            }
        }
    }

    cout << dp[2 * n - 2][n - 1][n - 1];

    return 0;
}