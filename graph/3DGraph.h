/* Licensed to the Apache Software Foundation (ASF) under one
       or more contributor license agreements.  See the NOTICE file
       distributed with this work for additional information
       regarding copyright ownership.  The ASF licenses this file
       to you under the Apache License, Version 2.0 (the
       "License"); you may not use this file except in compliance
       with the License.  You may obtain a copy of the License at

         http://www.apache.org/licenses/LICENSE-2.0

       Unless required by applicable law or agreed to in writing,
       software distributed under the License is distributed on an
       "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
       KIND, either express or implied.  See the License for the
       specific language governing permissions and limitations
       under the License.
*/

/*  Gezio-3D
      Copyright [2011] The Apache Software Foundation

      This product includes software developed at
      http://code.google.com/p/gezio-3d/ and the owner of this
      
      source : robinr.rao@gmail.com
*/	



/********************************************************************/
/*******      3dgraph.h     Constants and Structs            ********/
/********************************************************************/
#ifndef _3DGRAPH_H_
#define _3DGRAPH_H_


#define MaxXres  320
#define MaxYres  200
#define MaxX   (MaxXres -1)
#define MaxY   (MaxYres -1)

#define MaxCol 	7
#define MaxInten 	35

int XRes, YRes;
Word PreCalcY[MaxY+1];

typedef struct
{
	Byte Red;
	Byte Grn;
	Byte Blu;
}RGB;


typedef RGB PaletteRegister[255];

PaletteRegister Color;

int CentreX, CentreY;
int Angl, Tilt;
float CosA, SinA;
float CosB, SinB;
float CosACosB, SinASinB;
float CosASinB, SinACosB;

Boolean PerspectivePlot;
float   Mx, My, Mz, ds;

Boolean DrawAxisAndPalette;

/********************************************************************/
/********      3dgraph.h    Functions and Interfaces          ********/
/********************************************************************/

void SetMode(int Mode);
void PreCalc();
void Plot(int x, int y, Byte color);
void ClearPalette(PaletteRegister Color);
void SetPalette(PaletteRegister Hue);
void InitPalette(PaletteRegister Color);
void InitPalette2(PaletteRegister Color);
void CyclePalette(PaletteRegister Hue);
void Swap(int *first,int *second);
void Circle(Word x,Word y, Word radius, Byte Color);
void Draw(int xx1, int yy1, int xx2, int yy2, Byte color);
void InitGraphics();
void WaitForKey();
void ExitGraphics();
void Title();
void InitPlotting(int Ang,int Tlt);
void InitPerspective(Boolean Perspective, float x, float y, float z, float m);
void MapCoordinates(float X,float Y,float Z, int*Xp, int *Yp);
void CartesianPlot3D(float X,float Y, float Z, Byte Color);
void CylindricalPlot3D(float Rho,float Theta,float Z,Byte Color);
void SphericalPlot3D(float R,float Theta,float Phi,Byte Color);
void DrawLine3D(TDA Pnt1,TDA Pnt2,Byte Color);
void PutPixel(int x,int y,Byte Color,Byte Intensity);
int  GetPixel(int x,int y);
void PutAxisAndPalette(Boolean PlaceOnScreen);
void DisplayAxis();
void DisplayPalette();
void AxisAndPalette();

#endif