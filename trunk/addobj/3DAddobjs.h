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
/*******      3DAddobjs.h     Constants and Structs            ********/
/********************************************************************/
#ifndef _3DADDOBJS_H_
#define _3DADDOBJS_H_


#define NumObjects 40

int ObjectNum;
int LastObject;

typedef struct{
	Name ObjectName;
	float Tx, Ty, Tz;
	float Rx, Ry, Rz;
	float Sx, Sy, Sz;
	Boolean Reflection;
	Byte Color;
	Boolean Sortable;
	Boolean Mirror;
	}ObjL;

ObjL ObjList[NumObjects+1];
typedef char Strg[80];

Boolean EdgeReflectorAtZero;
Boolean EdgeReflector;

void InitObjectBuffer();
void AddObject(Name FileName);
void Scale(float x, float y, float z);
void Rotate(float x, float y, float z);
void Translate(float x, float y, float z);
void ReflectObject(Boolean State);
void ObjectColor(Byte Col);
void AllowSort(Boolean State);
void Mirrored(Boolean State);
void AddEdgeReflectorsAtZero();
void AddEdgeReflectors();
Boolean Bool(Strg B);
void AddObjectsToSceneFromDiskFile(Name FileName);
void StackedSpheres();
void AddObjectsToSceneFromProcedure();

#endif

