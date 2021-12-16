//
// Created by Andrew Li on 12/10/21.
//

#include <fstream>
#include <string>
#include <vector>

int main() {
    std::ifstream input {"input" };
    if (!input) {
        return 1;
    }

    std::vector<int> nums {};
    std::string line;
    while (std::getline(input, line)) {
        nums.push_back(std::stoi(line));
    }

    int numIncreased = 0;
    for (int i = 3; i < nums.size(); i++) {
        int temp = nums.at(i - 2) + nums.at(i - 1);
        int lastSum = nums.at(i - 3) + temp;
        int currSum = temp + nums.at(i);

        if (currSum > lastSum) {
            numIncreased++;
        }
    }
    std::cout << numIncreased << std::endl;
    return 0;
}
