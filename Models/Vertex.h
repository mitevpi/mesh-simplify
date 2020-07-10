//
// Created by Petr Mitev on 5/22/20.
//

#include <cmath>

#ifndef MESH_SIMPLIFY_VERTEX_H
#define MESH_SIMPLIFY_VERTEX_H


class Vertex {
public:
    Vertex(double x, double y, double z);

    double x;
    double y;
    double z;
    int lineIndex;

    static Vertex parseVertex(const std::string &x, const std::string &y, const std::string &z) {
        return Vertex(std::stod(x), std::stod(y), std::stod(z));
    }

    static std::vector<Vertex> getDuplicates(Vertex vertex, const std::vector<Vertex> &vertices) {
        std::vector<Vertex> duplicates;
        for (auto v : vertices) {
            if (v.lineIndex != vertex.lineIndex){
                if (approximatelyEqual(v.x, vertex.x) && approximatelyEqual(v.y, vertex.y) &&
                    approximatelyEqual(v.z, vertex.z)) {
                    duplicates.push_back(v);
                }
            }
        }
        return duplicates;
    }

    static bool approximatelyEqual(double a, double b, double epsilon = 0.01) {
        bool result = fabs(a - b) <= ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
        return result;
    }

    static std::vector<std::vector<Vertex> > getDuplicates(std::vector<Vertex> &vertices) {
        std::vector<std::vector<Vertex> > allDuplicates;
        for (auto v : vertices) {
            std::vector<Vertex> duplicates = Vertex::getDuplicates(v, vertices);
            allDuplicates.push_back(duplicates);
        }

        return allDuplicates;
    }
};

Vertex::Vertex(double x, double y, double z) {
    Vertex::x = x;
    Vertex::y = y;
    Vertex::z = z;
}

#endif //MESH_SIMPLIFY_VERTEX_H
