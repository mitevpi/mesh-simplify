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
    /// Read the OBJ file at the path and create an instance of this class.
    /// @param path the filepath of the OBJ File
    explicit ObjFile(std::string path);

    std::string FilePath;
    std::vector<std::string> Lines;
    std::vector<Face> Faces;
    std::vector<Vertex> Vertices;
    std::vector<std::vector<Vertex> > DuplicateVertices;

private:
    std::ifstream _fileStream;

    void read();

    void parseObjLine(const std::string &line, int lineIndex);

    void summarize() const;
};

ObjFile::ObjFile(std::string path) {
    ObjFile::FilePath = std::move(path);
    ObjFile::read();
    ObjFile::DuplicateVertices = Vertex::getDuplicates(Vertices);
    ObjFile::summarize();
}

void ObjFile::read() {
    int lineIndex = 1;
    std::string objLine;
    _fileStream.open(FilePath);

    // Terminate if file can't be opened
    if (!_fileStream) {
        std::cout << "Unable to open file";
        exit(1); // terminate with error
    }

    // Get Lines, and parse
    while (getline(_fileStream, objLine)) {
        parseObjLine(objLine, lineIndex);
        Lines.push_back(objLine);
        lineIndex++;
    }

    _fileStream.close();
}

void ObjFile::summarize() const {
    std::cout << "Finished Reading: " << Lines.size() << " Lines" << std::endl;
    std::cout << "Vertices: " << Vertices.size() << std::endl;
    std::cout << "Duplicate Vertices: " << DuplicateVertices.size() << std::endl;
    std::cout << "Faces: " << Faces.size() << std::endl;
}

void ObjFile::parseObjLine(const std::string &line, int lineIndex) {
    std::smatch objMatch;
    std::regex objRegex(R"(([vf])\s([-\d]+[\d\.]+)\s([-\d]+[\d\.]+)\s([-\d]+[\d\.]+))");
    std::string type;

    // Get regex matches
    std::regex_search(line, objMatch, objRegex);
    type = objMatch[1];

    // Convert to classes
    if (type == "v") {
        Vertex vert = Vertex::parseVertex(objMatch[2], objMatch[3], objMatch[4]);
        vert.lineIndex = lineIndex;
        Vertices.push_back(vert);
//        std::cout << type << " " << vert.x << " " << vert.y << " " << vert.z << std::endl;
    } else if (type == "f") {
        Face fa = Face::parseFace(objMatch[2], objMatch[3], objMatch[4]);
        fa.lineIndex = lineIndex;
        Faces.push_back(fa);
//        std::cout << type << " " << fa.x << " " << fa.y << " " << fa.z << std::endl;
    }
}

#endif //MESH_SIMPLIFY_OBJFILE_H
