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

#include "3DMath.h"
#include "3DGraph.h"

union REGS reg;
struct SREGS inreg;


void SetMode(int Mode)
{
	reg.h.ah=0;
	reg.h.al=Mode;
	int86(0x10,&reg,&reg);
}


void PreCalc()
{
	Word j;

	for(j=0;j<MaxY;j++)
		PreCalcY[j]=0;
	for(j=0;j<MaxX;j++)
		PreCalcY[j]=XRes*j;
}

void Plot(int x, int y, Byte color)
{
	Byte Offset;
	char  *address;

	if(!((x<0) || (y<0) || (x>MaxX) || (y>MaxY)))
	{
		Offset = PreCalcY[y] + x;
		address = (char *) (0xA0000000L + Offset);
		*address = color;
	}
}




void ClearPalette(PaletteRegister Color)
{
  Word i;

  for(i = 0; i <=255; i++)
  {
		  Color[i].Red=0;
		  Color[i].Grn=0;
		  Color[i].Blu=0;
  }
}

void SetPalette(PaletteRegister Hue)
{
	  reg.x.ax=0x1012;
	  segread(&inreg);
	  inreg.es= inreg.ds;
	  reg.x.bx=0;
	  reg.x.cx=256;
	  reg.x.dx=(int)&Hue[0];
	  int86x(0x10,&reg,&reg,&inreg);
}

void InitPalette(PaletteRegister Color)
{
	Word i;

	for(i=0; i<64; i++)
	{
		Color[i].Red=i;
		Color[i].Grn=i;
		Color[i].Blu=i;
	}

	for(i=64; i<128; i++)
	{
		Color[i].Red=i-64;
		Color[i].Grn=0;
		Color[i].Blu=0;
	}

	for(i=128; i<192; i++)
	{
		Color[i].Red=0;
		Color[i].Grn=i-128;
		Color[i].Blu=0;
	}

	for(i=192; i<255; i++)
	{
		Color[i].Red=0;
		Color[i].Grn=0;
		Color[i].Blu=i-192;
	}
}

void InitPalette2(PaletteRegister Color)
{
	Word i;

	for(i=0; i<36; i++)
	{
		Color[i].Red=0;
		Color[i].Grn=0;
		Color[i].Blu=Round(1.8*i);
	}

	for(i=36; i<72; i++)
	{
		Color[i].Red=0;
		Color[i].Grn=Round(1.8*(i-36));
		Color[i].Blu=0;
	}

	for(i=72; i<108; i++)
	{
		Color[i].Red=0;
		Color[i].Grn=Round(1.8*(i-72));
		Color[i].Blu=Round(1.8*(i-72));
	}

	for(i=108; i<144; i++)
	{
		Color[i].Red=Round(1.8*(i-108));
		Color[i].Grn=0;
		Color[i].Blu=0;
	}

	for(i=144; i<180; i++)
	{
		Color[i].Red=Round(1.8*(i-144));
		Color[i].Grn=0;
		Color[i].Blu=Round(1.8*(i-144));
	}

	for(i=180; i<216; i++)
	{
		Color[i].Red=Round(1.8*(i-180));
		Color[i].Grn=Round(1.8*(i-180));
		Color[i].Blu=0;
	}

	for(i=216; i<252; i++)
	{
		Color[i].Red=Round(1.8*(i-216));
		Color[i].Grn=Round(1.8*(i-216));
		Color[i].Blu=Round(1.8*(i-216));
	}

}

void CyclePalette(PaletteRegister Hue)
{
  Word i;
  RGB  tmp;

  tmp=Hue[0];
  for(i=1; i<=255; i++)
	  Hue[i-1]=Hue[i];
  Hue[255]=tmp;
  SetPalette(Hue);
}

void Swap(int *first,int *second)
{
	int temp;

	temp=*first;
	*first=*second;
	*second=temp;
}

void Circle(Word x,Word y, Word radius, Byte color)
{
	 int a, af, b, bf, target, r2;

	 target=0;
	 a=radius;
	 b=0;
	 r2=Sqr(radius);
	 while(a>=b)
	 {
		b=Round(sqrt(r2-Sqr(a)));
		Swap(&target,&b);
		while(b<target)
		{
			af=(120*a) / 100;
			bf=(120*b) / 100;
			Plot(x+af, y+b, color);
			Plot(x+bf, y+a, color);
			Plot(x-af, y+b, color);
			Plot(x-bf, y+a, color);
			Plot(x-af, y-b, color);
			Plot(x-bf, y-a, color);
			Plot(x+af, y-b, color);
			Plot(x+bf, y-a, color);
			++b;
		}
	 --a;
	 }
}


void Draw(int xx1, int yy1, int xx2, int yy2, Byte color)
{
  int LgDelta, ShDelta, Cycle, LgStep, ShStep;
   //int dtotal;

  LgDelta=xx2-xx1;
  ShDelta=yy2-yy1;
  if(LgDelta<0)
  {
	 LgDelta=-LgDelta;
	 LgStep=-1;
  }
  else
	 LgStep=1;
  if(ShDelta<0)
  {
	 ShDelta=-ShDelta;
	 ShStep=-1;
  }
  else
	 ShStep=1;
  if(ShDelta<LgDelta)
  {
	Cycle=LgDelta >> 1;
	while(xx1 != xx2)
	{
		Plot(xx1,yy1,color);
		Cycle+=ShDelta;
		if(Cycle>LgDelta)
		{
			Cycle-=LgDelta;
			yy1+=ShStep;
		}
		xx1+=LgStep;
	}
	Plot(xx1,yy1,color);
  }
  else
  {
	Cycle=ShDelta >> 1;
	Swap(&LgDelta,&ShDelta);
	Swap(&LgStep,&ShStep);
	while(yy1 != yy2)
	{
		Plot(xx1,yy1,color);
		Cycle+=ShDelta;
		if(Cycle>LgDelta)
		{
			Cycle-=LgDelta;
			xx1+=ShStep;
		}
		yy1+=LgStep;
	}
	Plot(xx1,yy1,color);
	}
}

void InitGraphics()
{
	XRes=MaxXres;
	YRes=MaxYres;
	PreCalc();
	SetMode(19);
	ClearPalette(Color);
	InitPalette2(Color);
	SetPalette(Color);
}

void WaitForKey()
{
	char k;

	while(!(k=getchar()));
}

void ExitGraphics()
{
	sound(1000);
	delay(500);
	nosound();
	WaitForKey();
	SetMode(3);
}

void Title()
{
	/*textcolor(YELLOW); */
	/*textbackground(BLUE); */
	clrscr();
}




void InitPlotting(int Ang,int Tlt)
{
	CentreX=MaxX >> 1;
	CentreY=MaxY >> 1;
	Angl=Ang;
	Tilt=Tlt;
	CosA=CosD(Angl);
	SinA=SinD(Angl);
	CosB=CosD(Tilt);
	SinB=SinD(Tilt);
	CosACosB=CosA*CosB;
	SinASinB=SinA*SinB;
	CosASinB=CosA*SinB;
	SinACosB=SinA*CosB;
}



void InitPerspective(Boolean Perspective, float x, float y, float z, float m)
{
	PerspectivePlot=Perspective;
	Mx=x;
	My=y;
	Mz=z;
	ds=m;
}

void MapCoordinates(float X,float Y,float Z, int*Xp, int *Yp)
{
	float Xt, Yt, Zt;

	Xt=(Mx+X*CosA-Y*SinA);
	Yt=(My+X*SinASinB+Y*CosASinB+Z*CosB);
	if(PerspectivePlot)
	{
	  Zt=Mz+X*SinACosB+Y*CosACosB-Z*SinB;
	  *Xp = CentreX+Round(ds*Xt/Zt);
	  *Yp = CentreY-Round(ds*Yt/Zt);
	}
	else
	{
		*Xp = CentreX+Round(Xt);
		*Yp = CentreY-Round(Yt);
	}
}

void CartesianPlot3D(float X,float Y, float Z, Byte Color)
{
	int Xp, Yp;

	MapCoordinates(X,Y,Z,&Xp,&Yp);
	Plot(Xp,Yp,Color);
}

void CylindricalPlot3D(float Rho,float Theta,float Z,Byte Color)
{
	float X, Y;

	Theta=Radians(Theta);
	X=Rho*CosD(Theta);
	Y=Rho*SinD(Theta);
	CartesianPlot3D(X,Y,Z,Color);
}

void SphericalPlot3D(float R,float Theta,float Phi,Byte Color)
{
	float X, Y, Z;

	Theta=Radians(Theta);
	Phi=Radians(Phi);
	X=R*sin(Theta)*cos(Phi);
	Y=R*cos(Theta)*sin(Phi);
	Z=R*cos(Theta);
	CartesianPlot3D(X,Y,Z,Color);
}

void DrawLine3D(TDA Pnt1,TDA Pnt2,Byte Color)
{
	int Xp1, Yp1;
	int Xp2, Yp2;
	float x1, y1, z1;
	float x2, y2, z2;

	UnVec(Pnt1,&x1,&y1,&z1);
	UnVec(Pnt2,&x2,&y2,&z2);
	MapCoordinates(x1,y1,z1,&Xp1,&Yp1);
	MapCoordinates(x2,y2,z2,&Xp2,&Yp2);
	Draw(Xp1,Yp1,Xp2,Yp2,Color);
}



void PutPixel(int x,int y,Byte Color,Byte Intensity)
{
  Byte Col;

  if(Intensity>MaxInten)
  {
		printf("Inten > MaxInten!!\n\nHit any key to exit\n");
		getchar();
		exit(1);
  }
  Col=((MaxInten+1)*(Color-1)+Intensity) & 255;
  Plot(x,y,Col);
}

int GetPixel(int x,int y)
{
	reg.x.ax=3328;
	reg.x.dx=y;
	reg.x.cx=x;
	int86(0x10,&reg,&reg);
	return(reg.x.ax&255);
	//return 1;
}



void PutAxisAndPalette(Boolean PlaceOnScreen)
{
	if(PlaceOnScreen)
		DrawAxisAndPalette=true;
	else
		DrawAxisAndPalette=false;
}

void DisplayAxis()
{
	int x, y, z;

	for(x=-100;x<101;x++)
	{
		CartesianPlot3D(x,0,0,35);
		CartesianPlot3D(100,0,0,251);
	}
	for(y=-100;y<101;y++)
	{
		CartesianPlot3D(0,y,0,71);
		CartesianPlot3D(0,100,0,251);
	}
	for(z=-100;z<101;z++)
	{
		CartesianPlot3D(0,0,z,107);
		CartesianPlot3D(0,0,100,251);
	}
}

void DisplayPalette()
{
	int X, Y;
	Byte Color;
	Byte Intensity;

	for(Color=1; Color<=MaxCol; Color++)
	{
		for(Intensity=0; Intensity<MaxInten; Intensity++)
		{
			for(X=0;X<4;X++)
			{
				for(Y=0;Y<4;Y++)
					PutPixel(X+5*Color,190-Y-5*Intensity,Color,Intensity);
			}
		}
	}
}

void AxisAndPalette()
{
	if(DrawAxisAndPalette)
	{
		DisplayAxis();
		DisplayPalette();
	}
}









