#include <iostream>
#include <iomanip>
#include <fstream>
#include <utility>
#include <vector>
#include <regex>
#include "Models/Vertex.h"
#include "Models/Face.h"
#include "Models/ObjFile.h"

void ParseObjFile(std::string path) {
//    std::string filePath = "/Users/mitevpi/Dropbox/Work/010_Project Files/200522_Mesh Simplification/TopoMeshCustom.obj";
//    std::string filePath = R"(C:\Users\pmitev\Dropbox\Work\010_Project Files\200522_Mesh Simplification\TopographyMesh.obj)";

    if (path.empty()){
        path = R"(C:\Users\pmitev\Dropbox\Work\010_Project Files\200522_Mesh Simplification\TopographyMesh.obj)";
    }
    ObjFile of = ObjFile(std::move(path));
    of.write();
}



