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

#define LEN 100

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

void print(int* num, int base = 1000)
{
    int i = LEN - 1;
    for (; i >= 0; i--)
        if (num[i] != 0)
            break;

    cout << num[i--];

    for (; i >= 0; i--)
    {
        cout << setw(log10(base)) << setfill('0') << num[i];
    }
    cout << endl;
}

int* add(int* a, int* b, int base = 1000)
{
    int* c = big_num();
    int carry = 0;
    for (int i = 0; i < LEN; i++)
    {
        carry += a[i] + b[i];
        c[i] = carry % base;
        carry /= base;
    }
    return c;
}

int* mul(int* a, int b, int base = 1000)
{
    int* c = big_num();
    int carry = 0, i;
    for (i = 0; i < LEN - 1; i++)
    {
        carry += a[i] * b;
        c[i] = carry % base;
        carry /= base;
    }
    while (carry)
    {
        c[i++] = carry % base;
        carry /= base;
    }
    return c;
}

int** factorial;

int main() {
    int n;
    cin >> n;

    factorial = new int* [n];
    factorial[0] = big_num(1);
    for (int i = 0; i < n - 1; i++)
    {
        factorial[i + 1] = mul(factorial[i], i + 2);
    }
    int* sum = big_num();
    for (int i = 0; i < n; i++)
    {
        sum = add(sum, factorial[i]);
    }
    print(sum);
    return 0;
}