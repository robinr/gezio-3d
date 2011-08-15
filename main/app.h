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

#ifndef _APP_H_
#define _APP_H_


#include "3DMath.h"
#include "3DGraph.h"
#include "3DModel.h"


Boolean Preview;
Boolean WireFrame;
Boolean SolidModel;
Boolean VerticalSort;

#define ViewPhi 270
#define ViewTheta 90

TDA View;
float LightPhi;
float LightTheta;

TDA Light;

TDA SrfNorm;

Boolean Reflect;
Boolean MirrorX;
Boolean MirrorY;
Boolean MirrorZ;

#define XBytes 39

Byte Refl[XBytes+1][MaxY+1];
Boolean Mirroring;

Strg B;

Name SceneFile;

void DoPreview(Boolean State);
void DoWireFrame(Boolean State);
void DoSolidModel(Boolean State);
void VertSort(Boolean Sort);
void DoTransform(Matx4x4 XForm);
void DoInvTransform(Matx4x4 XForm);
void AffineTransformation(float Tx, float Ty, float Tz, float Sx, float Sy, float Sz, float Rx, float Ry, float Rz);
void InvAffineTransformation(float Tx, float Ty, float Tz, float Sx, float Sy, float Sz, float Rx, float Ry, float Rz);
void GetViewVector();
void InitLightDirection(int LgtPhi, int LgtTheta);
void GetLightVector();
void GetSurfaceNormalVector(VoxelArray Face3d);
Byte Intensity();
Boolean Visible(VoxelArray Face3d);
void InitReflectionBuffer();
Boolean Reflected(int x, int y);
void MakeReflected(int x, int y);
void GetProjectedCroods(VoxelArray Face3d, PixelArray Face2d);
void PutFacet2(PixelArray Face2d, Byte Color, Byte Intens);
void GetSceneFile();
void LoadDescAndScene(Name FileName);

#endif