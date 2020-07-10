#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <regex>
#include "Models/Vertex.h"
#include "Models/Face.h"
#include "Models/ObjFile.h"

void ParseObjFile() {
    std::string filePath = "/Users/mitevpi/Dropbox/Work/010_Project Files/200522_Mesh Simplification/TopographyMesh.obj";

    ObjFile of = ObjFile(filePath);
    of.read();
}



