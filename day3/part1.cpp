//
// Created by Andrew Li on 12/10/21.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

int main() {
    std::ifstream input { "input" };
    if (!input) {
        return 1;
    }

    std::vector<int> acc {};
    std::string line;
    int lines { 0 };
    while (getline(input, line)) {
        for (int i = 0; i < line.size(); i++) {
            if (acc.size() < line.size()) {
                acc.push_back(0);
            }
            if (line[i] == '1') {
                acc[i] += 1;
            }
        }
        lines++;
    }

    int gamma = 0;
    int epsilon = 0;
    for (int i = 0; i < acc.size(); i++) {
        int place = pow(2, acc.size() - i - 1);
        if (acc[i] > lines - acc[i]) { // more 1s
            gamma += place;
        } else {
            epsilon += place;
        }
    }
    std::cout << gamma * epsilon << std::endl;
    return 0;
}