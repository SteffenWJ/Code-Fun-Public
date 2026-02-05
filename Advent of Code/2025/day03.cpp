#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <unordered_set>

int getLargestJolt(std::string &batteryBank) {
    int largestA = -999, indexA = -999;
    int largestB = -999, indexB = -999;
    std::string largestJolt;
    int tempDigit;
    bool switched = false;
    for (int i = 0; i < batteryBank.size(); ++i) {
        tempDigit = batteryBank[i] - '0';
        /* Smart trick to making it into a digit works by using asci info.
        For Example lets say the char is '7' then the ASCII code is 55 and the ASCII for '0' is 48
        So 55-48 = 7. Clever trick to convert to int.
        */
        if (tempDigit > largestA) {
            largestA = tempDigit;
            indexA = i;
        }
    }

    // Quick check if we are at last digit.
    if (indexA == batteryBank.size()-1) {
        switched = true;
        for (int i = 0; i < batteryBank.size()-1; ++i) {
            tempDigit = batteryBank[i] - '0';
            if (tempDigit > largestB && i != indexA) { //We skip if the index for i is the same as the one found for A
                largestB = tempDigit;
                indexB = i;
            }
        }
    } else {
        for (int i = indexA+1; i < batteryBank.size(); ++i) {
            tempDigit = batteryBank[i] - '0';
            if (tempDigit > largestB && i != indexA) { //We skip if the index for i is the same as the one found for A
                largestB = tempDigit;
                indexB = i;
            }
        }
    }
    if (switched) {
        largestJolt = std::string() + batteryBank[indexB] + batteryBank[indexA];
    } else {
        largestJolt = std::string() + batteryBank[indexA] + batteryBank[indexB];
    }
    return std::stoi(largestJolt);
};

int main() {
    std::cout << "Day 03 starting!" << std::endl;

    std::string inputFilePath = "";

    // Opening the input .txt file
    std::ifstream file(inputFilePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file\n";
        return 1;
    }

    std::string line;
    std::vector<int> batterJolts;
    int results;
    while (std::getline(file, line)) {
        //std::cout << line.size() << std::endl;
        //std::cout << line << std::endl;
        results = getLargestJolt(line);
        batterJolts.push_back(results);
    }
    int sumOfJolts = 0;
    for (int value : batterJolts) {
        std::cout << value << std::endl;
        sumOfJolts += value;
    }

    std::cout << "The Sum of Jolts for the batter was " << sumOfJolts << ": Correct Answer was 17158\n";

    return 0;
}
