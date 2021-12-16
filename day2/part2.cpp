//
// Created by Andrew Li on 12/10/21.
//

#include <iostream>
#include <fstream>

int main() {
    std::ifstream input { "input" };
    if (!input) {
        return 1;
    }

    int horizontal = 0;
    int depth = 0;
    int aim = 0;
    std::string line;
    while (getline(input, line)) {
        int sepIndex = line.find(" ");
        std::string dir = line.substr(0, sepIndex);
        int val = std::stoi(line.substr(sepIndex));

        if (dir == "forward") {
            horizontal += val;
            depth += aim * val;
        } else if (dir == "down") {
            aim += val;
        } else if (dir == "up") {
            aim -= val;
        }
    }
    std::cout << horizontal * depth << std::endl;
    return 0;
}