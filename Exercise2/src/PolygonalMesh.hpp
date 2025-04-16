#pragma once
#include <iostream>
#include "Eigen/Eigen"
using namespace std;


namespace TriangularLibrary {
	struct PolygonalMesh
{
		unsigned int NumCell0Ds;
		unsigned int NumCell1Ds;
		unsigned int NumCell2Ds;
		

		vector<unsigned int> Cell0DsId;
		vector<unsigned int> Cell1DsId;
		vector<unsigned int> Cell2DsId;
		
		//memorizzo coordinate
		Eigen::MatrixXd Cell0DsCoordinates; //perchè farò delle operazioni matematiche così non le devo di nuovo implementare
	    Eigen::MatrixXi Cell1DsExtrema;
		
		//lati e celle, paraview dà delle funzioni		
        vector<unsigned int> Cell0DsMarker;
	    vector<unsigned int> Cell01sMarker;
		
		vector<std::vector<unsigned int>> Cell2DsVertices;
        vector<std::vector<unsigned int>> Cell2DsEdges;
       
		//mappo
		map<unsigned int, list<unsigned int>> MarkerCell0Ds;
	    map<unsigned int, list<unsigned int>> MarkerCell1Ds;
};

}
