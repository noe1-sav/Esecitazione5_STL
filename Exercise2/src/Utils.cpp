#include "Utils.hpp" 
#include "PolygonalMesh.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;

namespace 	TriangularLibrary
{
bool ImportMesh(PolygonalMesh& mesh)
{   if(!ImportCell0Ds(mesh))
        return false;

    if(!ImportCell1Ds(mesh))
        return false;

    if(!ImportCell2Ds(mesh))
        return false;
    return false;
}
}

namespace TriangularLibrary{
bool ImportCell0Ds(PolygonalMesh& mesh)
{
    ifstream file("./Cell0Ds.csv");

    if (file.fail())
        return false;

    list<string> listLines;

    string line;
    while (getline(file, line))
        listLines.push_back(line);

    file.close();

    // remove header
    listLines.pop_front();

    mesh.NumCell0Ds = listLines.size();

    if (mesh.NumCell0Ds == 0)
    {
        cerr << "There is no cell 0D" << endl;
        return false;
    }

    mesh.Cell0DsId.reserve(mesh.NumCell0Ds);
    mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds);

    for (const string& line : listLines)
    {
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;
        Vector2d coord;

        converter >>  id >> marker >> mesh.Cell0DsCoordinates(0, id) >> mesh.Cell0DsCoordinates(1, id);

        mesh.Cell0DsId.push_back(id);

		
		if(marker != 0)
		{
			auto it = mesh.MarkerCell0Ds.find(marker); //cerca nella mappa
			if(it != mesh.MarkerCell0Ds.end())
			{
				(*it).second.push_back(id);
				// o fare direttamente
				//mesh.MarkerCellODs[marker].push_back(id);
			}
			else
			{
				mesh.MarkerCell0Ds.insert({marker,{id}});
			}
		}
		if(marker != 0)
		{
			auto it = mesh.MarkerCell1Ds.find(marker); 
			if(it != mesh.MarkerCell1Ds.end())
			{
				(*it).second.push_back(id);
			}
			else
			{
				mesh.MarkerCell1Ds.insert({marker,{id}});
			}
		}
	}
  return true;
}
}
// ***************************************************************************
namespace 	TriangularLibrary
{
bool ImportCell1Ds(PolygonalMesh& mesh)
{
    ifstream file("./Cell1Ds.csv");

    if(file.fail())
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
	{
        listLines.push_back(line);
	};

    file.close();

    // remove header
    listLines.pop_front();

    mesh.NumCell1Ds = listLines.size();

    if (mesh.NumCell1Ds == 0)
    {
        cerr << "There is no cell 1D" << endl;
        return false;
    }

    mesh.Cell1DsId.reserve(mesh.NumCell1Ds);
    mesh.Cell1DsExtrema = Eigen::MatrixXi(2, mesh.NumCell1Ds);

    for (const string& line : listLines)
    {
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;
        Eigen::Vector2i vertices;

        converter >>  id >> marker >>  mesh.Cell1DsExtrema(0, id) >>  mesh.Cell1DsExtrema(1, id);
        mesh.Cell1DsId.push_back(id);

        /// Memorizza i marker
    }

    return true;
}
}
// ***************************************************************************
namespace TriangularLibrary
{
bool ImportCell2Ds(PolygonalMesh& mesh)
{
    ifstream file;
    file.open("./Cell2Ds.csv");

    if(file.fail())
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    file.close();

    // remove header
    listLines.pop_front();

    mesh.NumCell2Ds = listLines.size();

    if (mesh.NumCell2Ds == 0)
    {
        cerr << "There is no cell 2D" << endl;
        return false;
    }

    mesh.Cell2DsId.reserve(mesh.NumCell2Ds);
    mesh.Cell2DsVertices.reserve(mesh.NumCell2Ds);
    mesh.Cell2DsEdges.reserve(mesh.NumCell2Ds);
    
    for (const string& line : listLines)
    {
        istringstream converter(line);
//essendo per poligoni generici bisogna togliere la dimensione fissa =3
        unsigned int id;
	    unsigned int numVertices=0;
        vector<unsigned int>vertices(numVertices);
        vector<unsigned int>edges(numVertices);

        for(unsigned int i = 0; i < numVertices; i++)
            converter >> vertices[i];
        for(unsigned int i = 0; i < numVertices; i++)
            converter >> edges[i];

        mesh.Cell2DsId.push_back(id);
        mesh.Cell2DsVertices.push_back(vertices);
        mesh.Cell2DsEdges.push_back(edges);
    }

    return true;
}
}
