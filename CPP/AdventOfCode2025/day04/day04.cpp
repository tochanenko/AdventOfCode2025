//
// Created by Vladyslav Tochanenko on 03.12.2025.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "../utils/utils.h"

using namespace std;



int count_rolls(string* map, int size) {
    int res = 0;
    for (int i = 1; i < size - 1; i++) {
        for (int j = 1; j < size - 1; j++) {
            if (map[i][j] != '@') continue;
            int surrounding_rolls = 0;
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    if (k == 0 && l == 0) continue;
                    if (map[i + k][j + l] == '@') surrounding_rolls++;
                }
            }
            if (surrounding_rolls < 4) res++;
        }
    }
    return res;
}

int main() {
    string path = "../day04/input.txt";
    vector<string> lines = readLines(path);

    const int size = lines.size() + 2;

    auto* map = new string[size];

    for (int i = 1; i < size; i++) {
        map[i] = "." + lines[i - 1] + ".";
    }
    for (int i = 0; i < size; i++) {
        map[0][i] = map[size - 1][i] = '.';
    }

    cout << count_rolls(map, size) << endl;

    return 0;
}
