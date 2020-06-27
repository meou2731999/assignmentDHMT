//  Le Ba Quan
//  1712817
//  main.cpp
//  Assignment
//
//  Created by Le Quan on 6/24/20.
//  Copyright © 2020 Le Quan. All rights reserved.

#define GL_SILENCE_DEPRECATION

#include <iostream>
#include "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/Headers/gl.h"
#include "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/GLUT.framework/Headers/glut.h"
#include <math.h>
#include "supportClass.h"
#include "Mesh.h"

using namespace std;

#define PI        3.1415926

int        screenWidth = 1000;
int        screenHeight= 1000;

bool     bWireFrame = false;

float    cameraX = -8;
float    cameraY = 6;
float    cameraZ = 8;

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
    float    fRInc;
    float    fAngle;
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
//    case '5':
//        cotta1.slideY += 0.01;
//        cotta2.slideY += 0.01;
//        break;
//    case '6':
//        cotta1.slideY -= 0.01;
//        cotta2.slideY -= 0.01;
//        break;
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

    case 'w':
    case 'W':
        bWireFrame = !bWireFrame;
        break;
    }
    glutPostRedisplay();
}

void SpecialKeys(int key, int x, int y)
{
switch (key)
{
    case GLUT_KEY_LEFT:
    break;
    case GLUT_KEY_RIGHT:
    break;
    case GLUT_KEY_UP:
        cameraY += 0.4;
        break;
    case GLUT_KEY_DOWN:
        cameraY -= 0.4;
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
            base.DrawColor();

    glPopMatrix();
}
void drawCyl()
{
    glPushMatrix();
    
        glTranslated(0, cyl.slideY + baseHeight, 0);
        glScalef(cyl.scaleX, cyl.scaleY, cyl.scaleZ);
        glRotatef(base.rotateY, 0, 1, 0);

        if(bWireFrame)
            cyl.DrawWireframe();
        else
            cyl.DrawColor();

    glPopMatrix();
}

void drawPerShelf()
{
    glPushMatrix();

        glRotatef(base.rotateY, 0, 1, 0);
        glTranslated(0, body1SizeY*2 + pshelfSizeY + cylHeight*cyl.scaleY + pshelf.slideY + baseHeight, - body1SizeZ + pshelfSizeZ);
        glScalef(pshelf.scaleX, pshelf.scaleY, pshelf.scaleZ);

        if(bWireFrame)
            pshelf.DrawWireframe();
        else{
            pshelf.DrawColor();
        }

    glPopMatrix();
}

void drawMovShelf1()
{
    glPushMatrix();

        glRotatef(base.rotateY, 0, 1, 0);
    glTranslated(body1SizeX - mshelf1SizeX, body1SizeY*2 + mshelf1SizeY + cylHeight*cyl.scaleY + mshelf1.slideY + baseHeight, body1SizeZ - mshelf1SizeZ);
        glScalef(mshelf1.scaleX, mshelf1.scaleY, mshelf1.scaleZ);

        if(bWireFrame)
            mshelf1.DrawWireframe();
        else{
            mshelf1.DrawColor();
        }

    glPopMatrix();
}

void drawMovShelf2()
{
    glPushMatrix();

        glRotatef(base.rotateY, 0, 1, 0);
        glTranslated(- body1SizeX + mshelf2SizeX, body1SizeY*2 + mshelf2SizeY + cylHeight*cyl.scaleY + mshelf2.slideY + baseHeight, body1SizeZ - mshelf2SizeZ);
        glScalef(mshelf2.scaleX, mshelf2.scaleY, mshelf2.scaleZ);
    
        if(bWireFrame)
            mshelf2.DrawWireframe();
        else{
            mshelf2.DrawColor();
        }

    glPopMatrix();
}

void drawMovLegde1()
{
    glPushMatrix();
        glRotatef(base.rotateY, 0, 1, 0);
        glTranslated(body1SizeX - mledge1SizeX, body1SizeY*2 + mshelf1SizeY*2 + mledge1SizeY + cylHeight*cyl.scaleY + mledge1.slideY + baseHeight - hcleft, body1SizeZ - mledge1SizeZ);
        glScalef(mledge1.scaleX, mledge1.scaleY, mledge1.scaleZ);
    
        glRotated(180, 1, 0, 0);

        if(bWireFrame)
            mledge1.DrawWireframe();
        else{
            mledge1.DrawColor();
        }

    glPopMatrix();
}

void drawMovLegde2()
{
    glPushMatrix();
        glRotatef(base.rotateY, 0, 1, 0);
        glTranslated(- body1SizeX + 2 * mshelf2SizeX, body1SizeY*2 + mshelf2SizeY*2 + mledge2SizeY + cylHeight*cyl.scaleY + mledge2.slideY + baseHeight - hcleft, body1SizeZ - mledge2SizeZ);
        glScalef(mledge2.scaleX, mledge2.scaleY, mledge2.scaleZ);
    
        glRotated(180, 1, 0, 0);

        if(bWireFrame)
            mledge2.DrawWireframe();
        else{
            mledge2.DrawColor();
        }

    glPopMatrix();
}

void drawCot1()
{
    glPushMatrix();

        glRotatef(base.rotateY, 0, 1, 0);
        glTranslated(0,baseHeight + cylHeight*cyl.scaleY + body1SizeY * 2 + pshelfSizeY * 2 + cotHeight/2 + cotta1.slideY , - body1SizeZ + pshelfSizeZ);
        glScalef(cotta1.scaleX, cotta1.scaleY, cotta1.scaleZ);

        if(bWireFrame)
            cotta1.DrawWireframe();
        else
            cotta1.DrawColor();

    glPopMatrix();
}

void drawShortCrank()
{
    glPushMatrix();

        glRotatef(base.rotateY, 0, 1, 0);
    glTranslated(0, baseHeight + cylHeight*cyl.scaleY + body1SizeY * 2 + pshelfSizeY * 2 + crankHeight/2 + shortcrank.slideY, - body1SizeZ + pshelfSizeZ);
    glRotatef(shortcrank.rotateY, 0, 1, 0);
        glScalef(shortcrank.scaleX, shortcrank.scaleY, shortcrank.scaleZ);

        if(bWireFrame)
            shortcrank.DrawWireframe();
        else
            shortcrank.DrawColor();

    glPopMatrix();
}


void drawCot2()
{
    glPushMatrix();

        glRotatef(base.rotateY, 0, 1, 0);
        glTranslated(body1SizeX - mledge1SizeX, baseHeight + cylHeight*cyl.scaleY + body1SizeY*2 + mshelf1SizeY*2 + mledge1SizeY*2 - hcleft + cotHeight/2 + cotta2.slideY, body1SizeZ - mledge1SizeZ);
        glScalef(cotta1.scaleX, cotta1.scaleY, cotta1.scaleZ);

        if(bWireFrame)
            cotta1.DrawWireframe();
        else
            cotta1.DrawColor();

    glPopMatrix();
}

void drawCot3()
{
    glPushMatrix();

        glRotatef(base.rotateY, 0, 1, 0);
        glTranslated(- body1SizeX + 2 * mshelf2SizeX,baseHeight + cylHeight*cyl.scaleY + body1SizeY*2 + mshelf2SizeY*2 + mledge2SizeY*2 - hcleft + cotHeight/2 + cotta3.slideY, body1SizeZ - mledge2SizeZ);
        glScalef(cotta1.scaleX, cotta1.scaleY, cotta1.scaleZ);

        if(bWireFrame)
            cotta1.DrawWireframe();
        else
            cotta1.DrawColor();

    glPopMatrix();
}

void drawBody1()
{
    glPushMatrix();
        glRotatef(base.rotateY, 0, 1, 0);
        glTranslated(0, body1SizeY + cylHeight*cyl.scaleY + baseHeight, 0);
        
        if(bWireFrame)
            body1.DrawWireframe();
        else
            body1.DrawColor();

    glPopMatrix();
}


void myDisplay()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ, 0, 1, 0, 0, 1, 0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(screenWidth/2, screenHeight/2, screenWidth, screenHeight);
    
    drawAxis();
    drawBase();
    drawCyl();
    drawBody1();
    drawPerShelf();
    drawMovShelf1();
    drawMovShelf2();
    drawMovLegde1();
    drawMovLegde2();
    drawCot1();
    drawCot2();
    drawCot3();
    drawShortCrank();

    glFlush();
    glutSwapBuffers();
}

void myInit()
{
    float    fHalfSize = 3;

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);

    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);

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
    base.SetColor(2);
    base.slideY = baseHeight/2.0;

    cyl.CreateCylinder(20, cylHeight, cylRadius);
    cyl.SetColor(0);
    cyl.slideY = cylHeight/2.0;

    body1.CreateCuboid(body1SizeX, body1SizeY, body1SizeZ);
    body1.SetColor(4);
    
    pshelf.CreateCuboid(pshelfSizeX, pshelfSizeY, pshelfSizeZ);
    pshelf.SetColor(2);
    
    mshelf1.CreateBoxWithCleft(mshelf1SizeX, mshelf1SizeY, mshelf1SizeZ, tzcleft, bzcleft, hcleft);
    mshelf1.SetColor(1);
    
    mshelf2.CreateBoxWithCleft(mshelf2SizeX, mshelf2SizeY, mshelf2SizeZ, tzcleft, bzcleft, hcleft);
    mshelf2.SetColor(2);
    
    mledge1.CreateBoxWithLegde(mledge1SizeX, mledge1SizeY, mledge1SizeZ, bzcleft, tzcleft, hcleft);
    mledge1.SetColor(3);
    
    mledge2.CreateBoxWithLegde(mledge2SizeX, mledge2SizeY, mledge2SizeZ, bzcleft, tzcleft, hcleft);
    mledge2.SetColor(3);
    
    cotta1.CreateCylinder(20, cotHeight, cotRadius);
    cotta1.SetColor(12);
    
    cotta2.CreateCylinder(20, cotHeight, cotRadius);
    cotta2.SetColor(12);
    
    cotta3.CreateCylinder(20, cotHeight, cotRadius);
    cotta3.SetColor(12);

    shortcrank.CreateBoxConnectCylinder(20, crankHeight, crankShortLenght, crankRadiusIn, crankRadiusOut);
    shortcrank.SetColor(0);
    
    myInit();

    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(myDisplay);
    
    glutMainLoop();
    return 0;
}
