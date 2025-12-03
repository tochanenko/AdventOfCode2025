//
// Created by Vladyslav Tochanenko on 03.12.2025.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "../utils/utils.h"

using namespace std;

long long highest_between_12(const long long highest, const long long new_number, const int batteries) {
    long long current_highest = highest;
    for (int i = 0; i < batteries; i++) {
        const long long temp = stoll(to_string(highest).erase(i, 1) + to_string(new_number));
        if (temp > current_highest) current_highest = temp;
    }
    return current_highest;
}

long long highest_joltage(const string& line, const int batteries) {
    long long highest = stoll(line.substr(0, batteries));
    for (int i = batteries; i < line.size(); i++) {
        highest = highest_between_12(highest, line[i] - 48, batteries);
    }
    return highest;
}

int main() {
    string path = "../day03/input.txt";
    vector<string> lines = readLines(path);

    long long total = 0L;

    for (const auto& line : lines) {
        long long highest = highest_joltage(line, 12);
        total += highest;
    }

    cout << total << endl;

    return 0;
}
