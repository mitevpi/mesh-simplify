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
#include <map>

class ObjFile {
public:
    /// Read the OBJ file at the path and create an instance of this class.
    /// @param path the filepath of the OBJ File
    explicit ObjFile(std::string path);

    std::string FilePath;
    std::vector<Face> Faces;
    std::vector<Vertex> Vertices;
    int DuplicateVertices;
    int LineCount = 0;
    void write();

private:
    std::ifstream _fileStreamRead;
    std::ofstream _fileStreamWrite;

    void read();
    void parseObjLine(const std::string &line, int lineIndex);
    void summarize() const;
};

ObjFile::ObjFile(std::string path) {
    ObjFile::FilePath = std::move(path);
    ObjFile::read();
    ObjFile::DuplicateVertices = Vertex::parseDuplicates(Vertices);
    ObjFile::summarize();
}

/**
 * Read an OBJ file line-by-line and parse the Face and Vertex data into
 * appropriate model classes.
 */
void ObjFile::read() {
    int lineIndex = 1;
    std::string objLine;
    _fileStreamRead.open(FilePath);

    // Terminate if file can't be opened
    if (!_fileStreamRead) {
        std::cout << "Unable to open file";
        exit(1); // terminate with error
    }

    // Get Lines, and parse
    while (getline(_fileStreamRead, objLine)) {
        parseObjLine(objLine, lineIndex);
        lineIndex++;
        LineCount++;
    }

    _fileStreamRead.close();
}

void ObjFile::write() {
    std::string NewPath = FilePath.substr(0, FilePath.find_last_of("\\/")) + "\\Simplified.obj";
    std::cout << "Starting to Write: " << LineCount << " Lines" << std::endl;
    _fileStreamWrite.open(NewPath);

    std::map<int, int> vLookupTable;

    // write vertices
    for (auto v : Vertices) {
        if (v.pointTo == -1) {
            _fileStreamWrite << "v " << v.x << " " << v.y << " " << v.z << std::endl;
        } else {
            vLookupTable[v.lineIndex] = v.pointTo;
        }
    }

    // write faces
    int fx, fy, fz;
    for (auto f: Faces){
        fx = ( vLookupTable.count(f.x) > 0 ) ? vLookupTable[f.x] : f.x;
        fy = ( vLookupTable.count(f.y) > 0 ) ? vLookupTable[f.y] : f.y;
        fz = ( vLookupTable.count(f.z) > 0 ) ? vLookupTable[f.z] : f.z;

        _fileStreamWrite << "f " << fx << " " << fy << " " << fz << std::endl;
    }

    _fileStreamWrite.close();
}

/**
 * Print ou a summary of the OBJ File and performed operations on the console.
 */
void ObjFile::summarize() const {
    std::cout << "Finished Reading: " << LineCount << " Lines" << std::endl;
    std::cout << "Vertices: " << Vertices.size() << std::endl;
    std::cout << "Duplicate Vertices: " << DuplicateVertices << std::endl;
    std::cout << "Faces: " << Faces.size() << std::endl;
}

void ObjFile::parseObjLine(const std::string &line, int lineIndex) {
    std::smatch objMatch;
//    std::regex objRegex(R"(([vf])\s([-\d]+[\d\.]+)\s([-\d]+[\d\.]+)\s([-\d]+[\d\.]+))");
    std::regex objRegex(R"(([vf])\s([-\d\.]+)\s([-\d\.]+)\s([-\d\.]+))");
    std::string type;

    // Get regex matches
    std::regex_search(line, objMatch, objRegex);
    type = objMatch[1];

    // Convert to classes
    if (type == "v") {
        Vertex vert = Vertex::parseVertex(objMatch[2], objMatch[3], objMatch[4]);
        vert.lineIndex = lineIndex;
        Vertices.push_back(vert);
    } else if (type == "f") {
        Face fa = Face::parseFace(objMatch[2], objMatch[3], objMatch[4]);
        fa.lineIndex = lineIndex;
        Faces.push_back(fa);
    }
}

#endif //MESH_SIMPLIFY_OBJFILE_H
