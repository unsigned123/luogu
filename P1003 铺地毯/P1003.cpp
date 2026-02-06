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

int *a, *b, *c, *d;
int n, x, y;

bool is_legal(int _a, int _b, int _c, int _d)
{
    if (_a <= x && x <= _c && _b <= y && y <= _d)
        return true;
    else
        return false;
}

int main() {
    cin >> n;

    a = new int[n];
    b = new int[n];
    c = new int[n];
    d = new int[n];

    for (int i = 0; i < n; i++)
    {
        int g, k;
        cin >> a[i] >> b[i] >> g >> k;
        c[i] = a[i] + g;
        d[i] = b[i] + k;
    }


    cin >> x >> y;

    int found = -2;

    for (int i = n - 1; i >= 0; i--)
    {
        if (!is_legal(a[i], b[i], c[i], d[i]))
            continue;
        else
        {
            found = i;
            break;
        }
    }

    cout << found + 1;

    return 0;
}