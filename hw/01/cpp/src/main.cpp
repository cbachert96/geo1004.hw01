// some standard libraries that are helpful for reading/writing text files
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Gmap.h"
#include <unordered_map>
#include <iomanip>

//to make a string out of 1 Point
std::string make_string(Point point){

    std::stringstream stream;
    stream << std::fixed << std::setprecision(4) << point.x << point.y << point.z;
    std::string stringed = stream.str();
    return stringed;
}

// to make a string out of two Points
std::string make_edge_string(Point point_1, Point point_2){
    std::stringstream stream;
    stream << std::fixed << std::setprecision(3) << point_1.x << point_1.y << point_1.z<<point_2.x << point_2.y << point_2.z;
    std::string stringed = stream.str();
    return stringed;
}

//to print an unordered_map
void print_map(std::unordered_map<std::string, int> const &m)
{
    for (auto const &pair: m) {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
}

int dart_id = 0;
int face_id = 0;
int edge_id = 0;
int vector_id = 0;


int main(int argc, const char * argv[]) {
    //input and output files.
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
                //vector to hold the 4 point_vertices of a Face
                std::vector<point_Vertex> face_points;
                //used indexes to get Vertex value.
                while (iss >> word) face_points.push_back((vertices[std::stoi(word)-1]));
                // place the vector of Vertices in vector faces
                faces.emplace_back(face_points);
            }
        }
    }

    //vectors to hold the output data of the designated types.
    std::vector<Vertex> output_vertices;
    std::vector<Face> output_faces;
    std::vector<Edge> output_edges;
    std::vector<Dart> output_darts;
    std::vector<Volume> output_volume;

    // since we only have 1 input file, and one volume, this part is hardcoded.
    output_volume.emplace_back(0,0);

    //make the unordered maps to check if a vertice or edge already exists
    std::unordered_map<std::string, int> unique_vertices = {};
    std::unordered_map<std::string, int> unique_edges = {};

    //loop through the faces vector to build the structures.
    for (auto face: faces){
        //id for face
        auto face_num = face_id++;
        // get a dart that is on the face
        auto dart_on_face = dart_id +1;
        output_faces.emplace_back(face_num, dart_on_face);
        //loop through the vertices in a face, to make the other structures
        for (int i = 0; i<face.vertices.size(); i++){
            //For each vertex we will make two faces
            auto dart_1 = dart_id++;
            auto dart_2 = dart_id++;
            //Make the vertex in a strin, so as to later be able to check if it already exists.
            auto str_vertex = make_string(face.vertices[i].point);
            int vertex_num;
            //If the vertice already exists in the unordered map, get the value of vertex_num from the value of the key-value pair.
            if (unique_vertices.count(str_vertex)) {
                vertex_num = unique_vertices.at(str_vertex);
            }
            //if it has not already been added.
            else{
                vertex_num = vector_id++;
                //add it to the unordered map
                unique_vertices[str_vertex] = vertex_num;
                //Place the vertex in the vector of Vertices.
                output_vertices.emplace_back(vertex_num, dart_1, face.vertices[i].x, face.vertices[i].y, face.vertices[i].z);
            }

            //Initiate two points, these will form an edge
            point_Vertex vertice_1;
            point_Vertex vertice_2;

            //two vertices to make an edge in between, 1st with 2nd and so on.
            if (i< (face.vertices.size() -1)){
                vertice_1 = face.vertices[i];
                vertice_2 = face.vertices[i+1];
            }
            //if we are at the final vertice, we need to make an edge between the final and first one.
            else{
                vertice_1 = face.vertices[i];
                vertice_2 = face.vertices[0];
            }

            // make the edge into a string, so as to check whether the edge already exists in the Gmap structure
            auto str_edge = make_edge_string(vertice_1.point, vertice_2.point);
            auto str_edge_rev = make_edge_string(vertice_2.point, vertice_1.point);
            int edge_num;
            // check if it already exists
            if (unique_edges.count(str_edge)) {
                edge_num = unique_edges.at(str_edge);
            }
            //if not: add both combinations of the edge to the unordered map
            else{
                edge_num = edge_id++;
                unique_edges[str_edge] = edge_num;
                unique_edges[str_edge_rev] = edge_num;
                //place the edge in the vector of Edges
                output_edges.emplace_back(edge_num, dart_1);
            }

            //initialize the alpha's
            int alpha_0_dart_1 = dart_1 +1;
            unsigned long alpha_1_dart_1;
            int alpha_2_dart_1 = 0;
            int alpha_3_dart_1 = 0;
            unsigned long alpha_1_dart_2;
            int alpha_0_dart_2 = dart_2 -1;
            int alpha_2_dart_2 = 0;
            int alpha_3_dart_2 = 0;

            //for the first dart, we need the final dart, that's why de do 2* the length of the vector -1. So dart 0 has 7 as alpha_0 in case of 4 vertices.
            if (i ==0){
                alpha_1_dart_1 = dart_1 + (2*face.vertices.size()-1);
                alpha_1_dart_2 = dart_2 +1;
                }

            //if we're at the final vertex, the last dart, let's say 7 needs to have 0 as the next, and not 8
            else if (i == face.vertices.size()-1){
                alpha_1_dart_1 = dart_1 -1;
                alpha_1_dart_2 = (dart_2 - (2*face.vertices.size())+1);
            }
            // if not at the first or final vertex
            else{
                alpha_1_dart_1 = dart_1 -1;
                alpha_1_dart_2 = dart_2 +1;
            }
            //place Darts in the vector of Darts.
            output_darts.emplace_back(dart_1,vertex_num, edge_num, face_num, alpha_0_dart_1, alpha_1_dart_1, alpha_2_dart_1, alpha_3_dart_1);
            output_darts.emplace_back(dart_2,vertex_num+1, edge_num, face_num, alpha_0_dart_2, alpha_1_dart_2, alpha_2_dart_2, alpha_3_dart_2);
        }
    }

// get alpha 2 values of darts.
// for each dart
    for (auto &dart_1 : output_darts) {
        // loop through all darts
        for (auto &dart_2: output_darts) {
            //check if it's not the same dart
            if (dart_1.id != dart_2.id) {
                //if they have the same vertice and the same edge
                if (dart_1.vertice == dart_2.vertice && dart_1.edge == dart_2.edge) {
                    //assign the ID of dart_2 1 to the alpha_2 value of dart 1
                    dart_1.alpha_2 = dart_2.id;
                }
            }
        }
    }

    //vertex output
    std::ofstream vertice_output;
    vertice_output.open(file_out_csv_0);
    vertice_output << "ID, dart, x, y, z\n";
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