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

void print(int num)
{
    vector<int> component;
    for (int i = 1, j = 0; i < 1048576; i <<= 1, j++)
        if (num & i)
            component.push_back(j);

    reverse(component.begin(), component.end());

    for (int i = 0; i < component.size(); i++)
    {
        auto c = component[i];
        if (c == 0)
            cout << "2(0)";
        else if (c == 1)
            cout << "2";
        else
        {
            cout << "2(";
            print(c);
            cout << ")";
        }

        if (i != component.size() - 1)
            cout << "+";
    }
}

int main() {
    int n;
    cin >> n;
    print(n);
    return 0;
}