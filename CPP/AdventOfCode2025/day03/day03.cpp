//
// Created by Vladyslav Tochanenko on 03.12.2025.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "../utils/utils.h"

using namespace std;

long long* pow_table;

void init_pow_table(int decimals) {
    pow_table = new long long[decimals + 1];

    pow_table[0] = 1;
    for (int i = 1; i <= decimals; i++) {
        pow_table[i] = pow_table[i - 1] * 10;
    }
}

long long highest_between_12(const long long highest, const long long new_number, const int batteries) {
    long long current_highest = highest;
    long long temp;
    for (int i = 0; i < batteries; i++) {
        temp = ((highest - highest % pow_table[batteries - i]) / 10 + highest % pow_table[batteries - i - 1]) * 10 + new_number;
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
    // correct answer: 172740584266849
    vector<string> lines = readLines(path);

    const int batteries = 12;

    init_pow_table(batteries);

    long long total = 0L;

    for (const auto& line : lines) {
        const long long highest = highest_joltage(line, batteries);
        total += highest;
    }

    cout << total << endl;

    return 0;
}
