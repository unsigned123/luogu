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

int a, n, m, x;


int main() {
    cin >> a >> n >> m >> x;

    int* fib = new int[30];

    fib[0] = fib[1] = 1;

    for (int i = 2; i < 30; i++)
        fib[i] = fib[i - 1] + fib[i - 2];

    int y = (m - a * (fib[n - 4] + 1)) / (fib[n - 3] - 1);

    if (x >= 3)
    {
        cout << a * (fib[x - 3] + 1) + (fib[x - 2] - 1) * y;
    }
    else
        cout << a;

    return 0;
}