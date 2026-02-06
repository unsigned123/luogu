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
int n;

vector<pair<int, int>> pois;
vector<int> path;

int search(int x, int y, int _index)
{
    if (x == n - 1 && y == n - 1)
    {
        path[_index] = -1;
        return map[x][y];
    }

    int sum = -1;
    int count = 0, max_count = -1;
    bool found = false;
    vector<int> max_path;

    for (auto poi : pois)
    {
        if (x <= poi.first && y <= poi.second && !(x == poi.first && y == poi.second))
        {
            int result = search(poi.first, poi.second, _index + 1);
            if (sum < result)
            {
                found = true;
                sum = result;
                max_count = count;

                max_path = path;
                max_path[_index] = count;
            }
        }
        count++;
    }

    if (!found)
    {
        path[_index] = -1;
        return map[x][y];
    }

    auto poi = pois[max_count];
    path = max_path;

    return sum + map[x][y];
}

int main() {
    cin >> n;

    path.resize(n * n, -1);

    map = new int* [n];

    for (int i = 0; i < n; i++)
    {
        map[i] = new int[n];
        memset(map[i], 0, n * sizeof(int));
    }

    while(1){
        int x, y, v;
        cin >> x >> y >> v;

        if (x == 0 && y == 0 && v == 0)
            break;

        x--;
        y--;


        map[x][y] = v;
        pois.push_back({ x,y });

    }

    int a = search(0, 0, 0);

    vector<pair<int, int>> new_pois;

    for (int i = 0; i < path.size(); i++)
    {
        if (path[i] == -1)
        {
            path.erase(path.begin() + i, path.end());
            break;
        }
    }

    sort(path.begin(), path.end());

    vector<bool> to_keep(pois.size(), true);

    for (auto p : path)
        to_keep[p] = false;

    for (int i = 0; i < pois.size(); i++) {
        if (pois[i].first == 0 && pois[i].second == 0)
        {
            map[0][0] = 0;
            continue;
        }

        if (to_keep[i])
            new_pois.push_back(pois[i]);
        else
            map[pois[i].first][pois[i].second] = 0;
    }

    pois = new_pois;

    path = vector<int>(n * n, -1);

    int b = search(0, 0, 0);


    cout << a + b;

    return 0;
}