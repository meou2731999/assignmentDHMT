#if !defined (_MESH_CLASS)
#define _MESH_CLASS

#include "supportClass.h"


class VertexID
{
public:
	int		vertIndex;
	int		colorIndex;
};

class Face
{
public:
	int		nVerts;
	VertexID*	vert;
	
	Face()
	{
		nVerts	= 0;
		vert	= NULL;
	}
	~Face()
	{
		if(vert !=NULL)
		{
			delete[] vert;
			vert = NULL;
		}
		nVerts = 0;
	}
};

class Mesh
{
public:
	int		numVerts;
	Point3*		pt;
	
	int		numFaces;
	Face*		face;
    
    float   slideX, slideY, slideZ;
    float   rotateX, rotateY, rotateZ;
    float   scaleX, scaleY, scaleZ;
public:
	Mesh()
	{
		numVerts	= 0;
		pt		= NULL;
		numFaces	= 0;
		face		= NULL;
        slideX      = 0;
        slideY      = 0;
        slideZ      = 0;
        rotateX     = 0;
        rotateY     = 0;
        rotateZ     = 0;
        scaleX      = 1;
        scaleY      = 1;
        scaleZ      = 1;
	}
	~Mesh()
	{
		if (pt != NULL)
		{
			delete[] pt;
		}	
		if(face != NULL)
		{
			delete[] face;
		}
		numVerts = 0;
		numFaces = 0;
	}
	void DrawWireframe();
	void DrawColor();
    void SetColor(int colorIdx);

	void CreateTetrahedron();
	void CreateCube(float	fSize);
    void CreateCuboid(float fSizeX, float fSizeY, float fSizeZ);
    void CreateCylinder(int nSegment, float fHeight, float fRadius);
    void CreateCylinderWithHole(int nSegment, float fHeight, float fRadiusIn, float fRadiusOut);
    void CreateBoxWithCleft(float fSizeX, float fSizeY, float fSizeZ, float zTCleft, float zBCleft, float hCleft);
    void CreateBoxWithLegde(float fSizeX, float fSizeY, float fSizeZ, float zTCleft, float zBCleft, float hCleft);
    void CreateCylinderColapCuboid(int nSegment, float fHeight,float fLong, float fRadius);
    void CreateDoubleSemicircle(int nSegment, float fHeight, float fRadius1, float fRadius2, float fDistance);
    void CreateBoxConnectCylinder(int nSegment, float fHeight, float fLong, float fRadiusIn, float fRadiusOut);
};

#endif
