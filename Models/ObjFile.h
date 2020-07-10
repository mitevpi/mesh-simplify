//
// Created by Petr Mitev on 7/10/20.
//

#ifndef MESH_SIMPLIFY_OBJFILE_H
#define MESH_SIMPLIFY_OBJFILE_H

#include <string>
#include <utility>
#include <fstream>
#include <iostream>
#include <vector>

class ObjFile {
public:
    explicit ObjFile(std::string path);
    std::string FilePath;
    std::vector< std::string > Lines;
    std::vector< Face > Faces;
    std::vector< Vertex > Vertices;

    void read();
private:
    std::ifstream _fileStream;

    void parseObjLine(const std::string& basicString);
};

ObjFile::ObjFile(std::string path){
    ObjFile::FilePath = std::move(path);
}

void ObjFile::read() {
    std::string objLine;

    _fileStream.open(FilePath);

    // Terminate if file can't be opened
    if (!_fileStream) {
        std::cout << "Unable to open file";
        exit(1); // terminate with error
    }

    // Get Lines
    while (getline(_fileStream, objLine)) {
        parseObjLine(objLine);
        Lines.push_back(objLine);
    }

    _fileStream.close();
    std::cout << "Finished Reading: " << Lines.size() << " Lines" << std::endl;
}

void ObjFile::parseObjLine(const std::string& line) {
    std::smatch objMatch;
    std::regex objRegex(R"(([vf])\s([-\d]+[\d\.]+)\s([-\d]+[\d\.]+)\s([-\d]+[\d\.]+))");
    std::string type;

    // Get regex matches
    std::regex_search(line, objMatch, objRegex);
    type = objMatch[1];

    // Convert to classes
    if (type == "v"){
        Vertex vert = Vertex::parseVertex(objMatch[2], objMatch[3], objMatch[4]);
        Vertices.push_back(vert);
        std::cout << type << " " << vert.x << " " << vert.y << " " << vert.z << std::endl;
    }
    else if (type == "f"){
        Face fa = Face::parseFace(objMatch[2], objMatch[3], objMatch[4]);
        Faces.push_back(fa);
        std::cout << type << " " << fa.x << " " << fa.y << " " << fa.z << std::endl;
    }
}

#endif //MESH_SIMPLIFY_OBJFILE_H
