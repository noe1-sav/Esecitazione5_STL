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
		Eigen::MatrixXd Cell0DsCoordinates;
		
		//lati e celle, paraview dà delle funzioni		
        vector<unsigned int> Cell0DsMarker;
	    vector<unsigned int> Cell1DsMarker;
	 
	    Eigen::MatrixXi Cell1DsExtrema;
		vector<vector<unsigned int>> Cell2DsVertices;	
        vector<vector<unsigned int>> Cell2DsEdges;
        
		//mappo
		map<unsigned int, list<unsigned int>> MarkerCell0Ds;
	    map<unsigned int, list<unsigned int>> MarkerCell1Ds;
	   
	
        		
};

}

