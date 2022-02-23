// some standard libraries that are helpful for reading/writing text files
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Gmap.h"

int id =0;
int dart_id = 0;
int face_id = 0;
int edge_id = 0;
int vector_id = 0;

int main(int argc, const char * argv[]) {
    std::string file_in = "torus.obj";
    std::string file_out_obj = "torus_triangulated.obj";
    std::string file_out_csv_d = "torus_darts.csv";
    std::string file_out_csv_0 = "torus_vertices.csv";
    std::string file_out_csv_1 = "torus_edges.csv";
    std::string file_out_csv_2 = "torus_faces.csv";
    std::string file_out_csv_3 = "torus_volume.csv";

    // ## Read OBJ file ##
    std::ifstream stream_in;
    stream_in.open(file_in);
    std::vector<Vertex> vertices;
    std::vector<Face> faces;
    std::vector<index_Face> indices ;
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
                //vector to hold the 4 vertices of a Face
                std::vector<Vertex> face_points;
                //used indexes to get Vertex value.
                while (iss >> word) face_points.push_back((vertices[std::stoi(word)-1]));
                // place the vector of Vertices in vector faces
                faces.emplace_back(face_points);
            }
        }
    }
    //another stream, because I can't get the previous thing to read the if(word =="f") part twice
    std::ifstream stream_in_2;
    stream_in_2.open(file_in);
    if (stream_in_2.is_open()) {
        std::string line;
        while (getline(stream_in_2, line)) {
            std::istringstream iss(line);
            std::string word;
            iss >> word;
            if (word == "f") {
                //vector that holds the indices of the faces, other thant the previous that stores the vertexes itself.
                std::vector<int> face_indices;
                //loop through the line
                while (iss >> word) face_indices.push_back(std::stoi(word));
                //place the indexes in the
                indices.emplace_back(face_indices[0], face_indices[1], face_indices[2], face_indices[3]);
            }
        }
    }

    std::vector<Vertex> test;
    for (auto face: faces){
        auto face_num = face_id++;
        for (int i = 0; i<face.faces.size(); i++){
            auto vertex_num = vector_id++;
            if (i< (face.faces.size() -1)){
                auto vertice_1 = face.faces[i];
                auto vertice_2 = face.faces[i+1];
            }
            else{
                auto vertice_1 = face.faces[i];
                auto vertice_2 = face.faces[0];
            }
            auto dart_1 = dart_id++;
            auto dart_2 = dart_id++;
            auto edge_num = edge_id++;


        }
        test.push_back(face.faces[0]);
    }

    for (auto vertice : test){
        std::cout<<vertice<<std::endl;
    }

    // to print the index_Faces
//    for (auto index: indices){
//        std::cout<<index<<std::endl;
//    }

//     print all vertices in the vector vertices
//    for (auto vertice : vertices){
//        std::cout<<vertice<<std::endl;
//    }

//        // Print all Faces
//        for (auto &face: faces) {
//            std::cout << face << std::endl;
//        }

        //vertex output
        std::ofstream vertice_output;
        vertice_output.open(file_out_csv_0);
        vertice_output << "ID, dart, x, y, z\n";
        for (auto vertice: vertices) {
            vertice_output << id++ << ", " << "dart" << ", " << vertice.x << ", " << vertice.y << ", " << vertice.z
                           << std::endl;
        }
        vertice_output.close();

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
        face_output.open(file_out_csv_2);
        face_output << "ID, dart, x, y, z\n";
        for (auto &face: faces) {
            for (auto vertex: face.faces)
                face_output << id++ << ", " << vertex.x << std::endl;
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
