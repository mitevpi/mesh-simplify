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

    void read();
private:
    std::ifstream _fileStream;

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
        //        parseObjLine(objLine);
        Lines.push_back(objLine);
    }

    _fileStream.close();
    std::cout << "Finished Reading: " << Lines.size() << " Lines" << std::endl;
}

#endif //MESH_SIMPLIFY_OBJFILE_H
