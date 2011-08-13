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

void InitVertexBuffer()
{
	InvScaleData=1.0/ScaleData;
	InvScaleImage=1.0/ScaleImage;
	for(VertexNum=0; VertexNum<=MaxVertex; VertexNum++)
		VecNullInt(Vertex[VertexNum]);
	for(FacetNum=0; FacetNum<=MaxFacet; FacetNum++)
	{
		for(VertexNumInFacet=0; VertexNumInFacet<=MaxVertexNumInFacet; VertexNumInFacet++)
			Facet[(FacetNum*5) + VertexNumInFacet]=0;
	}
}


void LoadData(Name FileName)
{
	TDIA temp;
	int x, y, z;

	DiskFile=fopen(FileName, "r+b");
	LastVertex=getw(DiskFile);
	LastFacet=getw(DiskFile);
	LastVertexNumInFacet=getw(DiskFile);
	for(VertexNum=1; VertexNum<=LastVertex; VertexNum++)
	{
		x=getw(DiskFile);
		y=getw(DiskFile);
		z=getw(DiskFile);
		if((abs(x)>ScaleData) || (abs(y)>ScaleData) || (abs(z)>ScaleData))
		{
			printf("Error : Data Out Of Range - Vertex #%d\n", VertexNum);
			exit(1);
		}
		else
			VecInt(x, y, z, Vertex[VertexNum]);
	}
	for(FacetNum=1; FacetNum<=LastFacet; FacetNum++)
	{
		for(VertexNumInFacet=1; VertexNumInFacet<=LastVertexNumInFacet; VertexNumInFacet++)
			Facet[(FacetNum*5)+VertexNumInFacet]=getw(DiskFile);
	}
	fclose(DiskFile);
}

void SaveData(Name FileName)
{
	int x, y, z;

	DiskFile=fopen(FileName, "w+b");
	putw(LastVertex, DiskFile);
	putw(LastFacet, DiskFile);
	putw(LastVertexNumInFacet, DiskFile);
	for(VertexNum=1; VertexNum<=LastVertex; VertexNum++)
	{
		UnVecInt(Vertex[VertexNum], &x, &y, &z);
		putw(x, DiskFile);
		putw(y, DiskFile);
		putw(z, DiskFile);
	}
	for(FacetNum=1; FacetNum<=LastFacet; FacetNum++)
	{
		for(VertexNumInFacet=1; VertexNumInFacet<=LastVertexNumInFacet; VertexNumInFacet++)
			putw(Facet[(FacetNum*5)+VertexNumInFacet], DiskFile);
	}
	fclose(DiskFile);
}


void PutWireFacet(PixelArray Pts, Byte Color)
{
	int t;

	for(t=1; t<=4; t++)
		Draw(Pts[t].x, Pts[t].y, Pts[t+1].x, Pts[t+1].y, Color);
}

void PutFacet(PixelArray Face2d, Byte Color, Byte Intens)
{
	int xc, yc;
	int i, x;
	int OldVertNum;
	int VertNum;
	int mnx, mxx;
	int mny, mxy;
	float slope;

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
				PutPixel(xc, yc, Color, Intens);
		}
	}
}

		 