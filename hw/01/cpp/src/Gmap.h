#pragma once

#include "Point.h"

struct Point;
struct Dart;
struct Vertex;
struct Edge;
struct Face;
struct Volume;

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
  // involutions:
  // ..

  // cells:
  // ...

};

struct Vertex {
  // the coordinates of this vertex:
  Point point;

  // constructor without arguments
  Vertex() : point(Point()) 
  {}

  // constructor with x,y,z arguments to immediately initialise the point member on this Vertex.
  Vertex(const double &x, const double &y, const double &z) : point(Point(x,y,z))
  {}

  //operator to print the vertices
  friend std::ostream& operator<<(std::ostream &os, const  Vertex& rhs){  //for struct output
        os << "Vertex = " << rhs.point;
        return os;
    }

  // a dart incident to this Vertex:
  // ...


};

struct Edge {
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

struct Face {

    // int of indice of coordinate it's referring to. Could also be a pointer to this indice, might has to be a vector of indices.
   std::vector<int> faces;

    // constructor without arguments
    Face() : faces(std::vector<int>())
    {}
  // a dart incident to this Face:
  // ...

  // function to compute the barycenter for this Face (needed for triangulation output):
  // Point barycenter() {}

//    //operator to print the Faces
//    friend std::ostream& operator<<(std::ostream &os, const  Face& rhs){  //for struct output
//        os << "Face = " << rhs.point;
//        return os;
//    }

};

struct Volume {
  // a dart incident to this Volume:
  // ...

//    //operator to print the vertices
//    friend std::ostream& operator<<(std::ostream &os, const  Volume& rhs){  //for struct output
//        os << "Volume  = " << rhs.;
//        return os;
//    }

};