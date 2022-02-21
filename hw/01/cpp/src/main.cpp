// some standard libraries that are helpful for reading/writing text files
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Gmap.h"

int id =0;

int main(int argc, const char * argv[]) {
    std::string file_in = "../../data/torus.obj";
    std::string file_out_obj = "../../data/torus_triangulated.obj";
    std::string file_out_csv_d = "../../data/torus_darts.csv";
    std::string file_out_csv_0 = "../../data/torus_vertices.csv";
    std::string file_out_csv_1 = "../../data/torus_edges.csv";
    std::string file_out_csv_2 = "../../data/torus_faces.csv";
    std::string file_out_csv_3 = "../../data/torus_volume.csv";

    // ## Read OBJ file ##
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
                std::vector<Vertex> indices;
                while (iss >> word) indices.push_back(vertices[std::stoi(word)]);
                std::cout<<indices.size();
                faces.emplace_back(indices);
                for (auto face: indices){
                    std::cout<<face<<std::endl;
                }
            }
        }
    }

std::cout<<faces.size();
//     print all vertices in the vector vertices
//    for (auto vertice : vertices){
//        std::cout<<vertice<<std::endl;
//    }

    for (auto &face: faces){
            std::cout<<face<<std::endl;
        }

//        std::cout<<face.point<<std::endl;
//        for(auto help : face){
//            std::cout<<"what";
//            std::cout<<help.point<<std::endl;
//        }


    //vertex output
    std::ofstream vertices_output;
    vertices_output.open (file_out_csv_0);
    vertices_output << "ID, dart, x, y, z\n";
    for (auto vertex : vertices){
        vertices_output<<id++<<", "<<"dart"<<", "<<vertex.x <<", "<<vertex.y<<", "<<vertex.z<<std::endl;
    }
    vertices_output.close();

//    //Dart output
//    std::ofstream dart_output;
//    dart_output.open (file_out_csv_d);
//    dart_output << "ID, a0, a1, a2, a3, v, e, f\n";
//    for (auto dart : darts){
//        dart_output<<id++<<", "<<"dart"<<", "<<vertice.x <<", "<<vertice.y<<", "<<vertice.z<<std::endl;
//    }
//    dart_output.close();

//    //edge output
//    std::ofstream edge_output;
//    edge_output.open (file_out_csv_1);
//    edge_output << "ID, dart, x, y, z\n";
//    for (auto edge : edges){
//        edge_output<<id++<<", "<<"dart"<<", "<<vertice.x <<", "<<vertice.y<<", "<<vertice.z<<std::endl;
//    }
//    edge_output.close();
//
    //face output
    std::ofstream face_output;
    face_output.open (file_out_csv_2);
    face_output << "ID, dart, x, y, z\n";
    for (auto face : faces){
        for(auto vertex: face.faces)
            face_output<<id++<<", "<< vertex.point << std::endl;
//            std::cout<<vertex<<std::endl;

    }
    face_output.close();
//
//    //volume output
//    std::ofstream volume_output;
//    volume_output.open (file_out_csv_1);
//    volume_output << "ID, dart, x, y, z\n";
//    for (auto volume : volumes){
//        volume_output<<id++<<", "<<"dart"<<", "<<vertice.x <<", "<<vertice.y<<", "<<vertice.z<<std::endl;
//    }
//    volume_output.close();


  // ## Construct generalised map using the structures from Gmap.h ##

  // ## Output generalised map to CSV ##

  // ## Create triangles from the darts ##

  // ## Write triangles to obj ##

  return 0;
}
