#ifndef STRINGCONSTRUCTION_H
#define STRINGCONSTRUCTION_H

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
using std::string;
using std::vector;

//Method from
//https://cp-algorithms.com/string/z-function.html
vector<size_t> ZFunction(const string & s) {
    size_t n = s.length();
    vector<size_t> z(n);
    for (size_t i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) {
            z[i] = std::min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

size_t BestClone(const std::string & s) {
    string r{ s };
    reverse(r.begin(), r.end());
    auto z = ZFunction(r);
    size_t best = 0;
    for (size_t i = 0; i < z.size(); i++) {
        best = std::max(best, std::min(z[i], i));
    }
    return s.length() - best;
}

int stringConstruction(const string & s, int clone_cost, int append_cost) {
    vector<int> costs = { 0 };
    costs.reserve(s.size());
    for (size_t j = 0; j < s.length(); j++) {
        size_t i = BestClone(string(s.substr(0, j + 1)));
        if (i <= j) {
            costs.push_back(
                    std::min(costs.back() + append_cost, costs[i] + clone_cost));
        }
        else {
            costs.push_back(costs.back() + append_cost);
        }
    }
    return costs.back();
}
// do not write or edit anything below this line

#endif