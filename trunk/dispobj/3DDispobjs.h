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
#ifndef _3DDISPOBJS_H_
#define _3DDISPOBJS_H_


int First;
int Last;
int FirstObject;
Boolean Sorting;
Boolean ReflSurface;
int NumMirrors;
int Index;
int i;
Boolean XReflectedObject;
Boolean yReflectedObject;
Boolean ZReflectedObject;

Name LastObjectName;
Boolean ReflectedObjects;

void PrepareSort();
void SwapStrings(Name A, Name B);
void SwapRealNum(float *A, float *B);
void SwapByteNum(Byte *A, Byte *B);
void SwapBoolean(Boolean *A, Boolean *B);
void SwapData();
void CheckForSwap(float v, float a, float b);
void OrderX();
void OrderY();
void OrderZ();
void SortObjectsBackToFront();
void SwapDown(float a, float b);
void SortTopToBottom();
void SwapUp(float a, float b);
void SortBottomToTop();
void CheckForSwap2(float v, float a, float b);
void Order_Y();
void SortObjectsFrontToBackInY();
void Order_X();
void SortObjectsFrontToBackInX();
void PreviewVerticies(Byte Color);
void WireFrameDiagram(Byte Color);
void PlaceFacet(Boolean MirX, Boolean MirY, Boolean MirZ, Byte Color);
void SolidModelDiagram(Byte Color);
void PlaceObjectOnScreen(Byte Color);
void DisplayReflectiveSurfaces();
void DisplayReflections();
void DisplayActualImages();
void DefineReflection(Boolean XRef, Boolean YRef, Boolean ZRef);
void DisplayObjectInScene();

#endif
