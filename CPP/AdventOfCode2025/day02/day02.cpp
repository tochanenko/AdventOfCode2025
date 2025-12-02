//
// Created by Vladyslav Tochanenko on 01.12.2025.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "../utils/utils.h"

using namespace std;

vector<long long> generate_halfs(int decimals) {
    vector<long long> numbers;

    long long start = static_cast<long long>(pow(10, decimals - 1));
    long long end = static_cast<long long>(pow(10, decimals)) - 1;
    numbers.reserve(end - start + 1);

    for (long long i = start; i <= end; ++i) {
        numbers.push_back(i);
    }

    return numbers;
}

vector<long long> generate_numbers(int decimals) {
    vector<long long> numbers;

    for (int i = 1; i <= decimals; ++i) {
        vector<long long> base_numbers = generate_halfs(i);

        long long multiplier = static_cast<long long>(pow(10, i));

        for (long long num : base_numbers) {
            long long new_num = (num * multiplier) + num;
            numbers.push_back(new_num);
        }
    }

    return numbers;
}

int number_of_digits(long long number) {
    int res = 0;
    while (number != 0) {
        res++;
        number /= 10;
    }
    return res;
}

int main() {
    string path = "../day02/input.txt";
    vector<string> lines = readLines(path);
    vector<string> values = split(lines[0], ',');

    long long max = 0;

    for (const auto& value : values) {
        vector<string> range = split(value, '-');
        if (stoll(range[0]) > max) max = stoll(range[0]);
        if (stoll(range[1]) > max) max = stoll(range[1]);
    }

    vector<long long> incorrect_ids = generate_numbers(number_of_digits(max) / 2);

    long long res = 0;

    for (const auto& value: values) {
        vector<string> range = split(value, '-');
        long long left = stoll(range[0]);
        long long right = stoll(range[1]);
        for (long long incorrect_id : incorrect_ids) {
            if (left <= incorrect_id && incorrect_id <= right) {
                res += incorrect_id;
            }
        }
    }

    cout << res << endl;

    return 0;
}
