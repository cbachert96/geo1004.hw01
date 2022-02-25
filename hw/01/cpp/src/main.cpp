// some standard libraries that are helpful for reading/writing text files
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Gmap.h"
#include <unordered_map>
#include <iomanip>

//struct point_Key
//{
//    Point point;
//
//    bool operator==(const point_Key &other) const
//    { return (point == other.point);
//    }
//};
//
//    template <>
//    struct std::hash<point_Key>
//    {
//        std::size_t operator()(const point_Key& k) const
//        {
//            using std::size_t;
//            using std::hash;
//            using std::string;
//            using Point;
//
//            // Compute individual hash values for first,
//            // second and third and combine them using XOR
//            // and bit shifting:
//
//            return ((hash<Point>()(k.first)
//                     ^ (hash<string>()(k.second) << 1)) >> 1)
//                   ^ (hash<int>()(k.third) << 1);
//        }
//    };


std::string make_string(Point point){

    std::stringstream stream;
    stream << std::fixed << std::setprecision(4) << point.x << point.y << point.z;
    std::string stringed = stream.str();
    return stringed;
}

std::string make_edge_string(Point point_1, Point point_2){

    std::stringstream stream;
    stream << std::fixed << std::setprecision(3) << point_1.x << point_1.y << point_1.z<<point_2.x << point_2.y << point_2.z;
    std::string stringed = stream.str();
    return stringed;
}

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
                //vector to hold the 4 vertices of a Face
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
    std::vector<Volume> output_volume;
    std::vector<Edge> output_edges;
    std::vector<Dart> output_darts;

    //make the unordered maps
    std::unordered_map<std::string, int> unique_vertices = {};
    std::unordered_map<std::string, int> unique_edges = {};
    output_volume.emplace_back(0,0);


    //loop through the faces vector to build the structure.
    for (auto face: faces){
        //id for face
        auto face_num = face_id++;
        auto dart_on_face = dart_id +1;
        output_faces.emplace_back(face_num, dart_on_face);
        //loop through the vertices in a face, to make the other structures
        for (int i = 0; i<face.vertices.size(); i++){
            auto dart_1 = dart_id++;
            auto dart_2 = dart_id++;
            // check if this edge has already been visited:
            auto str_vertex = make_string(face.vertices[i].point);
            int vertex_num;
            if (unique_vertices.count(str_vertex)) {
                vertex_num = unique_vertices.at(str_vertex);

//                std::cout<<"if"<< vertex_num<<std::endl;
            }
            else{
                vertex_num = vector_id++;
//                std::cout<<"else"<< vertex_num<<std::endl;
                unique_vertices[str_vertex] = vertex_num;
                output_vertices.emplace_back(vertex_num, dart_1, face.vertices[i].x, face.vertices[i].y, face.vertices[i].z);
            }

            //assign id's, it's just a number that goes up 1 each time it's called.
            point_Vertex vertice_1;
            point_Vertex vertice_2;

            //two vertices to make an edge in between, 1st with 2nd and so on.
            if (i< (face.vertices.size() -1)){
                vertice_1 = face.vertices[i];
                vertice_2 = face.vertices[i+1];
            }
            //if we are at the final vertice, we also need to make an edge between the final and first one.
            else{
                vertice_1 = face.vertices[i];
                vertice_2 = face.vertices[0];
            }

            auto str_edge = make_edge_string(vertice_1.point, vertice_2.point);
            auto str_edge_rev = make_edge_string(vertice_2.point, vertice_1.point);
            int edge_num;
            if (unique_edges.count(str_edge)) {
                edge_num = unique_edges.at(str_edge);
//                std::cout<<"test"<<std::endl;
            }
            else{
                edge_num = edge_id++;
                unique_edges[str_edge] = edge_num;
                unique_edges[str_edge_rev] = edge_num;
                output_edges.emplace_back(edge_num, dart_1);
            }
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
            else{
                alpha_1_dart_1 = dart_1 -1;
                alpha_1_dart_2 = dart_2 +1;
            }
//            std::cout<<vertex_num<<std::endl;
            output_darts.emplace_back(dart_1,vertex_num, edge_num, face_num, alpha_0_dart_1, alpha_1_dart_1, alpha_2_dart_1, alpha_3_dart_1);
            output_darts.emplace_back(dart_2,vertex_num+1, edge_num, face_num, alpha_0_dart_2, alpha_1_dart_2, alpha_2_dart_2, alpha_3_dart_2);
        }
    }

    std::vector<Dart> alpha_darts;
//    get alpha 2 values of darts.
    for (auto &dart_1 : output_darts) {
        for (auto &dart_2: output_darts) {
            if (dart_1.id != dart_2.id) {
                if (dart_1.vertice == dart_2.vertice && dart_1.edge == dart_2.edge) {
                    dart_1.alpha_2 = dart_2.id;
//                    dart_1 = Dart(dart_1.id, dart_1.vertice, dart_1.edge, dart_1.face, dart_1.alpha_0, dart_1.alpha_1,
//                                  dart_2.id,
//                                  dart_1.alpha_3);
                    alpha_darts.emplace_back(
                            Dart(dart_1.id, dart_1.vertice, dart_1.edge, dart_1.face, dart_1.alpha_0, dart_1.alpha_1,
                                 dart_2.id,
                                 dart_1.alpha_3));
                }
//                else{
//                    alpha_darts.emplace_back(
//                            Dart(dart_1.id, dart_1.vertice, dart_1.edge, dart_1.face, dart_1.alpha_0, dart_1.alpha_1,
//                                 dart_1.alpha_2,
//                                 dart_1.alpha_3));
//                }

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