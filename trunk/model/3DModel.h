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
/*******      3dModel.h     Constants and Structs            ********/
/********************************************************************/
#ifndef _3DMODEL_H_
#define _3DMODEL_H_


#define NumVerticiesInFacet 4
#define MaxVertexNumInFacet 4
#define ScaleData 23000
#define ScaleImage 100

#define MaxFacet 3600
#define MaxVertex 3721

int LastVertex, LastFacet;
int LastVertexNumInFacet;
int VertexNum, FacetNum;
int VertexNumInFacet;
TDIA Vertex[MaxVertex+1];
static int far *Facet;

float InvScaleData, InvScaleImage;

typedef char Name[20];

FILE *DiskFile;
Name FileName;


typedef struct{
	int x;
	int y;
	}PixelVector;

typedef PixelVector PixelArray[NumVerticiesInFacet+2];
typedef TDA VoxelArray[NumVerticiesInFacet+1];

void InitVertexBuffer();
void LoadData(Name FileName);
void SaveData(Name FileName);
void PutWireFacet(PixelArray Pts, Byte Color);
void PutFacet(PixelArray Face2d, Byte Color, Byte Intens);



#endif
