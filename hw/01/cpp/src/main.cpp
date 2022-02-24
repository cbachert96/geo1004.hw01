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
    std::vector<point_Vertex> vertices;
    std::vector<vertex_Face> faces;
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
                std::vector<point_Vertex> face_points;
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

    //vectors to hold the output data of the designated types.
    std::vector<Vertex> output_vertices;
    std::vector<Face> output_faces;
    std::vector<Volume> output_volume;
    std::vector<Edge> output_edges;
    std::vector<Dart> output_darts;

    output_volume.emplace_back(0,0);

    //loop through the faces vector to build the structure.
    for (auto face: faces){
        //id for face
        auto face_num = face_id++;
        auto dart_on_face = dart_id +1;
        output_faces.emplace_back(face_num, dart_on_face);
        //loop through the vertices in a face, to make the other structures
        for (int i = 0; i<face.vertices.size(); i++){
            //assign id's, it's just a number that goes up 1 each time it's called.
            auto dart_1 = dart_id++;
            auto dart_2 = dart_id++;
            auto vertex_num = vector_id++;
            auto edge_num = edge_id++;

            point_Vertex vertice_1;
            point_Vertex vertice_2;
            
            //two vertices to make an edge in between, 1st with 2nd and so on.
            if (i< (face.vertices.size() -1)){
                auto vertice_1 = face.vertices[i];
                auto vertice_2 = face.vertices[i+1];
            }
            //if we are at the final vertice, we also need to make an edge between the final and first one.
            else{
                auto vertice_1 = face.vertices[i];
                auto vertice_2 = face.vertices[0];
            }
            output_vertices.emplace_back(vertex_num, dart_1, face.vertices[i].x, face.vertices[i].y, face.vertices[i].z);
            output_edges.emplace_back(edge_num, dart_1);
            //for the first dart, we need the final dart, that's why de do 2* the length of the vector -1. So dart 0 has 7 as alpha_0 in case of 4 vertices.
            if (i ==0){
                int alpha_0_dart_1 = dart_1 +1;
                auto alpha_1_dart_1 = dart_1 + (2*face.vertices.size()-1);
                int alpha_2_dart_1 = 0;
                int alpha_3_dart_1 = 0;
                int alpha_0_dart_2 = dart_2 -1;
                int alpha_1_dart_2 = dart_2 +1;
                int alpha_2_dart_2 = 0;
                int alpha_3_dart_2 = 0;
                output_darts.emplace_back(dart_1,vertex_num, edge_num, face_num, alpha_0_dart_1, alpha_1_dart_1, alpha_2_dart_1, alpha_3_dart_1);
                output_darts.emplace_back(dart_2,vertex_num, edge_num, face_num, alpha_0_dart_2, alpha_1_dart_2, alpha_2_dart_2, alpha_3_dart_2);
                }

            //if we're at the final vertex, the last dart, let's say 7 needs to have 0 as the next, and not 8
            else if (i == face.vertices.size()-1){
                auto alpha_0_dart_1 = dart_1 +1;
                auto alpha_1_dart_1 = dart_1 -1;
                int alpha_2_dart_1 = 0;
                int alpha_3_dart_1 = 0;
                auto alpha_0_dart_2 = dart_2 -1;
                auto alpha_1_dart_2 = dart_2 + (2*face.vertices.size()+1);
                auto alpha_2_dart_2 = 0;
                int alpha_3_dart_2 = 0;
                output_darts.emplace_back(dart_1,vertex_num, edge_num, face_num, alpha_0_dart_1, alpha_1_dart_1, alpha_2_dart_1, alpha_3_dart_1);
                output_darts.emplace_back(dart_2,vertex_num, edge_num, face_num, alpha_0_dart_2, alpha_1_dart_2, alpha_2_dart_2, alpha_3_dart_2);
            }
            else{
                auto alpha_0_dart_1 = dart_1 +1;
                auto alpha_1_dart_1 = dart_1 -1;
                int alpha_2_dart_1 = 0;
                int alpha_3_dart_1 = 0;
                int alpha_0_dart_2 = dart_2 -1;
                int alpha_1_dart_2 = dart_2 +1;
                int alpha_2_dart_2 = 0;
                int alpha_3_dart_2 = 0;
                output_darts.emplace_back(dart_1,vertex_num, edge_num, face_num, alpha_0_dart_1, alpha_1_dart_1, alpha_2_dart_1, alpha_3_dart_1);
                output_darts.emplace_back(dart_2,vertex_num, edge_num, face_num, alpha_0_dart_2, alpha_1_dart_2, alpha_2_dart_2, alpha_3_dart_2);
            }
        }
    }

    //vertex output
    std::ofstream vertice_output;
    vertice_output.open(file_out_csv_0);
    vertice_output << "ID, dart\n";
    for (auto vertice: output_vertices) {
        vertice_output << vertice.id << ", " << vertice.dart << ", " << vertice.x << ", " << vertice.y << ", " << vertice.z
                       << std::endl;
    }
    vertice_output.close();

    //Dart output
    std::ofstream dart_output;
    dart_output.open (file_out_csv_d);
    dart_output << "ID, a0, a1, a2, a3, v, e, f\n";
    for (auto dart : output_darts){
        dart_output<<dart.id<< ", "<<dart.alpha_0<< ", "<<dart.alpha_1<< ", "<<dart.alpha_2<< ", "<<dart.alpha_3<< ", "<<dart.vertice<< ", "<<dart.edge<< ", "<<dart.face<<std::endl;
    }
    dart_output.close();

    //edge output
    std::ofstream edge_output;
    edge_output.open (file_out_csv_1);
    edge_output << "ID, dart\n";
    for (auto edge : output_edges){
        edge_output<<edge.id<<", "<<edge.dart<<std::endl;
    }
    edge_output.close();

    //face output
    std::ofstream face_output;
    face_output.open(file_out_csv_2);
    face_output << "ID, dart\n";
    for (auto face: output_faces) {
        face_output << face.id<< ", " << face.dart << std::endl;
    }
    face_output.close();

    //volume output
    std::ofstream volume_output;
    volume_output.open (file_out_csv_3);
    volume_output << "ID, dart\n";
    for (auto volume : output_volume){
        volume_output<<volume.id<<", "<<volume.dart<<std::endl;
    }
    volume_output.close();


    // ## Construct generalised map using the structures from Gmap.h ##

    // ## Output generalised map to CSV ##

    // ## Create triangles from the darts ##

    // ## Write triangles to obj ##

        return 0;
    }