//
// Created by Vladyslav Tochanenko on 06.12.2025.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "../utils/utils.h"

using namespace std;

vector<string> parse_string_by_whitespace(const string& input) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;

    while (ss >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

vector<long long> convert_vector_to_ll(const vector<string>& input) {
    vector<long long> output;
    output.reserve(input.size());
    for (const string& el : input) {
        output.push_back(stoll(el));
    }
    return output;
}

int main() {
    const string path = "../day06/input.txt";
    const vector<string> lines = readLines(path);
    const int NUMBERS = lines.size() - 1;

    vector<vector<long long>> numbers;
    numbers.reserve(NUMBERS);
    for (int i = 0; i < NUMBERS; i++) {
        numbers.push_back(convert_vector_to_ll(parse_string_by_whitespace(lines[i])));
    }

    vector<string> operators = parse_string_by_whitespace(lines.back());

    long long res = 0;

    for (int i = 0; i < operators.size(); i++) {
        if (operators[i] == "+") {
            for (int j = 0; j < NUMBERS; j++) {
                res += numbers[j][i];
            }
        } else {
            long long temp = numbers[0][i];
            for (int j = 1; j < NUMBERS; j++) {
                temp *= numbers[j][i];
            }
            res += temp;
        }
    }

    cout << res << endl;

    return 0;
}
