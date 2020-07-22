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
    int lineIndex{};
    int pointTo = -1;

    static Vertex parseVertex(const std::string &x, const std::string &y, const std::string &z) {
        return Vertex(std::stod(x), std::stod(y), std::stod(z));
    }

    static bool parseDuplicates(Vertex vertexA, std::vector<Vertex> &vertices) {
        bool duplicated = false;
        for (Vertex& vertexB : vertices) {
            // if both vertices aren't the same one (based on index) and if the vertex
            // to check has not already been flagged as a duplicate
            if (vertexB.lineIndex != vertexA.lineIndex && vertexA.pointTo < 1){
                if (approximatelyEqual(vertexB.x, vertexA.x) && approximatelyEqual(vertexB.y, vertexA.y) &&
                    approximatelyEqual(vertexB.z, vertexA.z)) {
                    vertexB.pointTo = vertexA.lineIndex;
                    duplicated = true;
                }
            }
        }
        return duplicated;
    }

    /**
     * Main method for finding duplicates in an array of Vertices.
     * @param vertices An array of Vertex elements.
     * @return The amount of vertices which are duplicated 1 or more times.
     */
    static int parseDuplicates(std::vector<Vertex> &vertices) {
        int duplicatedCount = 0;
        for (auto v : vertices) {
            bool duplicated = Vertex::parseDuplicates(v, vertices);

            if (duplicated){
                duplicatedCount++;
            }
        }
        return duplicatedCount;
    }


    static bool approximatelyEqual(double a, double b, double epsilon = 0.001) {
        bool result = fabs(a - b) <= ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
        return result;
    }
};

/**
 * Construct a Vertex class from known coordinates.
 * @param x Vertex X Coordinate.
 * @param y Vertex y Coordinate.
 * @param zVertex z Coordinate.
 */
Vertex::Vertex(double x, double y, double z) {
    Vertex::x = x;
    Vertex::y = y;
    Vertex::z = z;
}

#endif //MESH_SIMPLIFY_VERTEX_H
