//
// Created by Petr Mitev on 5/22/20.
//

#ifndef MESH_SIMPLIFY_VERTEX_H
#define MESH_SIMPLIFY_VERTEX_H


class Vertex {
public:
    Vertex(double x, double y, double z);
    double x;
    double y;
    double z;

    static Vertex parseVertex(const std::string& x, const std::string& y, const std::string& z){
        return Vertex(std::stod(x), std::stod(y), std::stod(z));
    }
};

Vertex::Vertex(double x, double y, double z){
 Vertex::x = x;
 Vertex::y = y;
 Vertex::z = z;
}

#endif //MESH_SIMPLIFY_VERTEX_H
