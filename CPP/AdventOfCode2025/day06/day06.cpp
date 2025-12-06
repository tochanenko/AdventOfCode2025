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

const bool DEBUG = false;

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

// ne marche pas
vector<string> transform(const vector<string>& lines) {
    if (lines.size() < 2) return lines;

    long long rows = lines.size() - 1;
    long long cols = lines[0].size();
    long long cycle = rows + 1;

    vector result(rows, string(cols, ' '));

    for (long long j = 0; j < cols; j++) {
        long long local_row = j % cycle;
        if (local_row < rows) {
            long long block_start = j - local_row;
            for (long long i = 0; i < rows; i++) {
                result[i][j] = lines[local_row][block_start + i];
            }
        } else {
            for (long long i = 0; i < rows; i++) {
                result[i][j] = lines[i][j];
            }
        }
    }

    result.push_back(lines.back());
    return result;
}

void part_1(vector<string> lines) {
    const long long NUMBERS = lines.size() - 1;

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
}

void part_2(vector<string> lines) {
    long long res = 0;
    const int size = lines[0].length();
    long long i = 0;
    while (i < size) {
        // Get length of chunk
        bool block_started = false;
        int temp_size = 0;
        for (; i < size; i++) {
            if (DEBUG) cout << "; Looking at : [" << lines[lines.size() - 1][i] << "]" << endl;
            if (lines[lines.size() - 1][i] == ' ') {
                temp_size++;
            } else if (!block_started) {
                temp_size++;
                block_started = true;
            } else {
                break;
            }
        }
        if (DEBUG) cout << "Current i: " << i << "; Current size: " << size << endl;
        if (i == size) {
            temp_size++;
            i++;
        }
        if (DEBUG) cout << temp_size << endl;

        // Get all numbers
        vector<string> numbers(temp_size, string(1, ' '));
        for (int j = 0; j < temp_size; j++) {
            for (int k = 0; k < lines.size() - 1; k++) {
                numbers[j] += lines[k][i - temp_size + j];
            }
        }

        if (DEBUG) cout << "Operator: " << lines[lines.size() - 1][i - temp_size] << endl;

        vector<long long> parsed_numbers;
        parsed_numbers.reserve(lines.size() - 1);
        for (int j = 0; j < temp_size - 1; j++) {
            string str = numbers[j];
            erase_if(str, [](unsigned char x) {
                return isspace(x);
            });
            parsed_numbers.push_back(stoll(str));
        }

        if (DEBUG) cout << "Parsed numbers: " << endl;
        for (long long number : parsed_numbers) {
            if (DEBUG) cout << "\t" << number << endl;
        }
        if (DEBUG) cout << endl;

        // Calculate result for operation
        long long temp_res = parsed_numbers[0];
        if (lines[lines.size() - 1][i - temp_size] == '+') {
            for (int j = 1; j < temp_size - 1; j++) {
                temp_res += parsed_numbers[j];
            }
        } else {
            for (int j = 1; j < temp_size - 1; j++) {
                temp_res *= parsed_numbers[j];
            }
        }

        if (DEBUG) cout << "Adding : " << temp_res << endl << endl << endl;
        res += temp_res;
    }

    cout << "Res: " << res << endl;
}

int main() {
    const string path = "../day06/input.txt";
    // const vector<string> lines = transform(readLines(path));
    const vector<string> lines = readLines(path);

    part_2(lines);

    return 0;
}
