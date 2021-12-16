//
// Created by Andrew Li on 12/10/21.
//

#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream input {"input" };
    if (!input) {
        return 1;
    }

    bool firstLine = true;
    int lastMeasurement = 0;
    int numIncreased = 0;
    std::string line;
    while (std::getline(input, line)) {
        int currMeasurement = std::stoi(line);
        if (!firstLine) {
            int diff = currMeasurement - lastMeasurement;
            if (diff > 0) {
                numIncreased++;
            }
        }
        lastMeasurement = currMeasurement;
        firstLine = false;
    }
    std::cout << numIncreased << std::endl;
    return 0;
}
