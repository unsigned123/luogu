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

vector<vector<string>> table;
unordered_map<char, int> map;
vector<char> identifiers;
unordered_map<char, int> id_to_index;
vector<int> value_to_index;

int main() {
    int n;

    //(n-1)进制

    cin >> n;

    char plus;
    cin >> plus;

    string all_identifiers;

    for (int i = 0; i < n - 1; i++)
    {
        char identifier;
        cin >> identifier;
        identifiers.push_back(identifier);
        all_identifiers += identifier;
        map[identifier] = -1;
        id_to_index[identifier] = i;
    }
    int index0 = -1, index1 = -1;
    table.resize(n - 1);
    for (int i = 0; i < n - 1; i++)
    {
        table[i].resize(n - 1);
        char c; cin >> c;
        string single_line = "";
        for (int j = 0; j < n - 1; j++)
        {
            cin >> table[i][j];
            single_line += table[i][j];

            if (single_line == all_identifiers)
                index0 = i;
            if (table[i][j].size() == 2)
                index1 = id_to_index[table[i][j][0]];
        }
    }

    value_to_index.resize(n - 1);

    value_to_index[0] = index0;
    value_to_index[1] = index1;

    for (int i = 2; i < n - 1; i++)
    {
        value_to_index[i] = id_to_index[table[index1][value_to_index[i - 1]][0]];
        
    }

    unordered_map<char, int> id_to_value;

    for (auto id : identifiers)
    {
        int i = 0;
        for (i = 0; i < n; i++)
        {
            if (id_to_index[id] == value_to_index[i])
                break;
        }
        id_to_value[id] = i;
    }


    vector<string> deduct;
    deduct.resize(2 * n - 2);

    for (int i = 0; i <= n - 2; i++)
        deduct[i] = all_identifiers[value_to_index[i]];

    for (int i = n - 1; i <= 2 * n - 4; i++)
    {
        deduct[i] = "  ";
        deduct[i][0] = all_identifiers[value_to_index[1]];
        deduct[i][1] = all_identifiers[value_to_index[i % (n - 1)]];
    }

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (deduct[id_to_value[identifiers[i]] + id_to_value[identifiers[j]]] != table[i][j])
                goto error;
        }
    }

    for (auto id : identifiers)
    {
        cout << id << "=" << id_to_value[id] << ' ';
    }

    cout << endl;
    cout << n - 1;

    return 0;

error:
    cout << "ERROR!";
    return 0;
}