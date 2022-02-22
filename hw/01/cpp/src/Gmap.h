#pragma once

#include "Point.h"
struct Point;
struct Dart;
struct Vertex;
struct Edge;
struct Face;
struct Volume;
struct index_Face;

/*
Below you find the basic elements that you need to build the generalised map.
The main thing you need to fill out are the links between the elements:
  * the involutions and cells on the Dart
  * the darts on the cells

One way to do this is by using pointers. eg. define a member on the dart struct like

  Struct Dart {
    // involutions:
    Dart* a0 = nullptr;
    // ...

    // cells:
    // ...
  
  };
Then you could create and link Darts like:
  Dart* dart_a = new Dart();
  Dart* dart_b = new Dart();

  dart_a->a0 = dart_b;
*/

struct Dart {
//    Point cell_0;//
//    Edge cell_1;
//    Face cell_2;
//    Dart ->previous_dart;
//    Dart ->nex_dart;
//    Dart ->opposing_dart;
//    // involutions:

  // ..

  // cells:
  // ...

};

struct Vertex {
  // the coordinates of this vertex:
  Point point;
  double x{};
  double y{};
  double z{};

  // constructor without arguments
  Vertex() : point(Point())
  {}

  Vertex(const double &x, const double &y, const double &z) : point(Point(x,y,z)){
      this-> x = x;
      this-> y = y;
      this-> z = z;
  }

  //operator to print the vertices
  friend std::ostream& operator<<(std::ostream &os, const  Vertex& rhs){  //for struct output
        os << "Vertex = " << rhs.point;
        return os;
    }

  // a dart incident to this Vertex:
  // ...

};

struct Edge {
    Point begin_point;
    Point endpoint;

  // a dart incident to this Edge:
  // ...

  // function to compute the barycenter for this Edge (needed for triangulation output):
  // Point barycenter() {}

//  //operator to print the edges
//    friend std::ostream& operator<<(std::ostream &os, const  Edge& rhs){  //for struct output
//        os << "Edge = " << rhs.;
//        return os;
//    }
};

struct index_Face{
    // int of indice of coordinate it's referring to. Could also be a pointer to this indice, might has to be a vector of indices.
    int llcorner;
    int lrcorner;
    int rurcorner;
    int lurcorner;

    // constructor with arguments
    index_Face(const int &llcorner, const int &lrcorner, const int &rurcorner, const int &lurcorner){
        this -> llcorner = llcorner;
        this -> lrcorner = lrcorner;
        this -> rurcorner = rurcorner;
        this -> lurcorner = lurcorner;
    }
    friend std::ostream& operator<< (std::ostream& os, const index_Face&a){
        os<< a.llcorner<<", "<< a.lrcorner << ", "<<a.rurcorner<<", "<<a.lurcorner;
        return os;
    }

};
// This is something we might want to implement in the future, where index_Face is a vector instead of 4 integers
//struct index_Face{
//    // int of indice of coordinate it's referring to. Could also be a pointer to this indice, might has to be a vector of indices.
//    std::vector<int> faces;
//
//    // constructor with arguments
//    index_Face(const std::vector<int>& hallo) : faces(std::vector<int>()){
////        this -> faces = faces;
//    }
//    friend std::ostream& operator<< (std::ostream& os, const index_Face&a){
//        os<<a.faces.size();
//        for (auto& e : a.faces) os << e;
//        return os;
//    }
//};

struct Face {
    // int of indice of coordinate it's referring to. Could also be a pointer to this indice, might has to be a vector of indices.
    std::vector<Vertex> faces;

    // constructor with arguments
    Face(const std::vector<Vertex>& faces){
        this-> faces = faces;
    }
    //ostream operator, prints the point in the Vertex
    friend std::ostream& operator<< (std::ostream& os, const Face&a){
        for (auto& e : a.faces) os << e.point;
        return os;
    }

  // a dart incident to this Face:
  // ...
  // function to compute the barycenter for this Face (needed for triangulation output):
  // Point barycenter() {}

};

struct Volume {
    Dart dart;
};