#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <regex>
#include "Vertex.h"
#include "Face.h"

void parseObjLine(const std::string& line);
Vertex parseVertex(const std::string& x, const std::string& y, const std::string& z);
Face parseFace(const std::string& x, const std::string& y, const std::string& z);

void readObjFile() {
    int count = 0;
    std::string objLine;
    std::ifstream inFile;

    inFile.open("/Users/mitevpi/Dropbox/Work/010_Project Files/200522_Mesh Simplification/TopographyMesh.obj");

    // Terminate if file can't be opened
    if (!inFile) {
        std::cout << "Unable to open file";
        exit(1); // terminate with error
    }

    // Get lines
    while (getline(inFile, objLine)) {
        parseObjLine(objLine);
        count++;
    }

    inFile.close();
    std::cout << "Finished Reading: " << count << " Lines"  << std::endl;
}

void parseObjLine(const std::string& line){
    std::smatch objMatch;
    std::regex objRegex(R"(([vf])\s([-\d]+[\d\.]+)\s([-\d]+[\d\.]+)\s([-\d]+[\d\.]+))");
    std::string type;

    // Get regex matches
    std::regex_search(line, objMatch, objRegex);
    type = objMatch[1];

    // Convert to classes
    if (type == "v"){
        Vertex vert = parseVertex(objMatch[2], objMatch[3], objMatch[4]);
        std::cout << type << " " << vert.x << " " << vert.y << " " << vert.z << std::endl;
    }
    else if (type == "f"){
        Face fa = parseFace(objMatch[2], objMatch[3], objMatch[4]);
        std::cout << type << " " << fa.x << " " << fa.y << " " << fa.z << std::endl;
    }
}

Vertex parseVertex(const std::string& x, const std::string& y, const std::string& z){
    return Vertex(std::stod(x), std::stod(y), std::stod(z));
}

Face parseFace(const std::string& x, const std::string& y, const std::string& z){
    return Face(stoi(x), stoi(y), stoi(z));
}