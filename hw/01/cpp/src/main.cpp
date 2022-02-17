// some standard libraries that are helpful for reading/writing text files
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "Gmap.h"

int main(int argc, const char * argv[]) {
    std::string file_in = "torus.obj";
    std::string file_out_obj = "torus_triangulated.obj";
    std::string file_out_csv_d = "torus_darts.csv";
    std::string file_out_csv_0 = "torus_vertices.csv";
    std::string file_out_csv_1 = "torus_edges.csv";
    std::string file_out_csv_2 = "torus_faces.csv";
    std::string file_out_csv_3 = "torus_volume.csv";


  // ## Read OBJ file ##

  //read obj file:
    std::ifstream stream_in;
    stream_in.open(file_in);
    std::vector<Vertex> vertices;
    std::vector<Face> faces;
    if (stream_in.is_open()) {
        std::string line;
        while (getline(stream_in, line)) {
            std::istringstream iss(line);
            std::string word;
            iss >> word;
            //for vertices
            if (word == "v") {
                std::vector<float> coordinates;
                while (iss >> word) coordinates.push_back(std::stof(word));
                if (coordinates.size() == 3) vertices.emplace_back(coordinates[0], coordinates[1], coordinates[2]);
                else vertices.emplace_back();
            }
            //for faces : similar too the vertices we need to retrieve the faces from the OBJ file and store them in the vector faces, made out of Face
            if (word == "f") {
                std::vector<int> indices;
                while (iss >> word) indices.push_back(std::stoi(word));
                for (auto indice :indices){
                    std::cout<<indice<<" ";
//                    faces.emplace_back(indice);
                }
                std::cout<<std::endl;
            }
        }
    }

    // to print size of vector
    std::cout<<vertices.size();

    // print all vertices in the vector vertices
//    for (auto vertice : vertices){
//        std::cout<<vertice<<std::endl;
//    }


  // ## Construct generalised map using the structures from Gmap.h ##

  // ## Output generalised map to CSV ##

  // ## Create triangles from the darts ##

  // ## Write triangles to obj ##

  return 0;
}
