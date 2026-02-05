#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <ranges>
#include <set>

// For Part 1
int howManyFreshIngredients(std::vector<std::pair<long long,long long>>& theRanges, std::vector<long long>& theIngredients) {
    int totalAmount = 0;
    for (auto ingredient : theIngredients) {
        for (auto [lowRange,highRange] : theRanges) {
            if (lowRange <= ingredient && ingredient <= highRange) {
                totalAmount++;
                break;
            }
        }
    }
    return totalAmount;
}

// For Part 2
long long howManyValuesInRange(std::vector<std::pair<long long,long long>>& ranges) {
    if (ranges.empty()) return 0;

    std::sort(ranges.begin(), ranges.end());  // sort by (first, then second)

    long long totalAmount = 0;
    long long currentLow = ranges[0].first;
    long long currentHigh = ranges[0].second;

    for (size_t i = 1; i < ranges.size(); ++i) {
        auto [lowRange, highRange] = ranges[i];

        if (lowRange <= currentHigh + 1) {
            if (highRange > currentHigh) currentHigh = highRange;
        } else {
            totalAmount += (currentHigh - currentLow + 1);   // The +1 Is so the value includes the high range
            currentLow = lowRange;
            currentHigh = highRange;
        }
    }
    totalAmount += (currentHigh - currentLow + 1);
    return totalAmount;
}


int main() {
    std::cout << "Day 05 starting!" << std::endl;
    std::string inputFilePath = "";

    // Opening the input .txt file
    std::ifstream file(inputFilePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file\n";
        return 1;
    }
    std::string line;
    bool secoundPart = false;
    int count = 0;
    std::vector<std::pair<long long,long long>> idRanges;
    std::vector<long long> ingredientIds;
    while (std::getline(file, line)) {
        //std::cout << line << std::endl;
        if (line == "") {
            //std::cout << "Found empty setting toggle\n";
            //std::cout << count << std::endl;
            secoundPart = true;
            continue; //Clever trick to make it skip one forward
        }
        if (not secoundPart) {
            std::vector<std::string> splitContainer; //Overwrites the container freeing it.
            for (auto part : std::views::split(line, std::string{"-"}) ) { //Was thinking to use regex, but this seemed cleaner.
                splitContainer.emplace_back(part.begin(), part.end());
            }
            long long from = std::stoll(splitContainer[0]); //String to Long Long
            long long to   = std::stoll(splitContainer[1]);

            idRanges.emplace_back(from, to);
        } else {
            //std::cout << line << std::endl;
            long long value = std::stoll(line);
            ingredientIds.push_back(value);
        }
    }
    int part1Result = howManyFreshIngredients(idRanges, ingredientIds);
    long long part2Result = howManyValuesInRange(idRanges);
    std::cout << "Part 1 - The amount of ingredients that are fresh is " << part1Result << "\n";
    std::cout << "Part 2 - Number of fresh ID's " << part2Result << "\n";
    return 0;
}
