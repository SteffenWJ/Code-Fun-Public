#include <fstream>
#include <iostream>
#include <string>
#include <vector>

constexpr int MAP_SIZE = 136; //This should fit with the input being 136x136

// Custom struct to keep the data type
struct Coordinate {
    int x;
    int y;
    bool paper;

    //Constructor
    Coordinate(int xIntial = 0, int yIntial = 0, bool paperIntial = false)
        : x(xIntial), y(yIntial), paper(paperIntial) {}
};

//Check predefined coordinates and handle any issues with out of bounds
bool lookAround(const std::vector<std::vector<Coordinate>>& map, const std::vector<std::pair<int,int>>& checkArea, int x, int y) {
    int ammountFound = 0;
    for (auto [dx, dy] : checkArea) {
        int lookX = x + dx;
        int lookY = y + dy;
        if (lookX >= 0 && lookX < MAP_SIZE &&
            lookY >= 0 && lookY < MAP_SIZE)
        {
            if (map[lookY][lookX].paper) {
                ammountFound ++;
            }
        }
    }
    if (ammountFound < 4) {
        return true;
    }
    return false;
}

// Helper function so i could see if it loaded the map
void printMap(const std::vector<std::vector<Coordinate>>& grid)
{
    for (int y = 0; y < MAP_SIZE; y++) {
        for (int x = 0; x < MAP_SIZE; x++) {
            std::cout << (grid[y][x].paper ? 'X' : '.');
            if (x < MAP_SIZE - 1) std::cout << ' ';
        }
        std::cout << '\n';
    }
}

// Creates the map
void loadMap(std::ifstream& file, std::vector<std::vector<Coordinate>>& grid) {
    std::string line;
    int y = 0;
    while (std::getline(file, line) && y < MAP_SIZE) {
        for (int x = 0; x < line.length() && x < MAP_SIZE; x++) {
            bool paper = (line[x] == '@');
            grid[y][x] = Coordinate(x, y, paper);
        }
        y++;
    }
}

// This is for part 1, leaving it as is
int howManyPapersCanBeMoved(const std::vector<std::vector<Coordinate>>& map, const std::vector<std::pair<int,int>>& checkArea) {
    int howManyPapers = 0;

    for (int x = 0; x < MAP_SIZE; ++x) {
        for (int y = 0; y < MAP_SIZE; ++y) {
            if (map[y][x].paper) {
                if (lookAround(map, checkArea, x, y)) {
                    howManyPapers++;
                }
            }
        }
    }
    return howManyPapers;
}

// Extended version for part 2
int howManyPapersCanBeMovedExtended(const std::vector<std::vector<Coordinate>>& mapOld, std::vector<std::vector<Coordinate>>& mapNew, const std::vector<std::pair<int,int>>& checkArea, int amountOfPaperInit) {
    int amountOfPaper = amountOfPaperInit;
    for (int x = 0; x < MAP_SIZE; ++x) {
        for (int y = 0; y < MAP_SIZE; ++y) {
            if (mapOld[y][x].paper) {
                if (lookAround(mapOld, checkArea, x, y)) {
                    amountOfPaper++;
                    mapNew[y][x].paper = false;  //This is all that is needed
                }
            }
        }
    }
    return amountOfPaper;
}


int main() {
    std::cout << "Day 04 starting!" << std::endl;
    std::string inputFilePath = "";

    // Opening the input .txt file
    std::ifstream file(inputFilePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file\n";
        return 1;
    }

    // To make sure i don't forget a part
    // [-1,-1][0,-1][1,-1]
    // [-1, 0][0, 0][1, 0]  //Remember we don't need origo
    // [-1, 1][0 ,1][1, 1]
    
    // Defined here ones so i can pass it as a refrence
    std::vector<std::pair<int,int>> lookAroundCoordinates = {
        {-1,-1},{0,-1},{1,-1},
        {-1,0},{1,0},
        {-1,1},{0,1},{1,1}
    };

    //Makes a default FALSE initialized vector of vectors. Could likely reduce this to not use the Coordinate struct
    std::vector<std::vector<Coordinate>> printingDepartmentMap(
        MAP_SIZE,
        std::vector<Coordinate>(MAP_SIZE)
    );

    loadMap(file,printingDepartmentMap);
    int result = howManyPapersCanBeMoved(printingDepartmentMap, lookAroundCoordinates);
    //printMap(printingDepartmentMap);
    std::cout << "Part 1: The number of papers that can be moved is: " << result << "\n";

    // These are made for part 2.
    // We can use every thing we have, but we need to extend a small part so that any removed paper is noted on the new map
    // There is no reason to remove papers it from the original map as we are removing them in steps.
    std::vector<std::vector<Coordinate>> printingDepartmentMapOld = printingDepartmentMap;
    std::vector<std::vector<Coordinate>> printingDepartmentMapNew = printingDepartmentMap;

    int safetyCounter = 0; // Not needed, but always smart to have a big dumb stop to the loop
    int oldPapers = 0;
    int newPapers = -9; //Dumb mistake not to set them to different values
    bool moreToMove = true;
    while (safetyCounter < 5000 && moreToMove) {
        newPapers = howManyPapersCanBeMovedExtended(printingDepartmentMapOld, printingDepartmentMapNew, lookAroundCoordinates, oldPapers);
        if (newPapers == oldPapers) {
            moreToMove = false;
        }
        oldPapers = newPapers;
        printingDepartmentMapOld = printingDepartmentMapNew;
        safetyCounter ++;
    }

    std::cout << "Part 2: The number of papers that can be moved is: " << newPapers << " and it took " << safetyCounter << " times\n";

    return 0;
}
