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
#include "3DModel.h"
#include "3DAddobjs.h"
#include "3DDispobjs.h"


void PrepareSort()
{
	ReflSurface=false;
	Last=LastObject;
	if(LastObject==1)
	{
		First=Last;
		FirstObject=LastObject;
	}
	else
	{
		First=1;
		while((ObjList[First].Sortable==false) && (First<Last))
			++First;
		FirstObject=1;
		while((ObjList[FirstObject].Mirror==true) && (FirstObject<LastObject))
		{		
			++FirstObject;
			ReflSurface=true;
		}
	}
	NumMirrors=FirstObject-1;
	if(First==Last)
		Sorting=false;
	else
		Sorting=true;
}


void SwapStrings(Name A, Name B)
{
	Name T;

	strcpy(T, A);
	strcpy(A, B);
	strcpy(B, T);
}

void SwapRealNum(float *A, float *B)
{
	float T;
	
	T=*A;
	*A=*B;
	*B=T;
}

void SwapByteNum(Byte *A, Byte *B)
{
	Byte T;
	
	T=*A;
	*A=*B;
	*B=T;
}

void SwapBoolean(Boolean *A, Boolean *B)
{
	Boolean T;

	T=*A;
	*A=*B;
	*B=T;
}

void SwapData()
{
	SwapSrings(ObjList[Index].ObjectName, ObjList[Index+1].ObjectName);
	SwapRealNum(&ObjList[Index].Tx, &ObjList[Index+1].Tx);
	SwapRealNum(&ObjList[Index].Ty, &ObjList[Index+1].Ty);
	SwapRealNum(&ObjList[Index].Tz, &ObjList[Index+1].Tz);
	SwapRealNum(&ObjList[Index].Rx, &ObjList[Index+1].Rx);
	SwapRealNum(&ObjList[Index].Ry, &ObjList[Index+1].Ry);
	SwapRealNum(&ObjList[Index].Rz, &ObjList[Index+1].Rz);
	SwapRealNum(&ObjList[Index].Sx, &ObjList[Index+1].Sx);
	SwapRealNum(&ObjList[Index].Sy, &ObjList[Index+1].Sy);
	SwapRealNum(&ObjList[Index].Sz, &ObjList[Index+1].Sz);
	SwapBoolean(&ObjList[Index].Reflection, &ObjList[Index+1].Reflection);
	SwapByteNum(&ObjList[Index].Color, &ObjList[Index+1].Color);
	SwapBoolean(&ObjList[Index].Sortable, &ObjList[Index+1].Sortable);
	SwapBoolean(&ObjList[Index].Mirror, &ObjList[Index+1].Mirror);
}


void CheckForSwap(float v, float a, float b)
{
	if(v>=0.0)
	{
		if(a<b)
			SwapData();
	}
	else
	{
		if(a>b)
			SwapData();
	}
}

void OrderX()
{
	for(i=First; i<Last; i++)
	{
		for(Index=First; Index<Last; Index++)
			CheckForSwap(View[0], ObjList[Index].Tx, ObjList[Index+1].Tx);
	}
}

void OrderY()
{
	for(i=First; i<Last; i++)
	{
		for(Index=First; Index<Last; Index++)
			CheckForSwap(View[1], ObjList[Index].Ty, ObjList[Index+1].Ty);
	}
}

void OrderZ()
{
	for(i=First; i<Last; i++)
	{
		for(Index=First; Index<Last; Index++)
			CheckForSwap(View[2], ObjList[Index].Tz, ObjList[Index+1].Tz);
	}
}

void SortObjectsBackToFront()
{
	float x, y, z;

	x=fabs(View[0]);
	y=fabs(View[1]);
	z=fabs(View[2]);
	if((x>y) && (x>z))
		OrderX();
	else
	{
		if((y>x) && (y>z))
			OrderY();
		else
			OrderZ();
	}
}

void SwapDown(float a, float b)
{
	if(a>b)
		SwapData();
}

void SortTopToBottom()
{
	for(i=First; i<Last; i++)
	{
		for(Index=First; Index<Last; Index++)
			SwapDown(ObjList[Index].Tz, ObjList[Index+1].Tz);
	}
}

void SwapUp(float a, float b)
{
	if(a<b)
		SwapData();
}

void SortBottomToTop()
{
	for(i=First; i<Last; i++)
	{
		for(Index=First; Index<Last; Index++)
			SwapUp(ObjList[Index].Tz, ObjList[Index+1].Tz);
	}
}

void CheckForSwap2(float v, float a, float b)
{
	if(v>=0.0)
	{
		if(a>b)
			SwapData();
	}
	else
	{
		if(a<b)
			SwapData();
	}
}

void Order_Y()
{
	for(i=First; i<Last; i++)
	{
		for(Index=First; Index<Last; Index++)
			CheckForSwap2(View[1], ObjList[Index].Ty, ObjList[Index+1].Ty);
	}
}

void SortObjectsFrontToBackInY()
{
	Order_Y();
}

void Order_X()
{
	for(i=First; i<Last; i++)
	{
		for(Index=First; Index<Last; Index++)
			CheckForSwap2(View[0], ObjList[Index].Tx, ObjList[Index+1].Tx);
	}
}

void SortObjectsFrontToBackInX()
{
	Order_X();
}


void PreviewVerticies(Byte Color)
{
	float x, y, z;
	TDA Pt;
	for(FacetNum=1; FacetNum<=LastFacet; FacetNum++)
	{
		for(VertexNumInFacet=1; VertexNumInFacet<=LastVertexNumInFacet; VertexNumInFacet++)
		{
			VertexNum=Facet[(FacetNum*5)+VertexNumInFacet];
			VecScalMultI(InvScaleImage, Vertex[VertexNum], Pt);
			UnVec(Pt, &x, &y, &z);
			CartesianPlot3D(x, y, z, ((MaxInten+1)*(Color-1)+MaxInten));
		}
	}
}

void WireFrameDiagram(Byte Color)
{
	VolexArray Face3d;
	PixelArray Face2d;

	for(FacetNum=1; FacetNum<=LastFacet; FacetNum++)
	{
		for(VertexNumInFacet=1; VertexNumInFacet<=LastVertexNumInFacet; VertexNumInFacet++)
		{
			VertexNum=Facet[(FacetNum*5)+VertexNumInFacet];
			VecScalMultI(InvScaleImage, Vertex[VertexNum], Face3d[VertexNumInFacet]);
		}
		if(Visible(Face3d))
		{
			GetProjectedCroods(Face3d, Face2d);
			PutFacet(Face2d, 1, BLACK);
			PutWireFacet(Face2d, ((MaxInten+1)*(Color-1)+MaxInten));
		}
	}
}

void PlaceFacet(Boolean MirX, Boolean MirY, Boolean MirZ, Byte Color)
{
	Byte Intens;
	VolexArray Face3d;
	PixelArray Face2d;

	MirrorX=MirX;
	MirrorY=MirY;
	MirrorZ=MirZ;
	for(VertexNumInFacet=1; VertexNumInFacet<=LastVertexNumInFacet; VertexNumInFacet++)
	{
		VertexNum=Facet[(FacetNum*5)+VertexNumInFacet];
		VecScalMultI(InvScaleImage, Vertex[VertexNum], Face3d[VertexNumInFacet]);
	}
	if(Visible [Face3d])
	{
		Intens=Intensity();
		if(Intens>0)
		{
			GetProjectedCroods(Face3d, Face2d);
			PutFacet2(Face2d, Color, Intens);
		}
	}
}

void SolidModelDiagram(Byte Color)
{
	for(FacetNum=1; FacetNum<=LastFacet; FacetNum++)
	{
		if((!(Reflect) && (!(ZReeflectedObject)) && (!(YReflectedObject)) && (!(XReflectedObject)))
			PlaceFacet(false, false, false, Color);
		else
		{
			if(ZReflectedObject)
				PlaceFacet(false, false, true, Color);
			else
			{
				if(YReflectedObject)
					PlaceFacet(false, true, false, Color);
				else
				{
					if(XReflectedObject)
						PlaceFacet(true, false, false, Color);
				}
			}
		}
	}
}

void PlaceObjectOnScreen(Byte Color)
{
	if(Preview)
		PreviewVerticies(Color);
	if(WireFrame)
		WireFrameDiagram(Color);
	if((SolidModel) && (!(Preview)) && (!(WireFrame)))
		SolidModelDiagram(Color);
}


void DisplayReflectiveSurfaces()
{
	strset(LastObjectName, 0);
	ReflectedObjects=false;
	Reflect=false;
	for(ObjectNum=1; ObjectNum<=FirstObject; ObjectNum++)
	{
		if(strcmp(ObjList[ObjectNum].ObjectName, LastObjectName)!=0)
		{
			InitVertexBuffer();
			LoadData(ObjList[ObjectNum].ObjectName);
		}
		if(ObjList[ObjectNum].Mirror)
		{
			ReflectedObjects=true;
			Mirroring=true;
			AffineTransformation(ObjList[ObjectNum].Tx, ObjList[ObjectNum].Ty, ObjList[ObjectNum].Tz, ObjList[ObjectNum].Sx, ObjList[ObjectNum].Sy, ObjList[ObjectNum].Sz, ObjList[ObjectNum].Rx, ObjList[ObjectNum].Ry, ObjList[ObjectNum].Rz);
			PlaceObjectOnScreen(ObjList[ObjectNum].Color);
			InvAffineTransformation(ObjList[ObjectNum].Tx, ObjList[ObjectNum].Ty, ObjList[ObjectNum].Tz, ObjList[ObjectNum].Sx, ObjList[ObjectNum].Sy, ObjList[ObjectNum].Sz, ObjList[ObjectNum].Rx, ObjList[ObjectNum].Ry, ObjList[ObjectNum].Rz);
		}
	 	else
			Mirroring=false;
		strcpy(LastObjectName, ObjList[ObjectNum].ObjectName);
	}
}

void DisplayReflections()
{
	for(ObjectNum=FirstObject; ObjectNum<=LastObject; ObjectNum++)
	{
		if(strcmp(ObjList[ObjectNum].ObjectName, LastObjectName)!=0)
		{
			InitVertexBuffer();
			LoadData(ObjList[ObjectNum].ObjectName);
		}
		if(ObjList[ObjectNum].Reflection) && (!(Preview)) && (!(WireFrame)))
		{
			Reflect=true;
			Mirroring=ObjList[ObjectNum].Mirror;
			AffineTransformation(ObjList[ObjectNum].Tx, ObjList[ObjectNum].Ty, ObjList[ObjectNum].Tz, ObjList[ObjectNum].Sx, ObjList[ObjectNum].Sy, ObjList[ObjectNum].Sz, ObjList[ObjectNum].Rx, ObjList[ObjectNum].Ry, ObjList[ObjectNum].Rz);
			PlaceObjectOnScreen(ObjList[ObjectNum].Color);
			InvAffineTransformation(ObjList[ObjectNum].Tx, ObjList[ObjectNum].Ty, ObjList[ObjectNum].Tz, ObjList[ObjectNum].Sx, ObjList[ObjectNum].Sy, ObjList[ObjectNum].Sz, ObjList[ObjectNum].Rx, ObjList[ObjectNum].Ry, ObjList[ObjectNum].Rz);
		}
		else
			Reflect=false;
		strcpy(LastObjectName, ObjList[ObjectNum].ObjectName);
	}
}

void DisplayActualImages()
{
	for(ObjectNum=FirstObject; ObjectNum<=LastObject; ObjectNum++)
	{
		if(strcmp(ObjList[ObjectNum].ObjectName, LastObjectName)!=0)
		{
			InitVertexBuffer();
			LoadData(ObjList[ObjectNum].ObjectName);
		}
		if(!((ObjectNum==1) && ObjList[ObjectNum].Mirror))
		{
			Reflect=false;
			Mirroring=ObjList[ObjectNum].Mirror;
			AffineTransformation(ObjList[ObjectNum].Tx, ObjList[ObjectNum].Ty, ObjList[ObjectNum].Tz, ObjList[ObjectNum].Sx, ObjList[ObjectNum].Sy, ObjList[ObjectNum].Sz, ObjList[ObjectNum].Rx, ObjList[ObjectNum].Ry, ObjList[ObjectNum].Rz);
			PlaceObjectOnScreen(ObjList[ObjectNum].Color);
			InvAffineTransformation(ObjList[ObjectNum].Tx, ObjList[ObjectNum].Ty, ObjList[ObjectNum].Tz, ObjList[ObjectNum].Sx, ObjList[ObjectNum].Sy, ObjList[ObjectNum].Sz, ObjList[ObjectNum].Rx, ObjList[ObjectNum].Ry, ObjList[ObjectNum].Rz);
		}
		strcpy(LastObjectName, ObjList[ObjectNum].ObjectName);
	}
}

void DefineReflection(Boolean XRef, Boolean YRef, Boolean ZRef)
{
	XReflectedObject=XRef;
	YReflectedObject=YRef;
	ZReflectedObject=ZRef;
}

void DisplayObjectInScene()
{
	PrepareSort();
	DefineReflection(false,false, false);
	if(Sorting)
		SortObjectsBackToFront();
	DisplayReflectiveSurfaces();
	if((!(Preview)) && (!(WireFrame)) && ReflSurface)
	{
		DefineReflection(false, false, true);
		if(Sorting && VerticalSort)
			SortTopToBottom();
		if(ReflectedObjects)
			DisplayReflections();
		if(NumMirrors>1)
		{
			DefineReflection(false, true, false);
			if(Sorting)
				SortObjectsFrontToBackInY();
			if(Sorting && VerticalSort)
				SortBottomToTop();
			if(ReflectedObjects)
				DisplayReflections();
			DefineReflection(true, false, false);
			if(Sorting)
				SortObjectsFrontToBackInX();
			if(Sorting && VerticalSort)
				SortBottomToTop();
			if(ReflectedObjects)
				DisplayReflections();
		}
	}
	DefineReflection(false, false, false);
	if(Soring)
		SortObjectBackToFront();
	if(Sortint && VerticalSort)
		SortBottomToTop();
	DisplayActualImages();
}





