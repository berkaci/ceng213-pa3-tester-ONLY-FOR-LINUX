#include "your_code/ObjLoader.h"
#include "your_code/BinaryHeap.cpp"
#include "your_code/BinaryHeap.h"
#include "your_code/MeshGraph.cpp"
#include "your_code/MeshGraph.h"
#include "your_code/ObjLoader.cpp"
#include "your_code/Structs.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>



#define VCOUNT 139
#define FN "facem-low2"

using namespace std;

void addtofile(ofstream &s, vector<Color> colors)
{
    for(int i = 0; i < (colors.size()); i++)
    {
        int r = (colors[i].r);
        int g = (colors[i].g);
        int b = (colors[i].b);

        s << +r << ", " << +g << ", " << +b << "\n";
    }

}

int main(int argv, const char* argc[])
{
    // You can use to test your code here
    ObjLoader a;
    Color kir;
    kir.r=255;
    kir.g=230;
    kir.b=200;
    a.LoadObjFile(FN+string(".obj"));
    std::vector<Double3> gvp=a.GetVertexPos();

    MeshGraph g(gvp,a.GetEdges());

    ofstream ff;
    ff.open(string("your_outputs/")+FN+"/0_short_funcs");
    ff << "AverageDistanceBetweenVertices: " << g.AverageDistanceBetweenVertices() << endl;
    ff << "AverageEdgePerVertex: " << g.AverageEdgePerVertex() << endl;
    ff << "TotalVertexCount: " << g.TotalVertexCount() << endl;
    ff << "TotalEdgeCount: " << g.TotalEdgeCount() << endl;
    ff.close();
    ff.open(string("your_outputs/")+FN+"/1_funcs_by_vertex");
    vector<int> outv;
    for(int i=0; i<VCOUNT; i++)
    {
        ff << string("Vertex ")<< i << ":\n";
        ff << "VertexEdgeCount: " << g.VertexEdgeCount(i)<< endl;
        ff << "ImmediateNeighbours: " ;
        sort(outv.begin(), outv.end());

        g.ImmediateNeighbours(outv, i);
        for(int j=0; j<outv.size(); j++)
        {
            ff << outv[j] << " ";
        }
        ff << endl << endl;

    }
    ff.close();
    ofstream between, geog, geob, eucg, eucb;



    for(int i=0; i< VCOUNT; i+=2 )
    {
        string ii;
        stringstream ssi;
        ssi << i;
        ii=ssi.str();
    	between.open(string("your_outputs/")+FN+"/2_PaintInBetweenVertex( vector , " + ii + " , ... , color)");
    	geog.open(string("your_outputs/")+FN+"/3_PaintInRangeGeodesic( vector , " + ii + " , color , ... , FILTER_GAUSSIAN , 10 )");
    	geob.open(string("your_outputs/")+FN+"/3_PaintInRangeGeodesic( vector , " + ii + " , color , ... , FILTER_BOX , 10 )");
    	eucg.open(string("your_outputs/")+FN+"/4_PaintInRangeEuclidian( vector , " + ii + " , color , ... , FILTER_GAUSSIAN , 10 )");
    	eucb.open(string("your_outputs/")+FN+"/4_PaintInRangeEuclidian( vector , " + ii + " , color , ... , FILTER_BOX , 10 )");

        for(int j=0;j<VCOUNT;j+=10)
        {
            vector<Color> vec;
            string jj;
            stringstream ssj;
            ssj << j;
            jj=ssj.str();
            between << "PaintInBetweenVertex( vector , " + ii + " , " + jj + " , color): " << endl;
            geog << "PaintInRangeGeodesic( vector , " + ii + " , color , " + jj + " , FILTER_GAUSSIAN , 10 ): " << endl;
            geob << "PaintInRangeGeodesic( vector , " + ii + " , color , " + jj + " , FILTER_BOX , 10 ): " << endl;
            eucg << "PaintInRangeEuclidian( vector , " + ii + " , color , " + jj + " , FILTER_GAUSSIAN , 10 ): " << endl;
            eucb << "PaintInRangeEuclidian( vector , " + ii + " , color , " + jj + " , FILTER_BOX , 10 ): " << endl;
            g.PaintInBetweenVertex( vec , i , j , kir);
            addtofile(between, vec);
            between << endl;

            g.PaintInRangeGeodesic( vec , i , kir , j , FILTER_GAUSSIAN , 10 );
            addtofile(geog, vec);
            geog << endl;
            g.PaintInRangeGeodesic( vec , i , kir , j , FILTER_BOX , 10 );
            addtofile(geob, vec);
            geob << endl;

            g.PaintInRangeEuclidian( vec , i , kir , j , FILTER_GAUSSIAN , 10 );
            addtofile(eucg, vec);
            eucg << endl;
            g.PaintInRangeEuclidian( vec , i , kir , j , FILTER_BOX , 10 );
            addtofile(eucb, vec);
            eucb << endl;



        }

    	between.close();
    	geog.close();
    	geob.close();
    	eucg.close();
    	eucb.close();

    }

}
