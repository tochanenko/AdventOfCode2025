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

int remove_until_finished(string* map, int size) {
    int res = 0;
    bool finished = false;
    do {
        finished = true;
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
                if (surrounding_rolls < 4) {
                    res++;
                    map[i][j] = '.';
                    finished = false;
                }
            }
        }
    } while (!finished);
    return res;
}

int main() {
    string path = "../day04/input.txt";
    vector<string> lines = readLines(path);

    if (lines.empty()) return 1;

    const int size = lines.size() + 2;
    auto* map = new string[size];
    string border(size + 2, '.');
    map[0] = border;
    map[size - 1] = border;

    for (int i = 0; i < lines.size(); i++) {
        map[i + 1] = "." + lines[i] + ".";
    }

    cout << remove_until_finished(map, size) << endl;

    delete[] map;
    return 0;
}
