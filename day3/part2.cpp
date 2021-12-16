//
// Created by Andrew Li on 12/11/21.
//

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <math.h>

int decimalFromBinaryString(std::string binStr) {
    int acc = 0;
    for (int i = 0; i < binStr.size(); i++) {
        acc += (binStr[i] == '1' ? 1 : 0) * pow(2, binStr.size() - i - 1);
    }
    return acc;
}

int main() {
    std::fstream input { "input" };
    if (!input) {
        return 1;
    }

    std::vector<std::string> lines {};
    std::string line;
    while (std::getline(input, line)) {
        lines.push_back(line);
    }

    std::vector<std::string> mostCommon = lines;
    std::vector<std::string> leastCommon = lines;
    for (int i = 0; i < line.size(); i++) {
        int mostOnes { 0 };
        int mostSize = mostCommon.size();
        if (mostSize > 1) {
            for (int j = 0; j < mostSize; j++) {
                mostOnes += (mostCommon[j][i] == '1' ? 1 : 0);
            }
            std::erase_if(mostCommon, [mostOnes, i, mostSize](std::string line) {
                char bit = mostOnes >= mostSize - mostOnes ? '1' : '0';
                return line[i] != bit;
            });
        }

        int leastOnes { 0 };
        int leastSize = leastCommon.size();
        if (leastSize > 1) {
            for (int j = 0; j < leastCommon.size(); j++) {
                leastOnes += (leastCommon[j][i] == '1' ? 1 : 0);
            }
            std::erase_if(leastCommon, [leastOnes, i, leastSize](std::string line) {
                char bit = leastOnes < leastSize - leastOnes ? '1' : '0';
                return line[i] != bit;
            });
        }
    }
    int oxygenRating { decimalFromBinaryString(mostCommon[0]) };
    int scrubberRating { decimalFromBinaryString(leastCommon[0]) };
    std::cout << oxygenRating * scrubberRating << std::endl;

    return 0;
}