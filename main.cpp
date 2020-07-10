#include <iostream>
#include <chrono>
#include "readObj.h"

int main() {
    std::vector<int> values(10000);

    // Get starting timepoint
    auto start = std::chrono::high_resolution_clock::now();

    std::cout << "Staring OBJ File Read!" << std::endl;
    ParseObjFile();

    // Get ending timepoint
    auto stop = std::chrono::high_resolution_clock::now();

    // Get duration. Substart timepoints to
    // get durarion. To cast it to proper unit
    // use duration cast method
    auto duration = duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Execution Time: " << duration.count() << " microseconds" << std::endl;
    return 0;
}