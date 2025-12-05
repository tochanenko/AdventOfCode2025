//
// Created by Vladyslav Tochanenko on 03.12.2025.
//

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "../utils/utils.h"

using namespace std;

vector<pair<long long, long long>> good_products;
vector<long long> products;

void init_freezer(vector<string>& lines) {
    bool good_products_finished = false;
    for (const string& line : lines) {
        if (line.empty()) {
            good_products_finished = true;
            continue;
        }

        if (!good_products_finished) {
            const int delimiter_pos = line.find('-');
            good_products.emplace_back(
                stoll(line.substr(0, delimiter_pos)),
                stoll(line.substr(delimiter_pos + 1))
                );
        } else {
            products.push_back(stoll(line));
        }
    }
    sort(good_products.begin(), good_products.end());
    sort(products.begin(), products.end());
}

void squash_good_products() {
    vector<pair<long long, long long>> merged_ranges;
    merged_ranges.push_back(good_products[0]);

    for (size_t i = 1; i < good_products.size(); ++i) {
        pair<long long, long long>& last_merged = merged_ranges.back();
        pair<long long, long long> current_range = good_products[i];

        if (last_merged.second >= current_range.first) {
            last_merged.second = max(last_merged.second, current_range.second);
        } else {
            merged_ranges.push_back(current_range);
        }
    }

    good_products = merged_ranges;
}

int count_good_products() {
    int res = 0;
    for (long long product : products) {
        for (pair good_product: good_products) {
            if (good_product.first <= product && product <= good_product.second) {
                res++;
                break;
            }
        }
    }
    return res;
}

long long count_all_good_products() {
    long long res = 0;
    for (pair good_product: good_products) {
        res += good_product.second - good_product.first + 1;
    }
    return res;
}

int main() {
    string path = "../day05/input.txt";
    vector<string> lines = readLines(path);

    init_freezer(lines);
    squash_good_products();

    cout << count_good_products() << endl;
    cout << count_all_good_products() << endl;

    return 0;
}
