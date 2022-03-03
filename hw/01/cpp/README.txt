hw01: Triangulating a polygonal mesh with generalised maps
Siebren Meines, Carolin Bachert

What does the code do?

	The code implemets a generalised map (g-map) out of a 3D polygonal mesh and triangulates it in a last step.
	It works for a single volume only and assumes that all the faces are convex without any holes.

	Input:
	* a 3D polygonal mesh in OBJ format

	Output:
	* 5 csv files for the implemented gmap containing the darts (torus_darts.csv, torus_vertices.csv, torus_edges.csv, torus_faces.csv, torus_volume.csv)
	* triangulated mesh in obj format (torus_triangulated.obj)


What is in the code?
	
	* main.cpp: This file conatins the main implementation of the code. It includes some general functions that are needed throughout the 
				the remaining script. Within the main function the contents of the obj file is read and stored appropriately, the gmap with
				its darts and components is derived by looping through the faces, the triangulation of the mesh is constructed based on the 
				gmap, and eventually the information is written to the according output files.
	* Point.h:	A structure to store 3D points/vectors with some convenient functions to do simple operations.
	* Gmap.h: 	Defines the basic structures that are needed for the gmap (Dart, Vertex, Edge, Face, Volume) and includes some operations
				for them that are meeded in main.cpp.


How to compile and run the code?

    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ ./hw01

