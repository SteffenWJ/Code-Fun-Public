#include <fstream>
#include <iostream>
#include <string>

// Used for Part Day 1 Part 1
struct safeOpeningLogic {
    int& safeValue;
    int& counter;
    void spinRight(int step) {  // Right on the dial should increase the number
        safeValue = (safeValue + step) % 100; // Modulus is used to wrap the number
        if (safeValue == 0) {
            counter++;
        }
    }
    void spinLeft(int step) {   // Left on the dial should decrease the number
        safeValue = (safeValue - step + 100) % 100;
        if (safeValue == 0) {
            counter++;
        }
    }
};
// Used for Part Day 1 Part 2
struct safeOpeningLogicBrute {
    // I was having some issues so i brute forced the solution
    int& safeValue;
    int& counter;

    void bruteSpinLeft(int step) {
        for (int i = 0; i < step; ++i) {
            if (safeValue == 0) {
                safeValue = 99; //Wrapping around
            } else {
                --safeValue;
            }
            // This is my solution to an earlier problem. I was counting WHEN I left 0 instead of when I landed on Zero.
            if (safeValue == 0) {
                ++counter;
            }
        }
    }
    void bruteSpinRight(int step) {
        for (int i = 0; i < step; ++i) {
            if (safeValue == 99) {
                safeValue = 0;
            } else {
                ++safeValue;
            }
            if (safeValue == 0) {
                ++counter;
            }
        }
    }
};

int main() {
    std::cout << "Day 01 starting!" << std::endl;
    std::string inputFilePath = "";

    // Opening the input .txt file
    std::ifstream file(inputFilePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file\n";
        return 1;
    }

    // Starting safe position and counter, they will be passed as a reference in the objects
    int safePositionPart1 = 50;
    int safePositionPart2 = 50;
    int counterPart1 = 0;
    int counterPart2 = 0;
    safeOpeningLogic safePart1(safePositionPart1,counterPart1);
    safeOpeningLogicBrute safePart2(safePositionPart2,counterPart2);
    std::string line;
    while (std::getline(file, line)) {
        char direction = line[0];
        int steps = std::stoi(line.substr(1)); // Converts the sub-string into an int.
        if (direction == 'L') {
            safePart1.spinLeft(steps);
            safePart2.bruteSpinLeft(steps);
        } else if (direction == 'R') {
            safePart1.spinRight(steps);
            safePart2.bruteSpinRight(steps);
        }
    }
    std::cout << "Part 1 - The dial hit Zero : " << counterPart1 << " times\n";
    std::cout << "Part 2 - The dial passed Zero : " << counterPart2 << " times\n";

    return 0;
}
