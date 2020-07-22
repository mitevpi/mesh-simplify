#include <iostream>
#include <chrono>
#include "ParseOBJ.h"

int main() {
    // Get starting time
    std::string filePath;
    std::cout << "Input Path of OBJ File to Simplify" << std::endl;

    getline (std::cin, filePath);
    std::cout << "Staring OBJ File Read!" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    ParseObjFile(filePath);

    // Get ending time and compute duration
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Execution Time: " << duration.count() << " microseconds" << std::endl;
    return 0;
}