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

int*** stored;
int** is_stored;

int m, n;
int** pow2;

#define LEN 30

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
int* dp(int* row, int start, int end, int level)
{
    if (is_stored[start][end])
        return stored[start][end];

    if (start + 1 == end)
        return mul(pow2[level], row[start]);

    int* left = dp(row, start + 1, end, level + 1);
    int* left_mul = mul(pow2[level], row[start]);
    int* right = dp(row, start, end - 1, level + 1);
    int* right_mul = mul(pow2[level], row[end - 1]);

    int* left_result = add(left, left_mul);
    delete[] left;
    delete[] left_mul;
    int* right_result = add(right, right_mul);
    delete[] right;
    delete[] right_mul;
    if (less_(left_result, right_result))
    {
        delete[] left_result;
        stored[start][end] = big_num(right_result);
        is_stored[start][end] = 1;
        return right_result;
    }
    else
    {
        delete[] right_result;
        stored[start][end] = big_num(left_result);
        is_stored[start][end] = 1;
        return left_result;
    }
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
        is_stored = new int* [n + 1];

        for (int j = 0; j < n + 1; j++)
        {
            is_stored[j] = new int[n + 1];
            memset(is_stored[j], 0, (n + 1) * sizeof(int));
        }

        stored = new int** [n + 1];

        for (int j = 0; j < n + 1; j++)
        {
            stored[j] = new int*[n + 1];
        }


        result = add(result, dp(map[i], 0, n, 1));

        delete[] stored;
        delete[] is_stored;
    }

    print(result);

    return 0;
}