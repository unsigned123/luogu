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

long long **map, **stored;
long long m, n;

long long dfs(long long x, long long y)
{
    if (stored[x][y] != -1)
        return stored[x][y];

    if (map[x][y])
        return 0;

    if (x == m && y == n)
    {
        return 1;
    }

    long long sum = 0;

    if (x < m)
    {
        sum += dfs(x + 1, y);
    }
    
    if (y < n)
    {
        sum += dfs(x, y + 1);
    }

    stored[x][y] = sum;

    return sum;
}


int main() {
    long long x, y;

    cin >> m >> n >> x >> y;

    map = new long long*[m + 1];
    stored = new long long* [m + 1];

    for (long long i = 0; i < m + 1; i++)
    {
        map[i] = new long long[n + 1];
        stored[i] = new long long[n + 1];

        memset(map[i], 0, sizeof(long long) * (n + 1));
        memset(stored[i], -1, sizeof(long long) * (n + 1));
    }

    vector<pair<long long, long long>> offsets = { {-2,-1} , {-1,-2} ,{2,1} ,{1,2} , {-2,1} ,{-1,2},{2,-1} ,{1,-2},{0,0} };

    for (auto p : offsets)
    {
        if (x + p.first >= 0 && x + p.first <= m && y + p.second >= 0 && y + p.second <= n)
            map[x + p.first][y + p.second] = 1;
    }

    cout << dfs(0, 0);

    return 0;
}