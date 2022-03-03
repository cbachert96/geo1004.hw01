// By Siebren Meines and Carolin Bachert

#pragma once
#include <algorithm>
#include "Point.h"
//help structures
struct Point;
struct vertex_Face;
struct point_Vertex;

//output structures
struct Dart;
struct Edge;
struct Face;
struct Vertex;
struct Volume;

//help structures these structures will not be the ouput, but we will use them to make the output structures correctly:
// help structure point_Vertex is used to store the Vertex data that is read from the OBJ file. This is later used in structure vertex_Face
struct point_Vertex {
    // the coordinates of this vertex:
    Point point;
    double x{};
    double y{};
    double z{};

    // constructor without arguments
    point_Vertex() : point(Point())
    {}

    point_Vertex(const double &x, const double &y, const double &z) : point(Point(x,y,z)){
        this-> x = x;
        this-> y = y;
        this-> z = z;
    }

    //operator to print the vertices
    friend std::ostream& operator<<(std::ostream &os, const  point_Vertex& rhs){  //for struct output
        os << "Vertex = " << rhs.point;
        return os;
    }
};


//help structure point_Vertex is used to build the structures on, by iterating over the 4 points that make a face.
struct vertex_Face {
    // a vertex_Face consists of a vector of point_Vertex
    std::vector<point_Vertex> vertices;

    // constructor with arguments
    vertex_Face(const std::vector<point_Vertex>& vertices){
        this-> vertices = vertices;
    }
    //ostream operator, prints the point in the Vertex
    friend std::ostream& operator<< (std::ostream& os, const vertex_Face&a){
        for (auto& e : a.vertices) os << e.point;
        return os;
    }

    template<typename _InputIterator>
    _InputIterator begin() {
        return nullptr;
    }
};

//output structures: these are the actual output structures, prefereably only hold output data.
//Structure Dart that holds all the relevant values for the Dart in Gmap
struct Dart {
    int id;
    int vertice;
    int edge;
    int face;
    int alpha_0;
    int alpha_1;
    int alpha_2;
    int alpha_3;

    // constructor with arguments
    Dart(const int &id, const int &vertice, const int &edge, const int &face, const int &alpha_0, const int &alpha_1, const int &alpha_2, const int &alpha_3){
        this -> id =id;
        this -> vertice = vertice;
        this -> edge = edge;
        this -> face = face;
        this -> alpha_0 = alpha_0;
        this -> alpha_1 = alpha_1;
        this -> alpha_2 = alpha_2;
        this -> alpha_3 = alpha_3;
    }
    void operator=(const Dart &other) {
        id=other.id;
        vertice=other.vertice;
        edge=other.edge;
        face = other.face;
        alpha_0 = other.alpha_0;
        alpha_1 = other.alpha_1;
        alpha_2 = other.alpha_2;
        alpha_3 = other.alpha_3;
    }

    //operator to print the Dart
    friend std::ostream& operator<<(std::ostream &os, const  Dart& rhs){  //for struct output
        os << "id = "<<rhs.id<< "Vertex = " << rhs.vertice << "edge = " << rhs.edge << "face = " << rhs.face<< "alpha_0 = " << rhs.alpha_0<< "alpha_1 = " << rhs.alpha_1<< "alpha_2 = " << rhs.alpha_2<< "alpha_3 = " << rhs.alpha_3;
        return os;
    }
};

//Structure Vertex that holds all the relevant values for the Vertex in Gmap
struct Vertex{
    int id;
    int dart;
    float x;
    float y;
    float z;

    Vertex(const int &id, const int&dart, const float&x, const float &y, const float &z){
        this -> id = id;
        this -> dart = dart;
        this -> x = x;
        this -> y = y;
        this -> z = z;
    }
    friend std::ostream & operator<<(std::ostream &os, const Vertex&rhs){
        os<< "id = "<< rhs.id<< "dart = "<<rhs.dart<< "x = "<<rhs.x<< "y = "<<rhs.y<< "z = "<<rhs.z;
        return os;
    }
};

//Structure Edge that holds all the relevant values for the Edge in Gmap
struct Edge {
    int id;
    int dart;

    Edge(const int &id, const int&dart){
        this -> id = id;
        this -> dart = dart;
    }
    friend std::ostream & operator<<(std::ostream &os, const Edge&rhs){
        os<< "id = "<< rhs.id<< "dart = "<<rhs.dart;
        return os;
    }

};

//Structure Face that holds all the relevant values for the Face in Gmap
struct Face{
    int id;
    int dart;

    Face(const int &id, const int&dart){
        this -> id = id;
        this -> dart = dart;
    }
    friend std::ostream & operator<<(std::ostream &os, const Face&rhs){
        os<< "id = "<< rhs.id<< "dart = "<<rhs.dart;
        return os;
    }

};
//Structure Volume that holds all the relevant values for the Volume in Gmap
struct Volume {
    int id;
    int dart;

    Volume(const int &id, const int&dart){
        this -> id = id;
        this -> dart = dart;
    }
    friend std::ostream & operator<<(std::ostream &os, const Volume&rhs){
        os<< "id = "<< rhs.id<< "dart = "<<rhs.dart;
        return os;
    }
};



