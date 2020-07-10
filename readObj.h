#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <regex>
#include "Models/Vertex.h"
#include "Models/Face.h"
#include "Models/ObjFile.h"


void parseObjLine(const std::string& line);

void readObjFile() {
    int count = 0;
    std::string filePath = "/Users/mitevpi/Dropbox/Work/010_Project Files/200522_Mesh Simplification/TopographyMesh.obj";

    ObjFile of = ObjFile(filePath);
    of.read();
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
        Vertex vert = Vertex::parseVertex(objMatch[2], objMatch[3], objMatch[4]);
        std::cout << type << " " << vert.x << " " << vert.y << " " << vert.z << std::endl;
    }
    else if (type == "f"){
        Face fa = Face::parseFace(objMatch[2], objMatch[3], objMatch[4]);
        std::cout << type << " " << fa.x << " " << fa.y << " " << fa.z << std::endl;
    }
}



