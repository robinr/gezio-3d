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
/*******      app.c    Constants and Structs            ********/
/********************************************************************/

#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <math.h>
#include <string.h>
#include <alloc.h>

#define  log_file "d:\proj\model1\model_log.txt"
#include "3DMath.h"
#include "3DGraph.h"
#include "3DModel.h"
#include "3DAddobjs.h"
#include "3DDispobjs.h"

#include "app.h"



void DoPreview(Boolean State)
{
	// log_printf("Entering DoPreview()\n");
	Preview=State;
	// log_printf("Exiting DoPreview()\n\n");

}

void DoWireFrame(Boolean State)
{
	// log_printf("Entering DoWireFrame()\n");
	WireFrame=State;
	// log_printf("Exiting DoWireFrame()\n\n");
}

void DoSolidModel(Boolean State)
{
	// log_printf("Entering DoSolidModel()\n");
	SolidModel=State;
	// log_printf("Exiting DoSolidModel()\n\n");
}

void VertSort(Boolean Sort)
{
	// log_printf("Entering VertSort()\n");
	VerticalSort=Sort;
	// log_printf("Exiting VertSort()\n\n");
}

void DoTransform(Matx4x4 XForm)
{
	TDA temp, temp2;

	// log_printf("Entering DoTransform()\n");
	for(VertexNum=1; VertexNum<=LastVertex; VertexNum++)
	{
		VecScalMultI(InvScaleData, Vertex[VertexNum], temp2);
		Transform(temp2, XForm, temp);
		VecScalMultInt(ScaleImage, temp, Vertex[VertexNum]);
	}
	// log_printf("Exiting DoTransform()\n\n");
}

void DoInvTransform(Matx4x4 XForm)
{
	TDA temp, temp2;

	// log_printf("Entering DoInvTransformation()\n");
	for(VertexNum=1; VertexNum<=LastVertex; VertexNum++)
	{
		VecScalMultI(InvScaleImage, Vertex[VertexNum], temp2);
		Transform(temp2, XForm, temp);
		VecScalMultInt(ScaleData, temp, Vertex[VertexNum]);
	}
	// log_printf("Exiting DoInvTransformation()\n\n");
}

void AffineTransformation(float Tx, float Ty, float Tz, float Sx, float Sy, float Sz, float Rx, float Ry, float Rz)
{
	Matx4x4 XForm;

	// log_printf("Entering AffineTransformation()\n");
	PrepareMatrix(Tx, Ty, Tz, Sx, Sy, Sz, Rx, Ry, Rz, XForm);
	DoTransform(XForm);
	// log_printf("Exiting AffineTransformation()\n\n");
}

void InvAffineTransformation(float Tx, float Ty, float Tz, float Sx, float Sy, float Sz, float Rx, float Ry, float Rz)
{
	Matx4x4 XForm;

	// log_printf("Entering InvAffineTransformation()\n");
	PrepareInvMatrix(-Tx, -Ty, -Tz, 1.0/Sx, 1.0/Sy, 1.0/Sz, -Rx, -Ry, -Rz, XForm);
	DoInvTransform(XForm);
	// log_printf("Exiting InvAffineTransformation()\n\n");
}



void GetViewVector()
{
	float Phi, Theta;
	float x, y, z;

	// log_printf("Entering GetViewVector()\n");
	Phi=Radians((float)ViewPhi-Angl);
	Theta=Radians((float)ViewTheta-Tilt);
	x=sin(Theta)*cos(Phi);
	y=sin(Theta)*sin(Phi);
	z=cos(Theta);
	Vec(x, y, z, View);
	// log_printf("Exiting GetViewVector()\n\n");
}


void InitLightDirection(int LgtPhi, int LgtTheta)
{
	// log_printf("Entering InitLightDirection\n");
	// log_printf("Light Direction is %d around the z-Axis and\n", LgtPhi);
	// log_printf(" %d off the z-Axis\n", LgtTheta);
	LightPhi=(float)LgtPhi;
	LightTheta=(float)LgtTheta;
	// log_printf("Exiting InitLightDirection\n");
}


void GetLightVector()
{
	float Phi, Theta;
	float x, y, z;

	// log_printf("Entering GetLightVector()\n");
	Phi=Radians(LightPhi);
	Theta=Radians(LightTheta);
	x=sin(Theta)*cos(Phi);
	y=sin(Theta)*sin(Phi);
	z=cos(Theta);
	Vec(x, y, z, Light);
	// log_printf("Exiting GetLightVector()\n\n");
}



void GetSurfaceNormalVector(VoxelArray Face3d)
{
	float Length, Length2;
	TDA Dir1;
	TDA Dir2;
	TDA Temp1;
	TDA Temp2;
	TDA Temp3;
	TDA SrfNorm2;

	// log_printf("Entering GetSurfaceNormalVector()\n");
	VecCopy(Face3d[2], Temp1);
	VecCopy(Face3d[1], Temp2);
	VecCopy(Face3d[LastVertexNumInFacet], Temp3);
	VecSub(Temp1, Temp2, Dir1);
	VecSub(Temp3, Temp2, Dir2);
	VecCross(Dir1, Dir2, SrfNorm);
	Length=VecLen(SrfNorm);
	VecCopy(Face3d[LastVertexNumInFacet], Temp1);
	VecCopy(Face3d[LastVertexNumInFacet-1], Temp2);
	VecCopy(Face3d[LastVertexNumInFacet-2], Temp3);
	VecSub(Temp1, Temp2, Dir1);
	VecSub(Temp3, Temp2, Dir2);
	VecCross(Dir1, Dir2, SrfNorm2);
	Length2=VecLen(SrfNorm2);
	if(Length==0.0)
		VecScalMult(1.0/Length2, SrfNorm2, SrfNorm);
	else
	{
		if(Length2==0.0)
			VecScalMult(1.0/Length, SrfNorm, SrfNorm);
		else
		{
			VecScalMult(1.0/Length, SrfNorm, SrfNorm);
			VecScalMult(1.0/Length2, SrfNorm2, SrfNorm2);
			VecAdd(SrfNorm, SrfNorm2, SrfNorm);
			VecScalMult(0.5, SrfNorm, SrfNorm);
		}
	}
	// log_printf("Exiting GetSurfaceNormalVector()\n");
}

Byte Intensity()
{
	float Ambient=0.30;
	float DifRfl=0.50;
	float SpcRfl=0.20;
	float Gloss=5.0;
	float CosTheta;
	float CosAlpha;
	TDA Ref;
	float TwoCosTheta;
	TDA temp;

	// log_printf("Entering Intensity()\n");
	CosTheta=VecDot(SrfNorm, Light);
	if(CosTheta<=0.0)
	{
		// log_printf("Exiting Intensity()\n");
		return(Round(MaxInten*Ambient));
	}
	else
	{
		TwoCosTheta=2.0*CosTheta;
		VecScalMult(TwoCosTheta, SrfNorm, temp);
		VecNormalize(temp);
		VecSub(temp, Light, Ref);
		VecNormalize(Ref);
		CosAlpha=VecDot(View, Ref);
		// log_printf("Exiting Intensity()\n");
		return(Round(MaxInten*(Ambient+DifRfl*CosTheta+SpcRfl * pow(CosAlpha, Gloss))));
	}
}


Boolean Visible(VoxelArray Face3d)
{
	float CosBeta;
	float nvx, nvy, nvz;
	TDA temp, v;
	Boolean vt;

	// log_printf("Entering Visibe()\n");
	GetSurfaceNormalVector(Face3d);
	VecCopy(View, v);
	if((!(Preview || WireFrame)) && Reflect && MirrorZ)
		v[2]=-v[2];
	VecElemMult(1.0, SrfNorm, v, temp);
	UnVec(temp, &nvx, &nvy, &nvz);
	vt=true;
	CosBeta=nvx+nvy+nvz;
	if((MirrorZ || (!(MirrorX || MirrorY))) && (CosBeta<0.0))
		vt=false;
	else
	{
		CosBeta=-nvx+nvy+nvz;
		if(MirrorX && (CosBeta<0.0))
			vt=false;
		else
		{
			CosBeta=nvx-nvy+nvz;
			if(MirrorY && (CosBeta<0.0))
				vt=false;
		}
	}
	// log_printf("Exiting Visibe()\n");
	return(vt);
}


void InitReflectionBuffer()
{
	int i, j;

	// log_printf("Entering InitReflectionBuffer()\n");
	for(i=0; i<=XBytes; i++)
	{
		for(j=0; j<=MaxY; j++)
			Refl[i][j]=0;
	}
	// log_printf("Exiting InitReflectionBuffer()\n");
}

Boolean Reflected(int x, int y)
{
	Byte tmp;

	// log_printf("Entering Reflected()\n");
	tmp=Refl[x/8][y]&(128>>(x%8));
	if(tmp==0)
	{
		// log_printf("Exiting Reflected()\n");
		return false;
	}
	else
	{
		// log_printf("Exiting Reflected()\n");
		return true;
	}
}

void MakeReflected(int x, int y)
{
	// log_printf("Entering MakeReflected()\n");
	Refl[x/8][y]=Refl[x/8][y]|(128>>(x%8));
	// log_printf("Exiting MakeReflected()\n");
}



void GetProjectedCroods(VoxelArray Face3d, PixelArray Face2d)
{
	float xt, yt, zt;

	// log_printf("Entering GetProjectedCroods()\n");
	for(VertexNumInFacet=1; VertexNumInFacet<=LastVertexNumInFacet; VertexNumInFacet++)
	{
		UnVec(Face3d[VertexNumInFacet], &xt, &yt, &zt);
		if(Reflect)
		{
			if(MirrorZ)
			{
				zt=-zt;
				if(EdgeReflector && (!(EdgeReflectorAtZero)))
					zt-=200.0;
			}
			else
			{
				if(MirrorY)
				{
					yt=-yt;
					if(EdgeReflector ||EdgeReflectorAtZero)
					yt-=200.0;
				}
				else
				{
					if(MirrorX)
					{
						xt=-xt;
						if(EdgeReflector || EdgeReflectorAtZero)
						xt-=200.0;
					}
				}
			}
		}
		MapCoordinates(xt, yt, zt, &Face2d[VertexNumInFacet].x, &Face2d[VertexNumInFacet].y);
	 }
	Face2d[LastVertexNumInFacet+1]=Face2d[1];
	// log_printf("Exiting GetProjectedCroods()\n");
}


void PutFacet2(PixelArray Face2d, Byte Color, Byte Intens)
{
	int xc, yc;
	int i, x;
	int OldVertNum;
	int VertNum;
	int mnx, mxx;
	int mny, mxy;
	float slope;

	// log_printf("Entering PutFacet2()\n");
	if(Intens<1)
		return;
	if(Reflect && (Intens!=1))
	{
		--Intens;
		if(Intens!=2)
		{
			--Intens;
			if(Intens!=3)
				--Intens;
		}
	}
	mny=Face2d[1].y;
	mxy=Face2d[1].y;
	for(i=2; i<=LastVertexNumInFacet; i++)
	{
		if(Face2d[i].y>mxy)
			mxy=Face2d[i].y;
		if(Face2d[i].y<mny)
			mny=Face2d[i].y;
	}
	if(mny<0)
		mny=0;
	if(mxy>MaxY)
		mxy=MaxY;
	for(yc=mny; yc<=mxy; yc++)
	{
		mnx=MaxX+1;
		mxx=-1;
		OldVertNum=LastVertexNumInFacet;
		for(VertNum=1; VertNum<=LastVertexNumInFacet; VertNum++)
		{
			if((Face2d[OldVertNum].y>=yc) || (Face2d[VertNum].y>=yc))
			{
				if((Face2d[OldVertNum].y<=yc) || (Face2d[VertNum].y<=yc))
				{
					if(Face2d[OldVertNum].y != Face2d[VertNum].y)
					{
						slope=(float)(Face2d[VertNum].x-Face2d[OldVertNum].x)/(float)(Face2d[VertNum].y-Face2d[OldVertNum].y);
						x=Round(slope*(float)((yc-Face2d[OldVertNum].y))+Face2d[OldVertNum].x);
						if(x<mnx)
							mnx=x;
						if(x>mxx)
							mxx=x;
					}
				}
			}
			OldVertNum=VertNum;
		}
		if(mnx<0)
			mnx=0;
		if(mxx>MaxX)
			mxx=MaxX;
		if(mnx<=mxx)
		{
			for(xc=mnx; xc<=mxx; xc++)
			{
				if(Mirroring)
				{
					MakeReflected(xc, yc);
					PutPixel(xc, yc, Color, Intens);
				}
				else
				{
					if(!(Reflect))
					{
					  	PutPixel(xc, yc, Color, Intens);  // Raghu adding code to fix display
					}
					else
					{
						if(Reflected(xc, yc))
							PutPixel(xc, yc, Color, Intens);
					}
				}
			}
		}
	}
 // log_printf("Entering PutFacet2()\n");
}


void GetSceneFile()
{
	int i;
	Byte x, y;

	// log_printf("Entering GetSceneFile\n");
	printf("\n Enter File Name -> ");
	x=wherex();
	y=wherey();
	gets(SceneFile);
	if(!(strcmp(SceneFile, "")))
	{
		strcpy(SceneFile, "CUBEPLAN");
		gotoxy(x, y);
		puts(SceneFile);
	}
	puts("");
	for(i=0; i<strlen(SceneFile); i++)
		SceneFile[i]=toupper(SceneFile[i]);
	// log_printf("Exiting GetSceneFile\n\n");
}

void LoadDescAndScene(Name FileName)
{
	FILE *TextDiskFile;

	printf("Entering LoadDescAndScene\n");
	TextDiskFile=fopen(FileName, "r+t");
	fscanf(TextDiskFile, "%s", B);
	PutAxisAndPalette(Bool(B));
	if(Bool(B))
		printf("Axis and Pallete Display On\n");
	else
		printf("Axis and Pallete Display Off\n");
	fscanf(TextDiskFile, "%s", B);
	DoSolidModel(Bool(B));
	if(Bool(B))
		printf("Solid Model Diaplay On\n");
	else
		printf("Solid Model Diaplay Off\n");
	if(SolidModel)
	{
		fscanf(TextDiskFile, "%s", B);
		fscanf(TextDiskFile, "%s", B);
		DoPreview(false);
		DoWireFrame(false);
	}
	else
	{
		fscanf(TextDiskFile, "%s", B);
		DoPreview(Bool(B));
		if(Bool(B))
			printf("Vertex Diaplay On\n");
		else
			printf("Vertex Diaplay Off\n");
		fscanf(TextDiskFile, "%s", B);
		DoWireFrame(Bool(B));
		if(Bool(B))
			printf("WireFrame Diaplay On\n");
		else
			printf("WireFrame Diaplay Off\n");
	}
	fscanf(TextDiskFile, "%s", B);
	fclose(TextDiskFile);
	if(Bool(B))
	{
		printf("Loading Scene from Disk File\n");
		GetSceneFile();
		printf("The scene file getting loaded is %s\n",SceneFile);
		AddObjectsToSceneFromDiskFile(SceneFile);
	}
	else
	{
		printf("Loading Scene from Procedure\n\n");
		AddObjectsToSceneFromProcedure();
	}
	printf("Hit any key....\n");
	// log_printf("Exiting LoadDiskAndScene\n\n");
	getch();
}


void main()
{
	int i=0;
	int result;
	result = init_log(log_file);

	// log_printf("Entering main()\n");
	Facet=farcalloc(((MaxFacet+1)*(MaxVertexNumInFacet+1)), sizeof(int));
	if(Facet==0)
	{
		printf("Not Enough Memory!\n");
		getch();
		exit(1);
	}
	Title();
	printf("3-D Modeling program\n\n");
	InitReflectionBuffer();
	InitVertexBuffer();
	InitObjectBuffer();
	LoadDescAndScene("MODEL.DES");
	//getch();
	InitGraphics();
	AxisAndPalette();

	// AddObjectsToSceneFromProcedure();
	//getch();
	if(DrawAxisAndPalette)
		WaitForKey();
	DisplayObjectsInScene();
	//Circle(80,80,20,100);
	//for(i=0; i<20;i++)
	//PutPixel(150, 150+i, i, 35);
	getch();
	ExitGraphics();
	farfree(Facet);
	// log_printf("Exiting main()\n\n");
	log_close();
}
