//  Le Ba Quan
//  1712817
//  main.cpp
//  Assignment
//
//  Created by Le Quan on 6/24/20.
//  Copyright © 2020 Le Quan. All rights reserved.

#define GL_SILENCE_DEPRECATION
#define PI            3.14159265359
#define COLORNUM        16

#include <iostream>
#include "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/Headers/gl.h"
#include "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/GLUT.framework/Headers/glut.h"
#include <math.h>
//#include "supportClass.h"
//#include "Mesh.h"

//***********************************SupportClass********************************//

#if !defined (_SUPPORT_CLASS)
#define _SUPPORT_CLASS

class Point3
{
public:
    float x, y, z;
    void set(float dx, float dy, float dz)
                        { x = dx; y = dy; z = dz;}
    void set(Point3& p)
                        { x = p.x; y = p.y; z = p.z;}
    Point3() { x = y = z = 0;}
    Point3(float dx, float dy, float dz)
                        { x = dx; y = dy; z = dz;}

};
class Color3
{
public:
    float r, g, b;
    void set(float red, float green, float blue)
                        { r = red; g = green; b = blue;}
    void set(Color3& c)
                        { r = c.r; g = c.g; b = c.b;}
    Color3() { r = g = b = 0;}
    Color3(float red, float green, float blue)
                        { r = red; g = green; b = blue;}

};
class Point2
{
    public:
        Point2() { x = y = 0.0f; } // constructor 1
        Point2(float xx, float yy) { x = xx; y = yy; } // constructor 2
        void set(float xx, float yy) { x = xx; y = yy; }
        float getX() { return x;}
        float getY(){return y;}
        void draw(){glBegin(GL_POINTS);
                                glVertex2f((GLfloat)x, (GLfloat)y);
                            glEnd();
                        }
    private:
        float     x, y;
};
class IntRect
{
     public:
        IntRect() { l = 0; r = 100; b = 0; t = 100; } // constructor
        IntRect( int left, int right, int bottom, int top)
            { l = left; r = right; b = bottom; t = top; }
        void set( int left, int right, int bottom, int top)
            { l = left; r = right; b = bottom; t = top; }
        void draw(){
            glRecti(l, b, r, t);
            glFlush();
        } // draw this rectangle using OpenGL
        int  getWidth(){return (r-l);}
        int  getHeight() { return (t-b);}
     private:
        int    l, r, b, t;
};


class RealRect
{
     public:
        RealRect() { l = 0; r = 100; b = 0; t = 100; } // constructor
        RealRect( float left, float right, float bottom, float top)
            { l = left; r = right; b = bottom; t = top; }
        void set( float left, float right, float bottom, float top)
            { l = left; r = right; b = bottom; t = top; }
        float  getWidth(){return (r-l);}
        float  getHeight() { return (t-b);}
    void draw(){
                            glRectf(l, b, r, t);
                            glFlush();
                        };// draw this rectangle using OpenGL
     private:
        float    l, r, b, t;
};

class Vector3
{
public:
    float    x, y, z;
    void set(float dx, float dy, float dz)
                        { x = dx; y = dy; z = dz;}
    void set(Vector3& v)
                        { x = v.x; y = v.y; z = v.z;}
    void flip()
                        { x = -x; y = -y; z = -z;}
    void normalize();
    Vector3() { x = y = z = 0;}
    Vector3(float dx, float dy, float dz)
                        { x = dx; y = dy; z = dz;}
    Vector3(Vector3& v)
                        { x = v.x; y = v.y; z = v.z;}
    Vector3 cross(Vector3 b);
    float dot(Vector3 b);
};
#endif

Vector3 Vector3::cross(Vector3 b)
{
    Vector3 c(y*b.z-z*b.y, z*b.x-x*b.z, x*b.y-y*b.x);
    return c;
}
float Vector3::dot(Vector3 b)
{
    return x*b.x + y*b.y + z*b.z;
}
void Vector3::normalize()
{
    float temp = sqrt(x*x + y*y + z*z);
    x = x/temp;
    y = y/temp;
    z = z/temp;
}
//*******************************************Mesh.cpp*****************************//

class VertexID
{
public:
    int        vertIndex;
    int        colorIndex;
};

class Face
{
public:
    int        nVerts;
    VertexID*    vert;
    Vector3     facenorm;
    
    Face()
    {
        nVerts    = 0;
        vert    = NULL;
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
    int        numVerts;
    Point3*        pt;
    
    int        numFaces;
    Face*        face;
    
    float   slideX, slideY, slideZ;
    float   rotateX, rotateY, rotateZ;
    float   scaleX, scaleY, scaleZ;
    
public:
    Mesh()
    {
        numVerts    = 0;
        pt            = NULL;
        numFaces    = 0;
        face        = NULL;
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
    void CalculateFacesNorm();
    void DrawWireframe();
    void DrawColor();
    void Draw();
    void SetColor(int colorIdx);

    void CreateTetrahedron();
    void CreateCube(float    fSize);
    void CreateCuboid(float fSizeX, float fSizeY, float fSizeZ);
    void CreateCylinder(int nSegment, float fHeight, float fRadius);
    void CreateCylinderWithHole(int nSegment, float fHeight, float fRadiusIn, float fRadiusOut);
    void CreateBoxWithCleft(float fSizeX, float fSizeY, float fSizeZ, float zTCleft, float zBCleft, float hCleft);
    void CreateBoxWithLegde(float fSizeX, float fSizeY, float fSizeZ, float zTCleft, float zBCleft, float hCleft);
    void CreateCylinderColapCuboid(int nSegment, float fHeight,float fLong, float fRadius);
    void CreateDoubleSemicircle(int nSegment, float fHeight, float fRadius1, float fRadius2, float fDistance);
    void CreateBoxConnectCylinder(int nSegment, float fHeight, float fLong, float fRadiusIn, float fRadiusOut);
};



GLfloat    ColorArr[COLORNUM][4] = {{1.0, 0.0, 0.0, 1.0}, {0.0, 1.0, 0.0, 1.0}, {0.0,  0.0, 1.0, 1.0}, {1.0, 1.0,  0.0, 1.0}, {1.0, 0.0, 1.0, 1.0},{ 0.0, 1.0, 1.0, 1.0}, {0.25, 0.25, 0.25, 1.0}, {0.5, 0.5, 0.5, 1.0}, { 0.9,  0.9, 0.9, 1.0}, {1.0, 0.5,  0.5, 1.0}, { 0.5, 1.0, 0.5, 1.0}, { 0.5, 0.5, 1.0, 1.0}, {0.0, 0.0, 0.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, {0.5, 0.18, 0.12, 1.0}, {0.83, 0.6, 0.28, 1.0}};





void Mesh::CreateCube(float    fSize)
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
    CalculateFacesNorm();
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
    CalculateFacesNorm();
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
    CalculateFacesNorm();
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
    CalculateFacesNorm();

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
    CalculateFacesNorm();
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
    face[0].vert[1].vertIndex = 4;
    face[0].vert[2].vertIndex = 5;
    face[0].vert[3].vertIndex = 1;
    for(i = 0; i<face[0].nVerts ; i++)
        face[0].vert[i].colorIndex = 0;
    
    //Far face
    face[1].nVerts = 4;
    face[1].vert = new VertexID[face[1].nVerts];
    face[1].vert[0].vertIndex = 2;
    face[1].vert[1].vertIndex = 6;
    face[1].vert[2].vertIndex = 7;
    face[1].vert[3].vertIndex = 3;
    for(i = 0; i<face[1].nVerts ; i++)
        face[1].vert[i].colorIndex = 1;

    //Bottom face
    face[2].nVerts = 4;
    face[2].vert = new VertexID[face[2].nVerts];
    face[2].vert[0].vertIndex = 5;
    face[2].vert[1].vertIndex = 4;
    face[2].vert[2].vertIndex = 7;
    face[2].vert[3].vertIndex = 6;
    for(i = 0; i<face[2].nVerts ; i++)
        face[2].vert[i].colorIndex = 2;

    //Top Near Out face
    face[3].nVerts = 4;
    face[3].vert = new VertexID[face[3].nVerts];
    face[3].vert[0].vertIndex = 8;
    face[3].vert[1].vertIndex = 0;
    face[3].vert[2].vertIndex = 1;
    face[3].vert[3].vertIndex = 9;
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
    face[5].vert[1].vertIndex = 13;
    face[5].vert[2].vertIndex = 12;
    face[5].vert[3].vertIndex = 8;
    for(i = 0; i<face[5].nVerts ; i++)
        face[5].vert[i].colorIndex = 5;
    
    //In Far Face
    face[6].nVerts = 4;
    face[6].vert = new VertexID[face[6].nVerts];
    face[6].vert[0].vertIndex = 11;
    face[6].vert[1].vertIndex = 15;
    face[6].vert[2].vertIndex = 14;
    face[6].vert[3].vertIndex = 10;
    for(i = 0; i<face[6].nVerts ; i++)
        face[6].vert[i].colorIndex = 6;
    
    //In Bottom Face
    face[7].nVerts = 4;
    face[7].vert = new VertexID[face[7].nVerts];
    face[7].vert[0].vertIndex = 12;
    face[7].vert[1].vertIndex = 13;
    face[7].vert[2].vertIndex = 14;
    face[7].vert[3].vertIndex = 15;
    for(i = 0; i<face[7].nVerts ; i++)
        face[7].vert[i].colorIndex = 7;
    
    //Front Near Face
    face[8].nVerts = 4;
    face[8].vert = new VertexID[face[8].nVerts];
    face[8].vert[0].vertIndex = 1;
    face[8].vert[1].vertIndex = 17;
    face[8].vert[2].vertIndex = 13;
    face[8].vert[3].vertIndex = 9;
    for(i = 0; i<face[8].nVerts ; i++)
        face[8].vert[i].colorIndex = 8;
    
    //Front Far Face
    face[9].nVerts = 4;
    face[9].vert = new VertexID[face[9].nVerts];
    face[9].vert[0].vertIndex = 2;
    face[9].vert[1].vertIndex = 10;
    face[9].vert[2].vertIndex = 14;
    face[9].vert[3].vertIndex = 18;
    for(i = 0; i<face[9].nVerts ; i++)
        face[9].vert[i].colorIndex = 9;
    
    //Front Bottom Face
    face[10].nVerts = 4;
    face[10].vert = new VertexID[face[10].nVerts];
    face[10].vert[0].vertIndex = 17;
    face[10].vert[1].vertIndex = 5;
    face[10].vert[2].vertIndex = 6;
    face[10].vert[3].vertIndex = 18;
    for(i = 0; i<face[10].nVerts ; i++)
        face[10].vert[i].colorIndex = 10;
    
    //Behind Near Face
    face[11].nVerts = 4;
    face[11].vert = new VertexID[face[11].nVerts];
    face[11].vert[0].vertIndex = 8;
    face[11].vert[1].vertIndex = 12;
    face[11].vert[2].vertIndex = 16;
    face[11].vert[3].vertIndex = 0;
    for(i = 0; i<face[11].nVerts ; i++)
        face[11].vert[i].colorIndex = 11;
    
    //Behind Far Face
    face[12].nVerts = 4;
    face[12].vert = new VertexID[face[12].nVerts];
    face[12].vert[0].vertIndex = 3;
    face[12].vert[1].vertIndex = 19;
    face[12].vert[2].vertIndex = 15;
    face[12].vert[3].vertIndex = 11;
    for(i = 0; i<face[12].nVerts ; i++)
       face[12].vert[i].colorIndex = 12;
    
    //Behind Bottom Face
    face[13].nVerts = 4;
    face[13].vert = new VertexID[face[13].nVerts];
    face[13].vert[0].vertIndex = 19;
    face[13].vert[1].vertIndex = 7;
    face[13].vert[2].vertIndex = 4;
    face[13].vert[3].vertIndex = 16;
    for(i = 0; i<face[13].nVerts ; i++)
       face[13].vert[i].colorIndex = 13;
    CalculateFacesNorm();

}

void Mesh::CreateBoxWithLegde(float fSizeX, float fSizeY, float fSizeZ, float zTCleft, float zBCleft, float hCleft){
    
    int i;

    numVerts = 16;
    pt = new Point3[numVerts];
    pt[0].set(-fSizeX, -fSizeY + hCleft, fSizeZ);
    pt[1].set( fSizeX, -fSizeY + hCleft, fSizeZ);
    pt[2].set( fSizeX, -fSizeY + hCleft, -fSizeZ);
    pt[3].set(-fSizeX, -fSizeY + hCleft, -fSizeZ);
    pt[4].set(-fSizeX, fSizeY, fSizeZ);
    pt[5].set( fSizeX, fSizeY, fSizeZ);
    pt[6].set( fSizeX, fSizeY, -fSizeZ);
    pt[7].set(-fSizeX, fSizeY, -fSizeZ);
    pt[8].set(-fSizeX, -fSizeY, zTCleft);
    pt[9].set( fSizeX, -fSizeY, zTCleft);
    pt[10].set( fSizeX, -fSizeY, -zTCleft);
    pt[11].set(-fSizeX, -fSizeY, -zTCleft);
    pt[12].set(-fSizeX, -fSizeY + hCleft, zBCleft);
    pt[13].set( fSizeX, -fSizeY + hCleft, zBCleft);
    pt[14].set( fSizeX, -fSizeY + hCleft, -zBCleft);
    pt[15].set(-fSizeX, -fSizeY + hCleft, -zBCleft);

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
    face[1].vert[1].vertIndex = 7;
    face[1].vert[2].vertIndex = 6;
    face[1].vert[3].vertIndex = 2;
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
    face[3].vert[1].vertIndex = 12;
    face[3].vert[2].vertIndex = 13;
    face[3].vert[3].vertIndex = 1;
    for(i = 0; i<face[3].nVerts ; i++)
        face[3].vert[i].colorIndex = 3;

    //Top Far Side face
    face[4].nVerts = 4;
    face[4].vert = new VertexID[face[4].nVerts];
    face[4].vert[0].vertIndex = 15;
    face[4].vert[1].vertIndex = 3;
    face[4].vert[2].vertIndex = 2;
    face[4].vert[3].vertIndex = 14;
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
    face[6].vert[1].vertIndex = 15;
    face[6].vert[2].vertIndex = 14;
    face[6].vert[3].vertIndex = 10;
    for(i = 0; i<face[6].nVerts ; i++)
        face[6].vert[i].colorIndex = 6;
    
    //Top Mid Face
    face[7].nVerts = 4;
    face[7].vert = new VertexID[face[7].nVerts];
    face[7].vert[0].vertIndex = 8;
    face[7].vert[1].vertIndex = 11;
    face[7].vert[2].vertIndex = 10;
    face[7].vert[3].vertIndex = 9;
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
    face[10].vert[1].vertIndex = 1;
    face[10].vert[2].vertIndex = 2;
    face[10].vert[3].vertIndex = 6;
    for(i = 0; i<face[10].nVerts ; i++)
        face[10].vert[i].colorIndex = 10;
    
    //Behind Bottom Face
    face[11].nVerts = 4;
    face[11].vert = new VertexID[face[11].nVerts];
    face[11].vert[0].vertIndex = 0;
    face[11].vert[1].vertIndex = 4;
    face[11].vert[2].vertIndex = 7;
    face[11].vert[3].vertIndex = 3;
    for(i = 0; i<face[11].nVerts ; i++)
        face[11].vert[i].colorIndex = 11;
    CalculateFacesNorm();
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
    CalculateFacesNorm();

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
    CalculateFacesNorm();
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
        face[idx].vert[3].vertIndex = i + 1 + nSegment;
        face[idx].vert[2].vertIndex = i + 1 + 3 * nSegment;
        face[idx].vert[1].vertIndex = i + 3 * nSegment;
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
    face[idx].vert[3].vertIndex = 3 * nSegment - 1;
    face[idx].vert[2].vertIndex = 4 * nSegment - 1;
    face[idx].vert[1].vertIndex = 2 * nSegment - 1;
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
        face[idx].vert[1].vertIndex = i + 5 * nSegment;
        if(i < nSegment - 1)
        {
            face[idx].vert[3].vertIndex = i + 1 + 4 * nSegment;
            face[idx].vert[2].vertIndex = i + 1 + 5 * nSegment;
        }
        else
        {
            face[idx].vert[3].vertIndex = 4 * nSegment;
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
        face[idx].vert[1].vertIndex = i + 7 * nSegment;
        if(i < nSegment - 1)
        {
            face[idx].vert[3].vertIndex = i + 1 + 5 *nSegment;
            face[idx].vert[2].vertIndex = i + 1 + 7 * nSegment;
        }
        else
        {
            face[idx].vert[3].vertIndex = 0 + 5 * nSegment;
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
        face[idx].vert[1].vertIndex = i + 9 * nSegment;
        if(i < nSegment - 1)
        {
            face[idx].vert[3].vertIndex = i + 1 + 8 * nSegment;
            face[idx].vert[2].vertIndex = i + 1 + 9 * nSegment;
        }
        else
        {
            face[idx].vert[3].vertIndex = 8 * nSegment;
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
        face[idx].vert[1].vertIndex = i + 11 * nSegment;
        if(i < nSegment - 1)
        {
            face[idx].vert[3].vertIndex = i + 1 + 9 *nSegment;
            face[idx].vert[2].vertIndex = i + 1 + 11 * nSegment;
        }
        else
        {
            face[idx].vert[3].vertIndex = 0 + 9 * nSegment;
            face[idx].vert[2].vertIndex = 0 + 11 * nSegment;
        }
        idx++;
    }
    CalculateFacesNorm();
}

void Mesh::DrawWireframe()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    for (int f = 0; f < numFaces; f++)
    {
        glBegin(GL_POLYGON);
        for (int v = 0; v < face[f].nVerts; v++)
        {
            int        iv = face[f].vert[v].vertIndex;

            glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
        }
        glEnd();
    }
}

void Mesh::Draw() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    for (int f = 0; f < numFaces; f++){
        glBegin(GL_POLYGON);
        for (int v = 0; v < face[f].nVerts; v++)
        {
            int iv = face[f].vert[v].vertIndex;
            glNormal3f(face[f].facenorm.x, face[f].facenorm.y, face[f].facenorm.z);
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
            int        iv = face[f].vert[v].vertIndex;
            int        ic = face[f].vert[v].colorIndex;
            
//            ic = f % COLORNUM;

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

void Mesh::CalculateFacesNorm(){
    for (int i = 0; i < numFaces; i ++)
    {
        float mx = 0;
        float my = 0;
        float mz = 0;
        for (int j = 0; j < face[i].nVerts; j++){
            int p = face[i].vert[j].vertIndex;
            int pn;
            if (j == (face[i].nVerts - 1))
                pn = face[i].vert[0].vertIndex;
            else
                pn = face[i].vert[j+1].vertIndex;
            mx += (pt[p].y - pt[pn].y)*(pt[p].z + pt[pn].z);
            my += (pt[p].z - pt[pn].z)*(pt[p].x + pt[pn].x);
            mz += (pt[p].x - pt[pn].x)*(pt[p].y + pt[pn].y);
        }
        face[i].facenorm.set(mx, my, mz);
    }
}


//*******************************************Main.cpp*****************************//

using namespace std;

int      screenWidth = 1000;
int      screenHeight= 1000;

bool     bWireFrame = false;
bool     viewing = false;
bool     animation = false;
bool     maxMshelf = false;
bool     lightsource = true;

float    camera_angle = 30 ;
float    camera_height = 7;
float    camera_dis = 10;

float    camera_radius = sqrt(camera_dis*camera_dis+camera_height*camera_height);

float    central_radius = 2;

float    baseRadius = 0.6;
float    baseHeight = 0.2;
float    baseRotateStep = 5;

float    cylRadius = 0.3;
float    cylHeight = 1.0;
float    cylMaxScaleY = 2.0;
float    cylScaleStep = 0.05;

float    body1SizeX = 3;
float    body1SizeY = 0.1;
float    body1SizeZ = 1.2;

float    pshelfSizeX = 0.2;
float    pshelfSizeY = 0.12;
float    pshelfSizeZ = 0.2;

float    tzcleft = 0.05;
float    bzcleft = 0.1;
float    hcleft = 0.1;

float    mshelf1SizeX = 1;
float    mshelf1SizeY = 0.08;
float    mshelf1SizeZ = 0.2;

float    mshelf2SizeX = 0.8;
float    mshelf2SizeY = 0.24;
float    mshelf2SizeZ = 0.2;

float    mledge1SizeX = 0.3;
float    mledge1SizeY = 0.09;
float    mledge1SizeZ = 0.2;

float    mledge2SizeX = 0.3;
float    mledge2SizeY = 0.09;
float    mledge2SizeZ = 0.2;


float    cotRadius = 0.1;
float    cotHeight = 0.16;

float   crankHeight = cotHeight;
float   crankShortLenght = 3*pshelfSizeX;
float   crankRadiusIn = cotRadius;
float   crankRadiusOut = 0.15;

Mesh    base;
Mesh    cyl;
Mesh    body1;
Mesh    body2;
Mesh    pshelf;
Mesh    mshelf1;
Mesh    mshelf2;
Mesh    mledge1;
Mesh    mledge2;
Mesh    cotta1;
Mesh    cotta2;
Mesh    cotta3;
Mesh    cottaconnect;
Mesh    cottacentral;
Mesh    shortcrank;
Mesh    longcrank1;
Mesh    longcrank2;
Mesh    longcrank3;

void setupMaterial(float ambient[], float diffuse[], float specular[], float shiness)
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiness);
}


void drawAxis()
{
    glPushMatrix();

    glColor3f(0, 0, 1);
    glBegin(GL_LINES);
        glColor3f(1, 0, 0);
        glVertex3f(-4, 0, 0);//x
        glVertex3f(4, 0, 0);

        glColor3f(0, 1, 0);
        glVertex3f(0, 0, 0);//y
        glVertex3f(0, 4, 0);

        glColor3f(0, 0, 1);
        glVertex3f(0, 0, -4);//z
        glVertex3f(0, 0, 4);
    glEnd();

    glPopMatrix();
}
void myKeyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
    case '1':
        base.rotateY += baseRotateStep;
        if(base.rotateY > 360)
            base.rotateY -=360;
        break;
    case '2':
        base.rotateY -= baseRotateStep;
        if(base.rotateY < 0)
            base.rotateY +=360;
        break;
    case '3':
        shortcrank.rotateY += baseRotateStep;
        if(shortcrank.rotateY > 360)
            shortcrank.rotateY -=360;
        break;
    case '4':
        shortcrank.rotateY -= baseRotateStep;
        if(shortcrank.rotateY < 0)
            shortcrank.rotateY +=360;
        break;
    case '5':
        if (mledge1.slideX >= body1SizeX - mledge1SizeX)
            break;
        mledge1.slideX += 0.035;
        break;
    case '6':
        if (mledge1.slideX <= body1SizeX - 2*mshelf1SizeX + mledge1SizeX)
            break;
        mledge1.slideX -= 0.035;
        break;
    case '7':
        if(cyl.scaleY >= cylMaxScaleY)
            break;
        cyl.scaleY += cylScaleStep;
        cyl.slideY += cylHeight*cylScaleStep/2;
        break;
    case '8':
        if(cyl.scaleY <= 0)
            break;
        cyl.scaleY -= 0.05;
        cyl.slideY -= cylHeight*0.025;
        break;
    case '+':
        camera_dis += 0.1;
        break;
    case '-':
        camera_dis -= 0.1;
        break;
    case 'a':
    case 'A':
        animation = !animation;
        break;
    case 'd':
    case 'D':
        cout<<"pass"<<endl;
        lightsource = !lightsource;
        break;
    case 'v':
    case 'V':
        viewing = !viewing;
        break;
    case 'w':
    case 'W':
        bWireFrame = !bWireFrame;
        break;
    }
    glutPostRedisplay();
}

void autoAnimation(){
    if (animation) {
        shortcrank.rotateY += baseRotateStep;
        if(shortcrank.rotateY > 360)
            shortcrank.rotateY -=360;
        if(maxMshelf){
            mledge1.slideX += 0.035;
            if (mledge1.slideX >= body1SizeX - mledge1SizeX)
                maxMshelf = !maxMshelf;
        }
        else{
            mledge1.slideX -= 0.035;
            if (mledge1.slideX <= body1SizeX - 2*mshelf1SizeX + mledge1SizeX)
                maxMshelf = !maxMshelf;
        }
        glutPostRedisplay();
    }
}

void SpecialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        camera_angle += 3;
    break;
    case GLUT_KEY_RIGHT:
        camera_angle -= 3;
    break;
    case GLUT_KEY_UP:
        camera_height += 0.5;
        break;
    case GLUT_KEY_DOWN:
        camera_height -= 0.5;
        break;
    }
    glutPostRedisplay();
}

void drawBase()
{
    glPushMatrix();

        glTranslated(0, base.slideY, 0);
        glRotatef(base.rotateY, 0, 1, 0);

        if(bWireFrame)
            base.DrawWireframe();
        else
        {
            GLfloat drawAmbient[] = { 0.1745f, 0.01175f, 0.01175f, 0.55f };
            GLfloat drawDiffuse[] = {0.61424f, 0.04136f, 0.04136f, 0.55f };
            GLfloat drawSpecular[] = {0.727811f, 0.626959f, 0.626959f, 0.55f };
            GLfloat Shininess = 76.8f;
            setupMaterial(drawAmbient, drawDiffuse, drawSpecular, Shininess);
            base.Draw();
        }
    glPopMatrix();
}
void drawCyl()
{
    glPushMatrix();
        cyl.slideY = cylHeight*cyl.scaleY/2.0 + baseHeight;
        cyl.rotateY = base.rotateY;
        glTranslated(cyl.slideX, cyl.slideY, cyl.slideZ);
        glScalef(cyl.scaleX, cyl.scaleY, cyl.scaleZ);
        glRotatef(cyl.rotateY, 0, 1, 0);

        if(bWireFrame)
            cyl.DrawWireframe();
        else
        {
            float drawAmbient[] ={ 0.0f,0.05f,0.05f,1.0f };
            float drawDiffuse[] ={0.4f,0.5f,0.5f,1.0f };
            float drawSpecular[] ={0.04f,0.7f,0.7f,1.0f };
            float Shininess = 10.0f;
            setupMaterial(drawAmbient, drawDiffuse, drawSpecular, Shininess);
            cyl.Draw();
        }
    glPopMatrix();
}


void drawBody1()
{
    glPushMatrix();
        body1.slideY = cylHeight*cyl.scaleY+baseHeight+body1SizeY;
        body1.rotateY = cyl.rotateY;
        glRotatef(body1.rotateY, 0, 1, 0);
        glTranslated(0, body1.slideY , 0);
        glScalef(body1.scaleX, body1.scaleY, body1.scaleZ);

        if(bWireFrame)
            body1.DrawWireframe();
        else{
            float drawAmbient[] ={ 0.0f,0.05f,0.0f,1.0f };
            float drawDiffuse[] ={ 0.4f,0.5f,0.4f,1.0f};
            float drawSpecular[] ={0.04f,0.7f,0.04f,1.0f };
            float Shininess = 10.0f;
            setupMaterial(drawAmbient, drawDiffuse, drawSpecular, Shininess);
            body1.Draw();
        }
    glPopMatrix();
}

void drawPerShelf()
{
    glPushMatrix();
        pshelf.slideY = body1.slideY + body1SizeY + pshelfSizeY;
        pshelf.slideZ = - body1SizeZ + pshelfSizeZ;
        pshelf.rotateY = body1.rotateY;
        glRotatef(pshelf.rotateY, 0, 1, 0);
        glTranslated(pshelf.slideX, pshelf.slideY,pshelf.slideZ);
        glScalef(pshelf.scaleX, pshelf.scaleY, pshelf.scaleZ);

        if(bWireFrame)
            pshelf.DrawWireframe();
        else
        {
            GLfloat drawAmbient[4] = {0.05, 0.0, 0.0, 1.0};
            GLfloat drawDiffuse[3] = {0.5, 0.4, 0.4};
            GLfloat drawSpecular[3] = {0.7, 0.4, 0.4};
            GLfloat Shininess = 128*0.078125;
            setupMaterial(drawAmbient, drawDiffuse, drawSpecular, Shininess);
            pshelf.Draw();
        }
    glPopMatrix();
}

void drawMovShelf1()
{
    glPushMatrix();
        mshelf1.rotateY = base.rotateY;
        mshelf1.slideX = body1SizeX - mshelf1SizeX;
        mshelf1.slideY = body1.slideY + body1SizeY + mshelf1SizeY;
        mshelf1.slideZ = body1SizeZ - mshelf1SizeZ;
        glRotatef(mshelf1.rotateY, 0, 1, 0);
        glTranslated(mshelf1.slideX, mshelf1.slideY, mshelf1.slideZ);
        glScalef(mshelf1.scaleX, mshelf1.scaleY, mshelf1.scaleZ);

        if(bWireFrame)
            mshelf1.DrawWireframe();
        else
        {
            GLfloat drawAmbient[4] = {0.05, 0.0, 0.0, 1.0};
            GLfloat drawDiffuse[3] = {0.5, 0.4, 0.4};
            GLfloat drawSpecular[3] = {0.7, 0.4, 0.4};
            GLfloat Shininess = 128*0.078125;
            setupMaterial(drawAmbient, drawDiffuse , drawSpecular, Shininess);
            mshelf1.Draw();
        }
    glPopMatrix();
}

void drawMovShelf2()
{
    glPushMatrix();
        mshelf2.rotateY = base.rotateY;
        mshelf2.slideX = - body1SizeX + mshelf2SizeX;
        mshelf2.slideY = body1.slideY + body1SizeY
    + mshelf2SizeY;
        mshelf2.slideZ = body1SizeZ - mshelf2SizeZ;
    
        glRotatef(mshelf2.rotateY, 0, 1, 0);
        glTranslated(mshelf2.slideX, mshelf2.slideY, mshelf2.slideZ);
        glScalef(mshelf2.scaleX, mshelf2.scaleY, mshelf2.scaleZ);
    
        if(bWireFrame)
            mshelf2.DrawWireframe();
        else
        {
            GLfloat drawAmbient[4] = {0.05, 0.0, 0.0, 1.0};
            GLfloat drawDiffuse[3] = {0.5, 0.4, 0.4};
            GLfloat drawSpecular[3] = {0.7, 0.4, 0.4};
            GLfloat Shininess = 128*0.078125;
            setupMaterial(drawAmbient, drawDiffuse , drawSpecular, Shininess);
            mshelf2.Draw();
        }

    glPopMatrix();
}

void drawMovLegde1()
{
    glPushMatrix();
    
        mledge1.slideY =  mshelf1.slideY + mledge1SizeY + mshelf1SizeY - hcleft;
        glRotatef(base.rotateY, 0, 1, 0);
        glTranslated(mledge1.slideX, mledge1.slideY, mledge1.slideZ);
        glScalef(mledge1.scaleX, mledge1.scaleY, mledge1.scaleZ);

        if(bWireFrame)
            mledge1.DrawWireframe();
        else
        {
            GLfloat drawAmbient[] = { 0.24725f, 0.1995f, 0.0745f, 1.0f };
            GLfloat drawDiffuse[] = {0.75164f, 0.60648f, 0.22648f, 1.0f };
            GLfloat drawSpecular[] = {0.628281f, 0.555802f, 0.366065f, 1.0f};
            GLfloat Shininess = 51.2f;
            setupMaterial(drawAmbient, drawDiffuse, drawSpecular, Shininess);
            mledge1.Draw();
        }

    glPopMatrix();
}


void drawCot1()
{
    glPushMatrix();
        cotta1.slideY = pshelf.slideY + pshelfSizeY + cotHeight/2;
        glRotatef(base.rotateY, 0, 1, 0);
        glTranslated(cotta1.slideX, cotta1.slideY, cotta1.slideZ);
        glScalef(cotta1.scaleX, cotta1.scaleY, cotta1.scaleZ);
        
        if(bWireFrame)
            cotta1.DrawWireframe();
        else
        {
            GLfloat drawAmbient[] = { 0.0f,0.0f,0.0f,1.0f };
            GLfloat drawDiffuse[] = { 0.55f,0.55f,0.55f,1.0f};
            GLfloat drawSpecular[] = {0.70f,0.70f,0.70f,1.0f };
            GLfloat Shininess = 32.0f;
            setupMaterial(drawAmbient, drawDiffuse, drawSpecular, Shininess);
            cotta1.Draw();
        }
    glPopMatrix();
}

void drawShortCrank()
{
    glPushMatrix();
        shortcrank.slideX = cotta1.slideX;
        shortcrank.slideY = cotta1.slideY;
        shortcrank.slideZ = cotta1.slideZ;
        glRotatef(base.rotateY, 0, 1, 0);
        glTranslated(shortcrank.slideX, shortcrank.slideY, shortcrank.slideZ);
        glRotatef(shortcrank.rotateY, 0, 1, 0);
        glScalef(shortcrank.scaleX, shortcrank.scaleY, shortcrank.scaleZ);

        if(bWireFrame)
            shortcrank.DrawWireframe();
        else
        {
            GLfloat drawAmbient[] = { 0.24725f, 0.1995f, 0.0745f, 1.0f };
            GLfloat drawDiffuse[] = {0.75164f, 0.60648f, 0.22648f, 1.0f };
            GLfloat drawSpecular[] = {0.628281f, 0.555802f, 0.366065f, 1.0f};
            GLfloat Shininess = 51.2f;
            setupMaterial(drawAmbient, drawDiffuse, drawSpecular, Shininess);
            shortcrank.Draw();
        }
    glPopMatrix();
}


void drawCot2()
{
    glPushMatrix();
        cotta2.slideX = mledge1.slideX;
        cotta2.slideY = mledge1.slideY + mledge1SizeY+cotHeight/2;
        cotta2.slideZ = mledge1.slideZ;
        glRotatef(base.rotateY, 0, 1, 0);
        glTranslated(cotta2.slideX, cotta2.slideY, cotta2.slideZ);
        glScalef(cotta2.scaleX, cotta2.scaleY, cotta2.scaleZ);
        
        if(bWireFrame)
            cotta2.DrawWireframe();
        else{
            GLfloat drawAmbient[] = { 0.0f,0.0f,0.0f,1.0f };
            GLfloat drawDiffuse[] = { 0.55f,0.55f,0.55f,1.0f};
            GLfloat drawSpecular[] = {0.70f,0.70f,0.70f,1.0f };
            GLfloat Shininess = 32.0f;
            setupMaterial(drawAmbient, drawDiffuse, drawSpecular, Shininess);
            cotta2.Draw();
        }

    glPopMatrix();
}


void drawCotConnect()
{
    glPushMatrix();
        glRotatef(base.rotateY, 0, 1, 0);
        cottaconnect.slideX = crankShortLenght * cos(-shortcrank.rotateY/180*PI) + shortcrank.slideX;
        cottaconnect.slideY = cotta1.slideY + cotHeight/2;
        cottaconnect.slideZ = crankShortLenght * sin(-shortcrank.rotateY/180*PI) + shortcrank.slideZ;
        glTranslated(cottaconnect.slideX, cottaconnect.slideY, cottaconnect.slideZ);
        glScalef(cottaconnect.scaleX, cottaconnect.scaleY, cottaconnect.scaleZ);
        
        if(bWireFrame)
            cottaconnect.DrawWireframe();
        else{
            GLfloat drawAmbient[] = { 0.0f,0.0f,0.0f,1.0f };
            GLfloat drawDiffuse[] = { 0.55f,0.55f,0.55f,1.0f};
            GLfloat drawSpecular[] = {0.70f,0.70f,0.70f,1.0f };
            GLfloat Shininess = 32.0f;
            setupMaterial(drawAmbient, drawDiffuse , drawSpecular, Shininess);
            cottaconnect.Draw();
        }
    glPopMatrix();
}

void drawCotCentral()
{
    glPushMatrix();
        glRotatef(base.rotateY, 0, 1, 0);
        float sumX = cottaconnect.slideX + cotta2.slideX;
        float sumZ = cottaconnect.slideZ + cotta2.slideZ;
        float deltaX = cottaconnect.slideX - cotta2.slideX;
        float deltaZ = cottaconnect.slideZ - cotta2.slideZ;
        float dist = sqrt(central_radius*central_radius - deltaX*deltaX/4-deltaZ*deltaZ/4);
        cottacentral.slideX = sumX/2 + sin(-atan(deltaZ/deltaX))*dist;
        cottacentral.slideY = cotta2.slideY + cotHeight;
        cottacentral.slideZ = sumZ/2 + cos(-atan(deltaZ/deltaX))*dist;
        glTranslated(cottacentral.slideX, cottacentral.slideY, cottacentral.slideZ);
//        glTranslated(sumX/2, cotta2.slideY + cotHeight, sumZ/2);
//        glRotatef(-atan(deltaZ/deltaX)/PI*180, 0, 1, 0);
//        glTranslated(0, 0,dist);

        if(bWireFrame)
            cottacentral.DrawWireframe();
        else{
            GLfloat drawAmbient[] = { 0.0f,0.0f,0.0f,1.0f };
            GLfloat drawDiffuse[] = { 0.55f,0.55f,0.55f,1.0f};
            GLfloat drawSpecular[] = {0.70f,0.70f,0.70f,1.0f };
            GLfloat Shininess = 32.0f;
            setupMaterial(drawAmbient, drawDiffuse, drawSpecular, Shininess);
            cottacentral.Draw();
        }
    glPopMatrix();
}

void drawMovLegde2()
{
    glPushMatrix();
        glRotatef(base.rotateY, 0, 1, 0);
        mledge2.slideY = mshelf2.slideY + mshelf2SizeY + mledge2SizeY - hcleft;
        mledge2.slideZ = mshelf2.slideZ;
        mledge2.slideX = 2*cottacentral.slideX - cotta2.slideX;
        glTranslated(mledge2.slideX, mledge2.slideY, mledge2.slideZ);
        if(bWireFrame)
            mledge2.DrawWireframe();
        else{
            GLfloat drawAmbient[] = { 0.24725f, 0.1995f, 0.0745f, 1.0f };
            GLfloat drawDiffuse[] = {0.75164f, 0.60648f, 0.22648f, 1.0f };
            GLfloat drawSpecular[] = {0.628281f, 0.555802f, 0.366065f, 1.0f};
            GLfloat Shininess = 51.2f;
            setupMaterial(drawAmbient, drawDiffuse , drawSpecular, Shininess);
            mledge2.Draw();
        }

    glPopMatrix();
}

void drawCot3()
{
    glPushMatrix();
        glRotatef(base.rotateY, 0, 1, 0);
        cotta3.slideY =  mledge2.slideY + mledge2SizeY + cotHeight/2;
        cotta3.slideZ = mledge2.slideZ;
        cotta3.slideX = mledge2.slideX;
        glTranslated(cotta3.slideX, cotta3.slideY, cotta3.slideZ);
        if(bWireFrame)
            cotta3.DrawWireframe();
        else{
            GLfloat drawAmbient[] = { 0.0f,0.0f,0.0f,1.0f };
            GLfloat drawDiffuse[] = { 0.55f,0.55f,0.55f,1.0f};
            GLfloat drawSpecular[] = {0.70f,0.70f,0.70f,1.0f };
            GLfloat Shininess = 32.0f;
            setupMaterial(drawAmbient, drawDiffuse, drawSpecular, Shininess);
            cotta3.Draw();
        }

    glPopMatrix();
}

void drawLongCrank1(){
    glPushMatrix();

        glRotatef(base.rotateY, 0, 1, 0);
        glTranslated(cottaconnect.slideX, cottaconnect.slideY + cotHeight/2, cottaconnect.slideZ);
        float deltaX = -cottaconnect.slideX + cottacentral.slideX;
        float deltaZ = -cottaconnect.slideZ + cottacentral.slideZ;
        if (deltaX <=0)
            glRotatef(-atan(deltaZ/deltaX)/PI*180 + 180, 0, 1, 0);
        else
            glRotatef(-atan(deltaZ/deltaX)/PI*180, 0, 1, 0);

        if(bWireFrame)
            longcrank1.DrawWireframe();
        else
        {
            GLfloat drawAmbient[] = { 0.0f,0.05f,0.05f,1.0f };
            GLfloat drawDiffuse[] = {0.4f,0.5f,0.5f,1.0f };
            GLfloat drawSpecular[] = {0.04f,0.7f,0.7f,1.0f };
            GLfloat Shininess = 10.0f;
            setupMaterial(drawAmbient, drawDiffuse , drawSpecular, Shininess);
            longcrank1.Draw();
        }

    glPopMatrix();
}

void drawLongCrank2(){
    glPushMatrix();

        glRotatef(base.rotateY, 0, 1, 0);
        glTranslated(cotta2.slideX, cotta2.slideY, cotta2.slideZ);
        float deltaX = -cotta2.slideX + cottacentral.slideX;
        float deltaZ = -cotta2.slideZ + cottacentral.slideZ;
        if (deltaX <=0)
            glRotatef(-atan(deltaZ/deltaX)/PI*180 + 180, 0, 1, 0);
        else
            glRotatef(-atan(deltaZ/deltaX)/PI*180, 0, 1, 0);

        if(bWireFrame)
            longcrank2.DrawWireframe();
        else
        {
            GLfloat drawAmbient[] = { 0.0f,0.05f,0.05f,1.0f };
            GLfloat drawDiffuse[] = {0.4f,0.5f,0.5f,1.0f };
            GLfloat drawSpecular[] = {0.04f,0.7f,0.7f,1.0f };
            GLfloat Shininess = 10.0f;
            setupMaterial(drawAmbient, drawDiffuse , drawSpecular, Shininess);
            longcrank2.Draw();
        }

    glPopMatrix();
}

void drawLongCrank3(){
    glPushMatrix();

        glRotatef(base.rotateY, 0, 1, 0);
        glTranslated(cotta3.slideX, cotta3.slideY, cotta3.slideZ);
        float deltaX = -cotta3.slideX + cottacentral.slideX;
        float deltaZ = -cotta3.slideZ + cottacentral.slideZ;
        if (deltaX <=0)
            glRotatef(-atan(deltaZ/deltaX)/PI*180 + 180, 0, 1, 0);
        else
            glRotatef(-atan(deltaZ/deltaX)/PI*180, 0, 1, 0);

        if(bWireFrame)
            longcrank3.DrawWireframe();
        else
        {
            GLfloat drawAmbient[] = { 0.05f,0.05f,0.05f,1.0f };
            GLfloat drawDiffuse[] = { 0.5f,0.5f,0.5f,1.0f};
            GLfloat drawSpecular[] = { 0.7f,0.7f,0.7f,1.0f};
            GLfloat Shininess = 10.0f;
            setupMaterial(drawAmbient, drawDiffuse , drawSpecular, Shininess);
            longcrank3.Draw();
        }

    glPopMatrix();
}

void myDisplay()
{
    if (!lightsource)
        glDisable(GL_LIGHT1);
    else
        glEnable(GL_LIGHT1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    float k = camera_radius/sqrt(camera_dis*camera_dis
                   +camera_height*camera_height);
    glScaled(k, k, k);
    if(viewing)
        gluLookAt(0, 10, 0.0001, 0, 1, 0, 0, -1, 0);
    else
        gluLookAt(camera_dis*cos(camera_angle*PI/180), camera_height, camera_dis*sin(camera_angle*PI/180), 0, 1, 0, 0, 1, 0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, 2000, 2000);
    drawAxis();
    drawBase();
    drawCyl();
    drawBody1();
    drawPerShelf();
    drawMovShelf1();
    drawMovShelf2();
    drawMovLegde1();
    drawCot1();
    drawCot2();
    drawShortCrank();
    drawCotConnect();
    drawCotCentral();
    drawMovLegde2();
    drawCot3();
    drawLongCrank1();
    drawLongCrank2();
    drawLongCrank3();
    glFlush();
    glutSwapBuffers();
    autoAnimation();
}

void myInit()
{
    
    float    fHalfSize = 4;
    
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);

    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
    
    GLfloat    lightAmbient[]={ 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat    lightDiffuse[]={ 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat    lightSpecular[]={ 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat    light_position1[]={ 0.0f, 300.0f, 0.0f, 0.0f };
    GLfloat    light_position2[]={-12.0f, 100.0f, -12.0f, 0.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    
    glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular);
    
    glEnable(GL_LIGHT1);
    
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, const char* argv[])
{
        
    glutInit(&argc, (char**)argv); //initialize the tool kit
    glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGB | GLUT_DEPTH);//set the display mode
    glutInitWindowSize(screenWidth, screenHeight); //set window size
    glutInitWindowPosition(100, 100); // set window position on screen
    glutCreateWindow("Assignment"); // open the screen window

    base.CreateCylinder(20, baseHeight, baseRadius);
    base.slideY = baseHeight/2.0;

    cyl.CreateCylinder(20, cylHeight, cylRadius);

    body1.CreateCuboid(body1SizeX, body1SizeY, body1SizeZ);
    
    pshelf.CreateCuboid(pshelfSizeX, pshelfSizeY, pshelfSizeZ);
    
    mshelf1.CreateBoxWithCleft(mshelf1SizeX, mshelf1SizeY, mshelf1SizeZ, tzcleft, bzcleft, hcleft);
    
    mshelf2.CreateBoxWithCleft(mshelf2SizeX, mshelf2SizeY, mshelf2SizeZ, tzcleft, bzcleft, hcleft);
    
    mledge1.CreateBoxWithLegde(mledge1SizeX, mledge1SizeY, mledge1SizeZ, bzcleft, tzcleft, hcleft);
    mledge1.rotateY = base.rotateY;
    mledge1.slideX =  body1SizeX - mledge1SizeX;
    mledge1.slideZ =  body1SizeZ - mledge1SizeZ;
    
    mledge2.CreateBoxWithLegde(mledge2SizeX, mledge2SizeY, mledge2SizeZ, bzcleft, tzcleft, hcleft);
    
    cotta1.CreateCylinder(20, cotHeight, cotRadius);
    cotta1.slideZ = -body1SizeZ + pshelfSizeZ;
    
    shortcrank.CreateBoxConnectCylinder(20, crankHeight, crankShortLenght, crankRadiusIn, crankRadiusOut);
    shortcrank.slideZ = - body1SizeZ + pshelfSizeZ;
    
    cottaconnect.CreateCylinder(20, cotHeight*2, cotRadius);
    
    cotta2.CreateCylinder(20, cotHeight, cotRadius);
    
    cottacentral.CreateCylinder(20, cotHeight*3, cotRadius);
    
    cotta3.CreateCylinder(20, cotHeight, cotRadius);


    longcrank1.CreateBoxConnectCylinder(20, crankHeight, central_radius, crankRadiusIn, crankRadiusOut);

    longcrank2.CreateBoxConnectCylinder(20, crankHeight, central_radius, crankRadiusIn, crankRadiusOut);

    longcrank3.CreateBoxConnectCylinder(20, crankHeight, central_radius, crankRadiusIn, crankRadiusOut);

    myInit();

    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(myDisplay);
    
    glutMainLoop();
    return 0;
}
