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

int num[9] = { 1,2,3,4,5,6,7,8,9 };
bool state[9];
int path[9] = {-1,-1,-1,-1,-1,-1,-1,-1,-1};
vector<vector<int>> record;

//dfs的轨迹就是一个全排列
//注意由此熟悉DFS的写法
void dfs(int level)
{
    if (level >= 9)
    {
        int a = path[0] * 100 + path[1] * 10 + path[2] * 1;
        int b = path[3] * 100 + path[4] * 10 + path[5] * 1;
        int c = path[6] * 100 + path[7] * 10 + path[8] * 1;

        if (b - a == a && c - b == a)
            record.push_back({ a,b,c });
        return;
    }

    for (int i = 0; i < 9; i++)
    {
        if (!state[i])
        {
            path[level] = num[i];
            state[i] = true;
            dfs(level + 1);
            //注意恢复现场
            state[i] = false;
            //下面这句可以去掉
            path[level] = -1;
        }
    }
}

int main() {
    
    dfs(0);
    for (auto r : record)
    {
        cout << r[0] << ' ' << r[1] << ' ' << r[2] << endl;
    }
    return 0;
}