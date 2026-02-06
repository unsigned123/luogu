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

int l, n;
int* pos;

int main() {
    cin >> l >> n;

    pos = new int[n];

    for (int i = 0; i < n; i++)
    {
        cin >> pos[i];
    }

    int min_result = 0, max_result = 0;

    for (int i = 0; i < n; i++)
    {
        min_result = max(min(l + 1 - pos[i], pos[i]), min_result);
        max_result = max(max(l + 1 - pos[i], pos[i]), max_result);
    }

    cout << min_result << ' ' << max_result;

    return 0;
}