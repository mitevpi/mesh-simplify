cmake_minimum_required(VERSION 3.16)
project(mesh_simplify)

set(CMAKE_CXX_STANDARD 20)

add_executable(mesh_simplify main.cpp Models/Vertex.h Models/ObjFile.h)