#define GL_SILENCE_DEPRECATION
#include "Mesh.h"
#include <math.h>
#include <iostream>

#define PI			3.1415926
#define	COLORNUM		14


float	ColorArr[COLORNUM][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, { 0.0,  0.0, 1.0}, 
								{1.0, 1.0,  0.0}, { 1.0, 0.0, 1.0},{ 0.0, 1.0, 1.0}, 
								 {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, { 0.9,  0.9, 0.9},
								{1.0, 0.5,  0.5}, { 0.5, 1.0, 0.5},{ 0.5, 0.5, 1.0},
									{0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}};





void Mesh::CreateCube(float	fSize)
{
	int i;
	numVerts=8;
	pt = new Point3[numVerts];
	pt[0].set(-fSize, fSize, fSize);
	pt[1].set( fSize, fSize, fSize);
	pt[2].set( fSize, fSize, -fSize);
	pt[3].set(-fSize, fSize, -fSize);
	pt[4].set(-fSize, -fSize, fSize);
	pt[5].set( fSize, -fSize, fSize);
	pt[6].set( fSize, -fSize, -fSize);
	pt[7].set(-fSize, -fSize, -fSize);


	numFaces= 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;
	
	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for(i = 0; i<face[4].nVerts ; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for(i = 0; i<face[5].nVerts ; i++)
		face[5].vert[i].colorIndex = 5;

}

void Mesh::CreateCuboid(float fSizeX, float fSizeY, float fSizeZ)
{
    int i;
    
    numVerts=8;
    pt = new Point3[numVerts];
    pt[0].set(-fSizeX, fSizeY, fSizeZ);
    pt[1].set( fSizeX, fSizeY, fSizeZ);
    pt[2].set( fSizeX, fSizeY, -fSizeZ);
    pt[3].set(-fSizeX, fSizeY, -fSizeZ);
    pt[4].set(-fSizeX, -fSizeY, fSizeZ);
    pt[5].set( fSizeX, -fSizeY, fSizeZ);
    pt[6].set( fSizeX, -fSizeY, -fSizeZ);
    pt[7].set(-fSizeX, -fSizeY, -fSizeZ);


    numFaces= 6;
    face = new Face[numFaces];

    //Left face
    face[0].nVerts = 4;
    face[0].vert = new VertexID[face[0].nVerts];
    face[0].vert[0].vertIndex = 1;
    face[0].vert[1].vertIndex = 5;
    face[0].vert[2].vertIndex = 6;
    face[0].vert[3].vertIndex = 2;
    for(i = 0; i<face[0].nVerts ; i++)
        face[0].vert[i].colorIndex = 0;
    
    //Right face
    face[1].nVerts = 4;
    face[1].vert = new VertexID[face[1].nVerts];
    face[1].vert[0].vertIndex = 0;
    face[1].vert[1].vertIndex = 3;
    face[1].vert[2].vertIndex = 7;
    face[1].vert[3].vertIndex = 4;
    for(i = 0; i<face[1].nVerts ; i++)
        face[1].vert[i].colorIndex = 1;

    //top face
    face[2].nVerts = 4;
    face[2].vert = new VertexID[face[2].nVerts];
    face[2].vert[0].vertIndex = 0;
    face[2].vert[1].vertIndex = 1;
    face[2].vert[2].vertIndex = 2;
    face[2].vert[3].vertIndex = 3;
    for(i = 0; i<face[2].nVerts ; i++)
        face[2].vert[i].colorIndex = 2;

    //bottom face
    face[3].nVerts = 4;
    face[3].vert = new VertexID[face[3].nVerts];
    face[3].vert[0].vertIndex = 7;
    face[3].vert[1].vertIndex = 6;
    face[3].vert[2].vertIndex = 5;
    face[3].vert[3].vertIndex = 4;
    for(i = 0; i<face[3].nVerts ; i++)
        face[3].vert[i].colorIndex = 3;

    //near face
    face[4].nVerts = 4;
    face[4].vert = new VertexID[face[4].nVerts];
    face[4].vert[0].vertIndex = 4;
    face[4].vert[1].vertIndex = 5;
    face[4].vert[2].vertIndex = 1;
    face[4].vert[3].vertIndex = 0;
    for(i = 0; i<face[4].nVerts ; i++)
        face[4].vert[i].colorIndex = 4;

    //Far face
    face[5].nVerts = 4;
    face[5].vert = new VertexID[face[5].nVerts];
    face[5].vert[0].vertIndex = 3;
    face[5].vert[1].vertIndex = 2;
    face[5].vert[2].vertIndex = 6;
    face[5].vert[3].vertIndex = 7;
    for(i = 0; i<face[5].nVerts ; i++)
        face[5].vert[i].colorIndex = 5;

}

void Mesh::CreateTetrahedron()
{
	int i;
	numVerts=4;
	pt = new Point3[numVerts];
	pt[0].set(0, 0, 0);
	pt[1].set(1, 0, 0);
	pt[2].set(0, 1, 0);
	pt[3].set(0, 0, 1);

	numFaces= 4;
	face = new Face[numFaces];

	face[0].nVerts = 3;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 2;
	face[0].vert[2].vertIndex = 3;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;
	

	face[1].nVerts = 3;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;	
	face[1].vert[1].vertIndex = 2;
	face[1].vert[2].vertIndex = 1;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

	
	face[2].nVerts = 3;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 3;
	face[2].vert[2].vertIndex = 2;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;


	face[3].nVerts = 3;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 1;
	face[3].vert[1].vertIndex = 3;
	face[3].vert[2].vertIndex = 0;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;
}

void Mesh::CreateCylinder(int nSegment, float fHeight, float fRadius){
    numVerts=nSegment*2 + 2;
    pt = new Point3[numVerts];

    int        i;
    int        idx;
    float    fAngle = 2*PI/nSegment;
    float    x, y, z;

    pt[0].set(0, fHeight/2, 0);
    for(i = 0; i<nSegment; i++){
        x = fRadius* cos(fAngle*i);
        z = fRadius* sin(fAngle*i);
        y = fHeight/2;
        pt[i+1].set(x, y, z);

        y = -fHeight/2;
        pt[i +1 + nSegment].set(x, y, z);
    }
    pt[numVerts-1].set(0, -fHeight/2, 0);

    numFaces= nSegment*3;
    face = new Face[numFaces];

    idx = 0;
    for(i = 0; i<nSegment; i++){
        face[idx].nVerts = 3;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = 0;
        if(i < nSegment -1)
            face[idx].vert[1].vertIndex = i + 2;
        else
            face[idx].vert[1].vertIndex = 1;
        face[idx].vert[2].vertIndex = i + 1;
        idx++;
    }

    for(i = 0; i<nSegment; i++){
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        
        face[idx].vert[0].vertIndex = i+1;
        if(i <nSegment - 1)
            face[idx].vert[1].vertIndex = i+2;
        else
            face[idx].vert[1].vertIndex = 1;
        face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
        face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

        idx++;
    }

    for(i = 0; i<nSegment; i++){
        face[idx].nVerts = 3;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = numVerts - 1;
        if(i < nSegment -1)
            face[idx].vert[2].vertIndex = i + 2 + nSegment;
        else
            face[idx].vert[2].vertIndex = 1 + nSegment;
        face[idx].vert[1].vertIndex = i + 1 + nSegment;
        idx++;
    }
}
void Mesh::CreateCylinderWithHole(int nSegment, float fHeight, float fRadiusIn, float fRadiusOut){
    numVerts=nSegment*4;
    pt = new Point3[numVerts];

    int        i;
    int        idx;
    float    fAngle = 2*PI/nSegment;
    float    x, y, z;

    for(i = 0; i<nSegment; i++){
        x = fRadiusIn* cos(fAngle*i);
        z = fRadiusIn* sin(fAngle*i);
        y = fHeight/2;
        pt[i].set(x, y, z);
        
        y = -fHeight/2;
        pt[i + nSegment].set(x, y, z);
        
        x = fRadiusOut* cos(fAngle*i);
        z = fRadiusOut* sin(fAngle*i);
        y = fHeight/2;
        pt[i + nSegment * 2].set(x, y, z);
        
        y = -fHeight/2;
        pt[i + nSegment * 3].set(x, y, z);
    }
    
    numFaces= nSegment*4;
    face = new Face[numFaces];

    idx = 0;
    for(i = 0; i<nSegment; i++){
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = i;
        face[idx].vert[3].vertIndex = i + 2*nSegment;
        if(i < nSegment - 1)
        {
            face[idx].vert[1].vertIndex = i + 1;
            face[idx].vert[2].vertIndex = i + 1 + 2 * nSegment;
        }
        else
        {
            face[idx].vert[1].vertIndex = 0;
            face[idx].vert[2].vertIndex = 0 + 2 * nSegment;
        }
        idx++;
    }

    for(i = 0; i<nSegment; i++){
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = i;
        face[idx].vert[3].vertIndex = i + nSegment;
        if(i < nSegment - 1)
        {
            face[idx].vert[1].vertIndex = i + 1;
            face[idx].vert[2].vertIndex = i + 1 + nSegment;
        }
        else
        {
            face[idx].vert[1].vertIndex = 0;
            face[idx].vert[2].vertIndex = 0 + nSegment;
        }
        idx++;
    }

    for(i = 0; i<nSegment; i++){
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = i + 2 * nSegment;
        face[idx].vert[3].vertIndex = i + 3 * nSegment;
        if(i < nSegment - 1)
        {
            face[idx].vert[1].vertIndex = i + 1 + 2 * nSegment;
            face[idx].vert[2].vertIndex = i + 1 + 3 * nSegment;
        }
        else
        {
            face[idx].vert[1].vertIndex = 0 + 2 * nSegment;
            face[idx].vert[2].vertIndex = 0 + 3 * nSegment;
        }
        idx++;
    }

    for(i = 0; i<nSegment; i++){
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = i + nSegment;
        face[idx].vert[3].vertIndex = i + 3 * nSegment;
        if(i < nSegment - 1)
        {
            face[idx].vert[1].vertIndex = i + 1 + nSegment;
            face[idx].vert[2].vertIndex = i + 1 + 3 * nSegment;
        }
        else
        {
            face[idx].vert[1].vertIndex = 0 + nSegment;
            face[idx].vert[2].vertIndex = 0 + 3 * nSegment;
        }
        idx++;
    }
}

void Mesh::CreateBoxWithCleft(float fSizeX, float fSizeY, float fSizeZ, float zTCleft, float zBCleft, float hCleft){
    
    int i;

    numVerts = 20;
    pt = new Point3[numVerts];
    pt[0].set(-fSizeX, fSizeY, fSizeZ);
    pt[1].set( fSizeX, fSizeY, fSizeZ);
    pt[2].set( fSizeX, fSizeY, -fSizeZ);
    pt[3].set(-fSizeX, fSizeY, -fSizeZ);
    pt[4].set(-fSizeX, -fSizeY, fSizeZ);
    pt[5].set( fSizeX, -fSizeY, fSizeZ);
    pt[6].set( fSizeX, -fSizeY, -fSizeZ);
    pt[7].set(-fSizeX, -fSizeY, -fSizeZ);
    pt[8].set(-fSizeX, fSizeY, zTCleft);
    pt[9].set( fSizeX, fSizeY, zTCleft);
    pt[10].set( fSizeX, fSizeY, -zTCleft);
    pt[11].set(-fSizeX, fSizeY, -zTCleft);
    pt[12].set(-fSizeX, fSizeY - hCleft, zBCleft);
    pt[13].set( fSizeX, fSizeY - hCleft, zBCleft);
    pt[14].set( fSizeX, fSizeY - hCleft, -zBCleft);
    pt[15].set(-fSizeX, fSizeY - hCleft, -zBCleft);
    pt[16].set(-fSizeX, fSizeY - hCleft, fSizeZ);
    pt[17].set( fSizeX, fSizeY - hCleft, fSizeZ);
    pt[18].set( fSizeX, fSizeY - hCleft, -fSizeZ);
    pt[19].set(-fSizeX, fSizeY - hCleft, -fSizeZ);


    numFaces= 14;
    face = new Face[numFaces];

    //Near face
    face[0].nVerts = 4;
    face[0].vert = new VertexID[face[0].nVerts];
    face[0].vert[0].vertIndex = 0;
    face[0].vert[1].vertIndex = 1;
    face[0].vert[2].vertIndex = 5;
    face[0].vert[3].vertIndex = 4;
    for(i = 0; i<face[0].nVerts ; i++)
        face[0].vert[i].colorIndex = 0;
    
    //Far face
    face[1].nVerts = 4;
    face[1].vert = new VertexID[face[1].nVerts];
    face[1].vert[0].vertIndex = 2;
    face[1].vert[1].vertIndex = 3;
    face[1].vert[2].vertIndex = 7;
    face[1].vert[3].vertIndex = 6;
    for(i = 0; i<face[1].nVerts ; i++)
        face[1].vert[i].colorIndex = 1;

    //Bottom face
    face[2].nVerts = 4;
    face[2].vert = new VertexID[face[2].nVerts];
    face[2].vert[0].vertIndex = 4;
    face[2].vert[1].vertIndex = 5;
    face[2].vert[2].vertIndex = 6;
    face[2].vert[3].vertIndex = 7;
    for(i = 0; i<face[2].nVerts ; i++)
        face[2].vert[i].colorIndex = 2;

    //Top Near Out face
    face[3].nVerts = 4;
    face[3].vert = new VertexID[face[3].nVerts];
    face[3].vert[0].vertIndex = 8;
    face[3].vert[1].vertIndex = 9;
    face[3].vert[2].vertIndex = 1;
    face[3].vert[3].vertIndex = 0;
    for(i = 0; i<face[3].nVerts ; i++)
        face[3].vert[i].colorIndex = 3;

    //Top Far Out face
    face[4].nVerts = 4;
    face[4].vert = new VertexID[face[4].nVerts];
    face[4].vert[0].vertIndex = 2;
    face[4].vert[1].vertIndex = 3;
    face[4].vert[2].vertIndex = 11;
    face[4].vert[3].vertIndex = 10;
    for(i = 0; i<face[4].nVerts ; i++)
        face[4].vert[i].colorIndex = 4;

    //In Near Face
    face[5].nVerts = 4;
    face[5].vert = new VertexID[face[5].nVerts];
    face[5].vert[0].vertIndex = 9;
    face[5].vert[1].vertIndex = 8;
    face[5].vert[2].vertIndex = 12;
    face[5].vert[3].vertIndex = 13;
    for(i = 0; i<face[5].nVerts ; i++)
        face[5].vert[i].colorIndex = 5;
    
    //In Far Face
    face[6].nVerts = 4;
    face[6].vert = new VertexID[face[6].nVerts];
    face[6].vert[0].vertIndex = 11;
    face[6].vert[1].vertIndex = 10;
    face[6].vert[2].vertIndex = 14;
    face[6].vert[3].vertIndex = 15;
    for(i = 0; i<face[6].nVerts ; i++)
        face[6].vert[i].colorIndex = 6;
    
    //In Bottom Face
    face[7].nVerts = 4;
    face[7].vert = new VertexID[face[7].nVerts];
    face[7].vert[0].vertIndex = 15;
    face[7].vert[1].vertIndex = 14;
    face[7].vert[2].vertIndex = 13;
    face[7].vert[3].vertIndex = 12;
    for(i = 0; i<face[7].nVerts ; i++)
        face[7].vert[i].colorIndex = 7;
    
    //Front Near Face
    face[8].nVerts = 4;
    face[8].vert = new VertexID[face[8].nVerts];
    face[8].vert[0].vertIndex = 1;
    face[8].vert[1].vertIndex = 9;
    face[8].vert[2].vertIndex = 13;
    face[8].vert[3].vertIndex = 17;
    for(i = 0; i<face[8].nVerts ; i++)
        face[8].vert[i].colorIndex = 8;
    
    //Front Far Face
    face[9].nVerts = 4;
    face[9].vert = new VertexID[face[9].nVerts];
    face[9].vert[0].vertIndex = 10;
    face[9].vert[1].vertIndex = 2;
    face[9].vert[2].vertIndex = 18;
    face[9].vert[3].vertIndex = 14;
    for(i = 0; i<face[9].nVerts ; i++)
        face[9].vert[i].colorIndex = 9;
    
    //Front Bottom Face
    face[10].nVerts = 4;
    face[10].vert = new VertexID[face[10].nVerts];
    face[10].vert[0].vertIndex = 17;
    face[10].vert[1].vertIndex = 18;
    face[10].vert[2].vertIndex = 6;
    face[10].vert[3].vertIndex = 5;
    for(i = 0; i<face[10].nVerts ; i++)
        face[10].vert[i].colorIndex = 10;
    
    //Behind Near Face
    face[11].nVerts = 4;
    face[11].vert = new VertexID[face[11].nVerts];
    face[11].vert[0].vertIndex = 8;
    face[11].vert[1].vertIndex = 0;
    face[11].vert[2].vertIndex = 16;
    face[11].vert[3].vertIndex = 12;
    for(i = 0; i<face[11].nVerts ; i++)
        face[11].vert[i].colorIndex = 11;
    
    //Behind Far Face
    face[12].nVerts = 4;
    face[12].vert = new VertexID[face[12].nVerts];
    face[12].vert[0].vertIndex = 3;
    face[12].vert[1].vertIndex = 11;
    face[12].vert[2].vertIndex = 15;
    face[12].vert[3].vertIndex = 19;
    for(i = 0; i<face[12].nVerts ; i++)
       face[12].vert[i].colorIndex = 12;
    
    //Behind Bottom Face
    face[13].nVerts = 4;
    face[13].vert = new VertexID[face[13].nVerts];
    face[13].vert[0].vertIndex = 19;
    face[13].vert[1].vertIndex = 16;
    face[13].vert[2].vertIndex = 4;
    face[13].vert[3].vertIndex = 7;
    for(i = 0; i<face[13].nVerts ; i++)
       face[13].vert[i].colorIndex = 13;
        
}

void Mesh::CreateBoxWithLegde(float fSizeX, float fSizeY, float fSizeZ, float zTCleft, float zBCleft, float hCleft){
    
    int i;

    numVerts = 16;
    pt = new Point3[numVerts];
    pt[0].set(-fSizeX, fSizeY - hCleft, fSizeZ);
    pt[1].set( fSizeX, fSizeY - hCleft, fSizeZ);
    pt[2].set( fSizeX, fSizeY - hCleft, -fSizeZ);
    pt[3].set(-fSizeX, fSizeY - hCleft, -fSizeZ);
    pt[4].set(-fSizeX, -fSizeY, fSizeZ);
    pt[5].set( fSizeX, -fSizeY, fSizeZ);
    pt[6].set( fSizeX, -fSizeY, -fSizeZ);
    pt[7].set(-fSizeX, -fSizeY, -fSizeZ);
    pt[8].set(-fSizeX, fSizeY, zTCleft);
    pt[9].set( fSizeX, fSizeY, zTCleft);
    pt[10].set( fSizeX, fSizeY, -zTCleft);
    pt[11].set(-fSizeX, fSizeY, -zTCleft);
    pt[12].set(-fSizeX, fSizeY - hCleft, zBCleft);
    pt[13].set( fSizeX, fSizeY - hCleft, zBCleft);
    pt[14].set( fSizeX, fSizeY - hCleft, -zBCleft);
    pt[15].set(-fSizeX, fSizeY - hCleft, -zBCleft);

    numFaces= 12;
    face = new Face[numFaces];

    //Near face
    face[0].nVerts = 4;
    face[0].vert = new VertexID[face[0].nVerts];
    face[0].vert[0].vertIndex = 0;
    face[0].vert[1].vertIndex = 1;
    face[0].vert[2].vertIndex = 5;
    face[0].vert[3].vertIndex = 4;
    for(i = 0; i<face[0].nVerts ; i++)
        face[0].vert[i].colorIndex = 0;
    
    //Far face
    face[1].nVerts = 4;
    face[1].vert = new VertexID[face[1].nVerts];
    face[1].vert[0].vertIndex = 3;
    face[1].vert[1].vertIndex = 2;
    face[1].vert[2].vertIndex = 6;
    face[1].vert[3].vertIndex = 7;
    for(i = 0; i<face[1].nVerts ; i++)
        face[1].vert[i].colorIndex = 1;

    //Bottom face
    face[2].nVerts = 4;
    face[2].vert = new VertexID[face[2].nVerts];
    face[2].vert[0].vertIndex = 4;
    face[2].vert[1].vertIndex = 5;
    face[2].vert[2].vertIndex = 6;
    face[2].vert[3].vertIndex = 7;
    for(i = 0; i<face[2].nVerts ; i++)
        face[2].vert[i].colorIndex = 2;

    //Top Near Side face
    face[3].nVerts = 4;
    face[3].vert = new VertexID[face[3].nVerts];
    face[3].vert[0].vertIndex = 0;
    face[3].vert[1].vertIndex = 1;
    face[3].vert[2].vertIndex = 13;
    face[3].vert[3].vertIndex = 12;
    for(i = 0; i<face[3].nVerts ; i++)
        face[3].vert[i].colorIndex = 3;

    //Top Far Side face
    face[4].nVerts = 4;
    face[4].vert = new VertexID[face[4].nVerts];
    face[4].vert[0].vertIndex = 15;
    face[4].vert[1].vertIndex = 14;
    face[4].vert[2].vertIndex = 2;
    face[4].vert[3].vertIndex = 3;
    for(i = 0; i<face[4].nVerts ; i++)
        face[4].vert[i].colorIndex = 4;

    //Side Near Face
    face[5].nVerts = 4;
    face[5].vert = new VertexID[face[5].nVerts];
    face[5].vert[0].vertIndex = 8;
    face[5].vert[1].vertIndex = 9;
    face[5].vert[2].vertIndex = 13;
    face[5].vert[3].vertIndex = 12;
    for(i = 0; i<face[5].nVerts ; i++)
        face[5].vert[i].colorIndex = 5;
    
    //In Far Face
    face[6].nVerts = 4;
    face[6].vert = new VertexID[face[6].nVerts];
    face[6].vert[0].vertIndex = 11;
    face[6].vert[1].vertIndex = 10;
    face[6].vert[2].vertIndex = 14;
    face[6].vert[3].vertIndex = 15;
    for(i = 0; i<face[6].nVerts ; i++)
        face[6].vert[i].colorIndex = 6;
    
    //Top Mid Face
    face[7].nVerts = 4;
    face[7].vert = new VertexID[face[7].nVerts];
    face[7].vert[0].vertIndex = 8;
    face[7].vert[1].vertIndex = 9;
    face[7].vert[2].vertIndex = 10;
    face[7].vert[3].vertIndex = 11;
    for(i = 0; i<face[7].nVerts ; i++)
        face[7].vert[i].colorIndex = 7;
    
    //Front Top Face
    face[8].nVerts = 4;
    face[8].vert = new VertexID[face[8].nVerts];
    face[8].vert[0].vertIndex = 9;
    face[8].vert[1].vertIndex = 10;
    face[8].vert[2].vertIndex = 14;
    face[8].vert[3].vertIndex = 13;
    for(i = 0; i<face[8].nVerts ; i++)
        face[8].vert[i].colorIndex = 8;
    
    //Behind Top Face
    face[9].nVerts = 4;
    face[9].vert = new VertexID[face[9].nVerts];
    face[9].vert[0].vertIndex = 8;
    face[9].vert[1].vertIndex = 12;
    face[9].vert[2].vertIndex = 15;
    face[9].vert[3].vertIndex = 11;
    for(i = 0; i<face[9].nVerts ; i++)
        face[9].vert[i].colorIndex = 9;
    
    //Front Bottom Face
    face[10].nVerts = 4;
    face[10].vert = new VertexID[face[10].nVerts];
    face[10].vert[0].vertIndex = 5;
    face[10].vert[1].vertIndex = 6;
    face[10].vert[2].vertIndex = 2;
    face[10].vert[3].vertIndex = 1;
    for(i = 0; i<face[10].nVerts ; i++)
        face[10].vert[i].colorIndex = 10;
    
    //Behind Bottom Face
    face[11].nVerts = 4;
    face[11].vert = new VertexID[face[11].nVerts];
    face[11].vert[0].vertIndex = 0;
    face[11].vert[1].vertIndex = 3;
    face[11].vert[2].vertIndex = 7;
    face[11].vert[3].vertIndex = 4;
    for(i = 0; i<face[11].nVerts ; i++)
        face[11].vert[i].colorIndex = 11;
    
}

void Mesh::CreateCylinderColapCuboid(int nSegment, float fHeight,float fLong, float fRadius)
{
    numVerts=nSegment*4;
    pt = new Point3[numVerts];

    int      i;
    int      idx;
    float    fAngle = 2*PI/(nSegment*4);
    float    x, y, z;

    for(i = 0; i<nSegment; i++){
        x = fRadius* cos(fAngle*i + 3*PI/4) + fLong;
        z = fRadius* sin(fAngle*i + 3*PI/4);
        y = fHeight/2;
        pt[i].set(x, y, z);
        
        y = -fHeight/2;
        pt[i + nSegment].set(x, y, z);
        
        x = fRadius* cos(fAngle*i + 7*PI/4) - fLong;
        z = fRadius* sin(fAngle*i + 7*PI/4);
        y = fHeight/2;
        pt[nSegment - 1 - i + nSegment * 2].set(x, y, z);
        
        y = -fHeight/2;
        pt[nSegment - 1 - i + nSegment * 3].set(x, y, z);
    }
    
    numFaces= nSegment*4 + 2;
    face = new Face[numFaces];

    idx = 0;
    for(i = 0; i<nSegment-1; i++){
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = i;
        face[idx].vert[1].vertIndex = i + 1;
        face[idx].vert[2].vertIndex = i + 1 + nSegment;
        face[idx].vert[3].vertIndex = i + nSegment;
        idx++;
    }

    for(i = 0; i<nSegment-1; i++){
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = i;
        face[idx].vert[1].vertIndex = i + 1;
        face[idx].vert[2].vertIndex = i + 1 + 2 * nSegment;
        face[idx].vert[3].vertIndex = i + 2 * nSegment;
        idx++;
    }
    for(i = 0; i<nSegment-1; i++){
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = i + 2 * nSegment;
        face[idx].vert[1].vertIndex = i + 1 + 2 * nSegment;
        face[idx].vert[2].vertIndex = i + 1 + 3 * nSegment;
        face[idx].vert[3].vertIndex = i + 3 * nSegment;
        idx++;
    }

    for(i = 0; i<nSegment-1; i++){
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = i + nSegment;
        face[idx].vert[1].vertIndex = i + 1 + nSegment;
        face[idx].vert[2].vertIndex = i + 1 + 3 * nSegment;
        face[idx].vert[3].vertIndex = i + 3 * nSegment;
        idx++;
    }
    
    face[idx].nVerts = 4;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = 0;
    face[idx].vert[1].vertIndex = 2 * nSegment;
    face[idx].vert[2].vertIndex = 3 * nSegment;
    face[idx].vert[3].vertIndex = nSegment;
    idx++;
    
    face[idx].nVerts = 4;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = nSegment - 1;
    face[idx].vert[1].vertIndex = 3 * nSegment - 1;
    face[idx].vert[2].vertIndex = 4 * nSegment - 1;
    face[idx].vert[3].vertIndex = 2 * nSegment - 1;

}

void Mesh::CreateDoubleSemicircle(int nSegment, float fHeight, float fRadius1, float fRadius2, float fDistance)
{
    
    float fDeltaAngle = acos((fRadius2-fRadius1)/fDistance);
    numVerts=nSegment*4 + 4;
    pt = new Point3[numVerts];

    int      i;
    int      idx;
    float    fAngle1 = 2*fDeltaAngle/(nSegment-1);
    float    fAngle1St = PI - fDeltaAngle;
    float    fAngle2St = - PI + fDeltaAngle;
    float    fAngle2 = 2*fAngle1St/(nSegment-1);
    float    x, y, z;

    for(i = 0; i<nSegment; i++){
        x = fRadius1* cos(fAngle1St + fAngle1*i);
        z = fRadius1* sin(fAngle1St + fAngle1*i);
        y = fHeight/2;
        pt[i].set(x, y, z);
        
        y = -fHeight/2;
        pt[i + nSegment * 2].set(x, y, z);
        
        x = fRadius2* cos(fAngle2St + fAngle2*i) + fDistance;
        z = fRadius2* sin(fAngle2St + fAngle2*i);
        y = fHeight/2;
        pt[i + nSegment].set(x, y, z);
        
        y = -fHeight/2;
        pt[i + nSegment * 3].set(x, y, z);
    }
    numFaces= nSegment*2 + 4;
    face = new Face[numFaces];

    idx = 0;
    for(i = 0; i<nSegment - 1; i++){
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = i;
        face[idx].vert[1].vertIndex = i + 1;
        face[idx].vert[2].vertIndex = i + 1 + 2 * nSegment;
        face[idx].vert[3].vertIndex = i + 2 * nSegment;
        idx++;
    }
    for(i = 0; i<nSegment - 1; i++){
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = i + nSegment;
        face[idx].vert[1].vertIndex = i + nSegment +  1;
        face[idx].vert[2].vertIndex = i + 1 + 3 * nSegment;
        face[idx].vert[3].vertIndex = i + 3 * nSegment;
        idx++;
    }
    face[idx].nVerts = 4;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = 0;
    face[idx].vert[1].vertIndex = nSegment * 2 - 1;
    face[idx].vert[2].vertIndex = nSegment * 4 - 1;
    face[idx].vert[3].vertIndex = nSegment * 2;
    idx++;
    
    face[idx].nVerts = 4;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = nSegment - 1;
    face[idx].vert[1].vertIndex = nSegment;
    face[idx].vert[2].vertIndex = 3 * nSegment;
    face[idx].vert[3].vertIndex = 3 * nSegment - 1;
    idx++;
    
    face[idx].nVerts = 2 * nSegment;
    face[idx].vert = new VertexID[face[idx].nVerts];
    for(i = 0; i< 2 * nSegment; i++){
        face[idx].vert[i].vertIndex = i;
    }
    idx++;
    
    face[idx].nVerts = 2 * nSegment;
    face[idx].vert = new VertexID[face[idx].nVerts];
    for(i = 0; i< 2 * nSegment; i++){
        face[idx].vert[i + 2 * nSegment].vertIndex = i;
    }
    idx++;
    
}

void Mesh::CreateBoxConnectCylinder(int nSegment, float fHeight, float fLong, float fRadiusIn, float fRadiusOut)
{
    numVerts=nSegment*12;
    pt = new Point3[numVerts];

    int      i;
    int      idx;
    float    fAngle = 2*PI/(nSegment*4);
    float    x, y, z;

    for(i = 0; i<nSegment; i++){
        x = fRadiusOut* cos(fAngle*i + 3*PI/4) + fLong;
        z = fRadiusOut* sin(fAngle*i + 3*PI/4);
        y = fHeight/4;
        pt[i].set(x, y, z);
        
        y = -fHeight/4;
        pt[i + nSegment].set(x, y, z);
        
        x = fRadiusOut* cos(fAngle*i + 7*PI/4);
        z = fRadiusOut* sin(fAngle*i + 7*PI/4);
        y = fHeight/4;
        pt[nSegment - 1 - i + nSegment * 2].set(x, y, z);
        
        y = -fHeight/4;
        pt[nSegment - 1 - i + nSegment * 3].set(x, y, z);
    }
    
    fAngle = 2*PI/nSegment;
    
    for(i = 0; i<nSegment; i++){
        x = fRadiusIn* cos(fAngle*i) + fLong;
        z = fRadiusIn* sin(fAngle*i);
        y = fHeight/2;
        pt[i + nSegment * 4].set(x, y, z);
        
        y = -fHeight/2;
        pt[i + nSegment * 5].set(x, y, z);
        
        x = fRadiusOut* cos(fAngle*i) + fLong;
        z = fRadiusOut* sin(fAngle*i);
        y = fHeight/2;
        pt[i + nSegment * 6].set(x, y, z);
        
        y = -fHeight/2;
        pt[i + nSegment * 7].set(x, y, z);
    }
    
    for(i = 0; i<nSegment; i++){
        x = fRadiusIn* cos(fAngle*i);
        z = fRadiusIn* sin(fAngle*i);
        y = fHeight/2;
        pt[i + nSegment * 8].set(x, y, z);
        
        y = -fHeight/2;
        pt[i + nSegment * 9].set(x, y, z);
        
        x = fRadiusOut* cos(fAngle*i) ;
        z = fRadiusOut* sin(fAngle*i);
        y = fHeight/2;
        pt[i + nSegment * 10].set(x, y, z);
        
        y = -fHeight/2;
        pt[i + nSegment * 11].set(x, y, z);
    }
    
    numFaces= nSegment*10;
    face = new Face[numFaces];

    idx = 0;

    for(i = 0; i<nSegment-1; i++){
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = i;
        face[idx].vert[1].vertIndex = i + 1;
        face[idx].vert[2].vertIndex = i + 1 + 2 * nSegment;
        face[idx].vert[3].vertIndex = i + 2 * nSegment;
        idx++;
    }

    for(i = 0; i<nSegment-1; i++){
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = i + nSegment;
        face[idx].vert[1].vertIndex = i + 1 + nSegment;
        face[idx].vert[2].vertIndex = i + 1 + 3 * nSegment;
        face[idx].vert[3].vertIndex = i + 3 * nSegment;
        idx++;
    }
    
    face[idx].nVerts = 4;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = 0;
    face[idx].vert[1].vertIndex = 2 * nSegment;
    face[idx].vert[2].vertIndex = 3 * nSegment;
    face[idx].vert[3].vertIndex = nSegment;
    idx++;
    
    face[idx].nVerts = 4;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = nSegment - 1;
    face[idx].vert[1].vertIndex = 3 * nSegment - 1;
    face[idx].vert[2].vertIndex = 4 * nSegment - 1;
    face[idx].vert[3].vertIndex = 2 * nSegment - 1;
    idx++;
    

    for(i = 0; i<nSegment; i++){
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = i + 4 * nSegment;
        face[idx].vert[3].vertIndex = i + 6 * nSegment;
        if(i < nSegment - 1)
        {
            face[idx].vert[1].vertIndex = i + 1 + 4 * nSegment;
            face[idx].vert[2].vertIndex = i + 1 + 6 * nSegment;
        }
        else
        {
            face[idx].vert[1].vertIndex = 4 * nSegment;
            face[idx].vert[2].vertIndex = 6 * nSegment;
        }
        idx++;
    }

    for(i = 0; i<nSegment; i++){
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = i + 4 * nSegment ;
        face[idx].vert[3].vertIndex = i + 5 * nSegment;
        if(i < nSegment - 1)
        {
            face[idx].vert[1].vertIndex = i + 1 + 4 * nSegment;
            face[idx].vert[2].vertIndex = i + 1 + 5 * nSegment;
        }
        else
        {
            face[idx].vert[1].vertIndex = 4 * nSegment;
            face[idx].vert[2].vertIndex = 5 * nSegment;
        }
        idx++;
    }

    for(i = 0; i<nSegment; i++){
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = i + 6 * nSegment;
        face[idx].vert[3].vertIndex = i + 7 * nSegment;
        if(i < nSegment - 1)
        {
            face[idx].vert[1].vertIndex = i + 1 + 6 * nSegment;
            face[idx].vert[2].vertIndex = i + 1 + 7 * nSegment;
        }
        else
        {
            face[idx].vert[1].vertIndex = 0 + 6 * nSegment;
            face[idx].vert[2].vertIndex = 0 + 7 * nSegment;
        }
        idx++;
    }

    for(i = 0; i<nSegment; i++){
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = i + 5 * nSegment;
        face[idx].vert[3].vertIndex = i + 7 * nSegment;
        if(i < nSegment - 1)
        {
            face[idx].vert[1].vertIndex = i + 1 + 5 *nSegment;
            face[idx].vert[2].vertIndex = i + 1 + 7 * nSegment;
        }
        else
        {
            face[idx].vert[1].vertIndex = 0 + 5 * nSegment;
            face[idx].vert[2].vertIndex = 0 + 7 * nSegment;
        }
        idx++;
    }
    for(i = 0; i<nSegment; i++){
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = i + 8 * nSegment;
        face[idx].vert[3].vertIndex = i + 10 * nSegment;
        if(i < nSegment - 1)
        {
            face[idx].vert[1].vertIndex = i + 1 + 8 * nSegment;
            face[idx].vert[2].vertIndex = i + 1 + 10 * nSegment;
        }
        else
        {
            face[idx].vert[1].vertIndex = 8 * nSegment;
            face[idx].vert[2].vertIndex = 10 * nSegment;
        }
        idx++;
    }

    for(i = 0; i<nSegment; i++){
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = i + 8 * nSegment ;
        face[idx].vert[3].vertIndex = i + 9 * nSegment;
        if(i < nSegment - 1)
        {
            face[idx].vert[1].vertIndex = i + 1 + 8 * nSegment;
            face[idx].vert[2].vertIndex = i + 1 + 9 * nSegment;
        }
        else
        {
            face[idx].vert[1].vertIndex = 8 * nSegment;
            face[idx].vert[2].vertIndex = 9 * nSegment;
        }
        idx++;
    }

    for(i = 0; i<nSegment; i++){
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = i + 10 * nSegment;
        face[idx].vert[3].vertIndex = i + 11 * nSegment;
        if(i < nSegment - 1)
        {
            face[idx].vert[1].vertIndex = i + 1 + 10 * nSegment;
            face[idx].vert[2].vertIndex = i + 1 + 11 * nSegment;
        }
        else
        {
            face[idx].vert[1].vertIndex = 0 + 10 * nSegment;
            face[idx].vert[2].vertIndex = 0 + 11 * nSegment;
        }
        idx++;
    }

    for(i = 0; i<nSegment; i++){
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = i + 9 * nSegment;
        face[idx].vert[3].vertIndex = i + 11 * nSegment;
        if(i < nSegment - 1)
        {
            face[idx].vert[1].vertIndex = i + 1 + 9 *nSegment;
            face[idx].vert[2].vertIndex = i + 1 + 11 * nSegment;
        }
        else
        {
            face[idx].vert[1].vertIndex = 0 + 9 * nSegment;
            face[idx].vert[2].vertIndex = 0 + 11 * nSegment;
        }
    }
}

void Mesh::DrawWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;

			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawColor()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			int		ic = face[f].vert[v].colorIndex;
			
//			ic = f % COLORNUM;

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]); 
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::SetColor(int colorIdx){
    for (int f = 0; f < numFaces; f++)
    {
        for (int v = 0; v < face[f].nVerts; v++)
        {
            face[f].vert[v].colorIndex = colorIdx;
        }
    }
}
