#include <iostream>
#include <chrono>
#include "ParseOBJ.h"

int main() {
    // Get starting timepoint
    std::string filePath;
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "Input Path of OBJ File to Simplify" << std::endl;

    getline (std::cin, filePath);
    ParseObjFile(filePath);
    std::cout << "Staring OBJ File Read!" << std::endl;

    // Get ending timepoint
    auto stop = std::chrono::high_resolution_clock::now();

    // Get duration. Substart timepoints to get durarion.
    auto duration = duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Execution Time: " << duration.count() << " microseconds" << std::endl;
    return 0;
}