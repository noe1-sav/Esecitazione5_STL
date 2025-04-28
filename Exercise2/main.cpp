#include "PolygonalMesh.hpp"
#include "Utils.hpp"
#include "UCDUtilities.hpp"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Eigen/Eigen"
using namespace std;
using namespace Eigen;
using namespace TriangularLibrary;

double PartialPolygonArea(const vector<unsigned int>& polygonVertices, const Eigen::MatrixXd& point){
	double area= 0.0;
	int n = polygonVertices.size(); 
	
	for(int i=0; i<n; i++){
		int j=(i+1) % n;
		unsigned int p1=polygonVertices[i];
		unsigned int p2=polygonVertices[j];
		area += point(0, p1) * point(1, p2) - point(1, p1) * point(0, p2);
		
	}
	area = abs(area)*0.5;
	return area;
}

int main()
{	Gedim::UCDUtilities utilities;
	

	PolygonalMesh mesh;

    if(!ImportMesh(mesh))
    {
        cerr << "file not found" << endl;
        return 1;
    }
	utilities.ExportPoints("./Cell0Ds.inp", mesh.Cell0DsCoordinates);
	utilities.ExportSegments("./Cell1Ds.inp",
                             mesh.Cell0DsCoordinates,
                             mesh.Cell1DsExtrema);


    for (size_t i = 0; i < mesh.Cell2DsVertices.size(); ++i) {
        const vector<unsigned int>& polygon = mesh.Cell2DsVertices[i];
        double area = PartialPolygonArea(polygon, mesh.Cell0DsCoordinates);
        cout << "Area del poligono " << i + 1 << ": " << area << endl;
    }
    return 0;
}
