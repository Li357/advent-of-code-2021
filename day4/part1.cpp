//
// Created by Andrew Li on 12/14/21.
//

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>

int runBingo(const std::vector<int>& order, const std::vector<std::unordered_map<int, int[3]>>& boards) {
    bool called[boards.size()][5][5];
    for (int i = 0; i < boards.size(); i++){
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                called[i][j][k] = 0;
            }
        }
    }

    for (auto currCalledNum : order) {
        std::cout << "CALLED " << currCalledNum << std::endl;
        for (int i = 0; i < boards.size(); i++) {
            auto currBoard = boards[i];
            currBoard[currCalledNum][2] = true;

            int row = currBoard[currCalledNum][0];
            int column = currBoard[currCalledNum][1];
            called[i][row][column] = true;
//
//            std::cout << "BOARD " << i << std::endl;
//            for (int k=0;k<5;k++){
//                for(int j=0;j<5;j++) {
//                    std::cout << called[i][k][j] << " ";
//                }
//                std::cout << "\n";
//            }
//            std::cout << "\n";

            for (int r = 0; r < 5; r++) {
                bool horizontalBingo = true;
                bool verticalBingo = true;
                for (int c = 0; c < 5; c++) {
                    horizontalBingo = horizontalBingo && called[i][r][c];
                    verticalBingo = verticalBingo && called[i][c][r];
                }

                if (horizontalBingo || verticalBingo) {
                    int uncalledSum { 0 };
                    for (const auto &[num, info] : currBoard) {
                        if (!called[i][info[0]][info[1]]) {
                            uncalledSum += num;
                            std::cout << num << " " << info[0] << " " << info[1] << std::endl;
                        }
                    }
                    std::cout << currCalledNum << " * " << uncalledSum << std::endl;
                    return currCalledNum * uncalledSum;
                }
            }
        }
    }
    return -1;
}

int main() {
    std::fstream input { "input" };
    if (!input) {
        return 1;
    }

    std::string line;
    input >> line;

    std::istringstream orderInput;
    orderInput.str(line);
    std::vector<int> order {};
    std::string currNum;
    while (std::getline(orderInput, currNum, ',')) {
        order.push_back(std::stoi(currNum));
    }

    std::getline(input, line);
    std::getline(input, line);

    int row { 0 };
    std::unordered_map<int, int[3]> currBoard; // board number -> [row, column, called?]
    std::vector<std::unordered_map<int, int[3]>> boards {};
    while (std::getline(input, line)) {
        if (line.empty()) {
            row = 0;
            boards.push_back(currBoard);
            currBoard.clear();
            continue;
        }
        int currBoardNum;
        std::istringstream lineStream;
        lineStream.str(line);
        int column { 0 };
        while (lineStream >> currBoardNum) {
            currBoard[currBoardNum][0] = row;
            currBoard[currBoardNum][1] = column;
            currBoard[currBoardNum][2] = false;
            column++;
        }
        row++;
    }
    boards.push_back(currBoard);

    int score { runBingo(order, boards) };
    std::cout << score << std::endl;

    return 0;
}
