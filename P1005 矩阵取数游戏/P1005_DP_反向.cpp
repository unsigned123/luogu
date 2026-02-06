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

int m, n;
int** pow2;

#define LEN 20

int* big_num(int n = 0, int base = 1000)
{
    int* num = new int[LEN];
    memset(num, 0, sizeof(int) * LEN);

    for (int i = 0; n > 0; i++)
    {
        num[i] = n % base;
        n /= base;
    }

    return num;
}

int* big_num(int* src)
{
    int* num = new int[LEN];
    memset(num, 0, sizeof(int) * LEN);

    memcpy(num, src, sizeof(int) * LEN);
    return num;
}

int* add(int* a, int* b, int base = 1000)
{
    int* result = big_num();
    for (int i = 0; i < LEN - 1; i++)
    {
        result[i] += a[i] + b[i];
        if (result[i] >= base)
        {
            result[i + 1]++;
            result[i] -= base;
        }
    }

    return result;
}


//注意大base下long long溢出问题
int* mul(int* a, int b, int base = 1000)
{
    int* result = big_num();

    long long carry = 0;
    int i = 0;
    for (i = 0; i < LEN - 1; i++)
    {
        carry += a[i] * (long long)b;
        result[i] = carry % base;
        carry /= base;
    }
    while (carry > 0)
    {
        result[i] = carry % base;
        carry /= base;
        i++;
    }
    return result;
}


//注意高精度下base不为10对print的影响
void print(int* num, int base = 1000)
{
    int i;
    for (i = LEN - 1; i > 0; i--)
        if (num[i] != 0) 
            break;

    //最高位直接输出
    cout << num[i--];

    //其他位补零
    for (; i >= 0; i--) {
        cout << setw(log10(base)) << setfill('0') << num[i];
    }
    cout << endl;
}

//i = LEN-1!!!! ->-1-<!!!
bool less_(int* a, int* b)
{
    for (int i = LEN - 1; i >= 0; i--)
    {
        if (a[i] != b[i])
            return a[i] < b[i];
    }
    return false;
}


//高精度需要专门的比较函数！
int* dp(int* row)
{
    int*** dp_;

    dp_ = new int** [n];

    for (int i = 0; i < n; i++)
    {
        dp_[i] = new int*[n];
    }

    for (int i = 0; i < n; i++)
        dp_[i][i] = big_num(2 * row[i]);

    for (int length = 2; length <= n; length++)
    {
        for (int left = 0; left < n - length + 1; left++)
        {
            int right = left + length - 1;
            dp_[left][right] = max(
                {
                    add(mul(dp_[left + 1][right], 2), big_num(2 * row[left])),
                    add(mul(dp_[left][right - 1], 2), big_num(2 * row[right]))
                }
            ,less_);
        }
    }

    return dp_[0][n - 1];
}




int main() {
    cin >> m >> n;


    map = new int* [m];

    for (int i = 0; i < m; i++)
    {
        map[i] = new int[n];
        memset(map[i], 0, n * sizeof(int));
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            cin >> map[i][j];
    }

    pow2 = new int*[90];
    pow2[0] = big_num(1);

    for (int i = 0; i < 89; i++)
    {
        pow2[i + 1] = mul(pow2[i], 2);
    }

    int* result = big_num();

    for (int i = 0; i < m; i++)
    {
        result = add(result, dp(map[i]));
    }

    print(result);

    return 0;
}