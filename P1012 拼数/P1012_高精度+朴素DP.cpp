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

#define LEN 500

int* big_num(int n = 0, int base = 10)
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

int* add(int* a, int* b, int base = 10)
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
int* mul(int* a, int b, int base = 10)
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
void print(int* num, int base = 10)
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

int get_size(int* num, int base = 10)
{
    int i;
    for (i = LEN - 1; i > 0; i--)
        if (num[i] != 0)
            break;

    return i + 1;
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

int* numcat(int* a, int* b)
{
    int* c = big_num();
    memcpy(c, b, sizeof(int) * LEN);
    int len = get_size(b);
    //此处是size(a)!!
    memcpy(c + len, a, sizeof(int) * get_size(a));
    return c;
}

int** numbers;
int** dp;
int** pow10;

int* multi_num_cat(vector<int>& indexes)
{
    int* result = big_num(numbers[indexes[0]]);


    for (int i = 1; i < indexes.size(); i++)
    {
        int* old_result = result;
        result = numcat(result, numbers[indexes[i]]);
        delete[] old_result;
    }
    return result;
}

void find_insert(vector<int>& indexes, int num_index)
{
    vector<int*> results;
    for (int i = 0; i <= indexes.size(); i++)
    {
        indexes.insert(indexes.begin() + i, num_index);
        results.push_back(multi_num_cat(indexes));
        indexes.erase(indexes.begin() + i);
    }
    auto index = max_element(results.begin(), results.end(), less_) - results.begin();
    indexes.insert(indexes.begin() + index, num_index);
    for (int i = 0; i < results.size(); i++)
    {
        delete[] results[i];
    }
}



int main() {
    int n;
    cin >> n;
    
    int a;



    numbers = new int* [n];
    vector<int> dp;
    //注意：过大的resize会使得dp多出很多0
    dp.resize(1);

    for (int i = 0; i < n; i++)
    {
        cin >> a;
        numbers[i] = big_num(a);
    }

    dp[0] = 0;
    for (int i = 1; i < n; i++)
    {
        find_insert(dp, i);
    }

    print(multi_num_cat(dp));
    return 0;
}