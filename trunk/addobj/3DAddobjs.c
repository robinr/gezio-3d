#include "3DMath.h"
#include "3DGraph.h"
#include "Model.Inc"

#include <string.h>


void InitObjectBuffer()
{
	for(ObjectNum=0; ObjectNum<=NumObjects; ObjectNum++)
	{
		strset(ObjList[ObjectNum].ObjectName, 0);
		ObjList[ObjectNum].Tx=0.0;
		ObjList[ObjectNum].Ty=0.0;
		ObjList[ObjectNum].Tz=0.0;
		ObjList[ObjectNum].Rx=0.0;
		ObjList[ObjectNum].Ry=0.0;
		ObjList[ObjectNum].Rz=0.0;
		ObjList[ObjectNum].Sx=0.0;
		ObjList[ObjectNum].Sy=0.0;
		ObjList[ObjectNum].Sz=0.0;
		ObjList[ObjectNum].Reflection=0.0;
		ObjList[ObjectNum].Color=0;
		ObjList[ObjectNum].Sortable=false;
		ObjList[ObjectNum].Mirror=false;
	}
	ObjectNum=0;
}

void AddObject(Name FileName)
{
	++ObjectNum;
	strcpy(ObjList[ObjectNum].ObjectName, FileName);
	LastObject=ObjectNum;
}

void Scale(float x, float y, float z)
{
	ObjList[ObjectNum].Sx=x;
	ObjList[ObjectNum].Sy=y;
	ObjList[ObjectNum].Sz=z;
}

void Rotate(float x, float y, float z)
{
	ObjList[ObjectNum].Rx=-x;
	ObjList[ObjectNum].Ry=-y;
	ObjList[ObjectNum].Rz=-z;
}

void Translate(float x, float y, float z)
{
	ObjList[ObjectNum].Tx=-x;
	ObjList[ObjectNum].Ty=-y;
	ObjList[ObjectNum].Tz=-z;
}

void ReflectObject(Boolean State)
{
	ObjList[ObjectNum].Reflection=State;
}

void ObjectColor(Byte Col)
{
	ObjList[ObjectNum].Color=Col;
}

void AllowSort(Boolean State)
{
	ObjList[ObjectNum].Sortable=State;
}

void Mirrored(Boolean State)
{
	ObjList[ObjectNum].Mirror=State;
}

void AddEdgeReflectorsAtZero()
{
	EdgeReflectorAtZero=true;

	AddObject("GRID.DAT");
	Scale(100.0, 100.0, 100.0);
	Rotate(0.0, 0.0, 0.0);
	Translate(0.0, 0.0, 0.0);
	ReflectObject(false);
	ObjectColor(7);
	AllowSort(false);
	Mirrored(true);

	AddObject("GRID.DAT");
	Scale(50.0, 100.0, 50.0);
	Rotate(0.0, 90.0, 0.0);
	Translate(-100.0, 0.0, 50.0);
	ReflectObject(false);
	ObjectColor(7);
	AllowSort(false);
	Mirrored(true);

	AddObject("GRID.DAT");
	Scale(100.0, 50.0, 50.0);
	Rotate(-90.0, 0.0, 0.0);
	Translate(0.0, -100.0, 50.0);
	ReflectObject(false);
	ObjectColor(7);
	AllowSort(false);
	Mirrored(true);
}

void AddEdgeReflectors()
{
	EdgeReflector=true;

	AddObject("GRID.DAT");
	Scale(100.0, 100.0, 100.0);
	Rotate(0.0, 0.0, 0.0);
	Translate(0.0, 0.0, -100.0);
	ReflectObject(false);
	ObjectColor(7);
	AllowSort(false);
	Mirrored(true);

	AddObject("GRID.DAT");
	Scale(100.0, 100.0, 100.0);
	Rotate(0.0, 90.0, 0.0);
	Translate(-100.0, 0.0, 0.0);
	ReflectObject(false);
	ObjectColor(7);
	AllowSort(false);
	Mirrored(true);

	AddObject("GRID.DAT");
	Scale(100.0, 100.0, 100.0);
	Rotate(-90.0, 0.0, 0.0);
	Translate(0.0, -100.0, 0.0);
	ReflectObject(false);
	ObjectColor(7);
	AllowSort(false);
	Mirrored(true);
}


Boolean Bool(Strg B)
{
	strupr(B);
	if(!(strcmp(B, "FALSE")))
		return(false);
	else
		return(true);
}

void AddObjectsToSceneFromDiskFile(Name FileName)
{
	int I1, I2, I3, I4;
	float R1, R2, R3;
	Name ObjectFileName;
	char blank[256];
	FILE *TextDiskFile;
	int L1;
	Strg B;

	strcat(FileName, ".SCN");
	TextDiskFile=fopen(FileName, "r+t");
	fgets(blank, 255, TextDiskFile);
	fgets(blank, 255, TextDiskFile);
	fscanf(TextDiskFile, "%s %d %d %d %d", B, &I1, &I2, &I3, &I4);
	InitPerspective(Bool(B), I1, I2, I3, I4);
	fscanf(TextDiskFile, "%d %d", &I1, &I2);
	InitPlotting(I1, I2);
	GetViewVector();
	fscanf(TextDiskFile, "%d %d", &I1, &I2);
	InitLightDirection(I1, I2);
	GetLightVector();
	fscanf(TextDiskFile, "%s", B);
	VertSort(Bool(B));
	fscanf(TextDiskFile, "%s", B);
	if(Bool(B))
		AddEdgeReflectors();
	fscanf(TextDiskFile, "%s", B);
	if(Bool(B))
		AddEdgeReflectorsAtZero();
	do
	{
		strset(ObjectFileName, 0);
		fscanf(TextDiskFile, "%s", ObjectFileName);
		if(ObjectFileName[0]==0)
			goto L1;
		AddObject(ObjectFileName);
		fscanf(TextDiskFile, "%d", &I1);
		ObjectColor(I1);
		fscanf(TextDiskFile, "%f %f %f", &R1, &R2, &R3);
		Scale(R1, R2, R3);
		fscanf(TextDiskFile, "%f %f %f", &R1, &R2, &R3);
		Rotate(R1, R2, R3);
		fscanf(TextDiskFile, "%f %f %f", &R1, &R2, &R3);
		Translate(R1, R2, R3);
		fscanf(TextDiskFile, "%s", B);
		ReflectObject(Bool(B));
		fscanf(TextDiskFile, "%s", B);
		AllowSort(Bool(B));
		fscanf(TextDiskFile, "%s", B);
		Mirrored(Bool(B));
	}while(!(ObjectFileName[0]==0));
	L1: fclose(TextDiskFile);
}

void StackedSpheres()
{
	float r, s;

	r=16.0;
	s=16.0;

	AddObject("SPHERE.DAT");
	Scale(r, r, r);
	Rotate(0.0, 0.0, 0.0);
	Translate(-2.0*r, -r, s+r);
	ReflectObject(true);
	ObjectColor(1);
	AllowSort(true);
	Mirrored(false);

	AddObject("SPHERE.DAT");
	Scale(r, r, r);
	Rotate(0.0, 0.0, 0.0);
	Translate(0.0, -r, s+r);
	ReflectObject(true);
	ObjectColor(2);
	AllowSort(true);
	Mirrored(false);

	AddObject("SPHERE.DAT");
	Scale(r, r, r);
	Rotate(0.0, 0.0, 0.0);
	Translate(2.0*r, -r, s+r);
	ReflectObject(true);
	ObjectColor(3);
	AllowSort(true);
	Mirrored(false);

	AddObject("SPHERE.DAT");
	Scale(r, r, r);
	Rotate(0.0, 0.0, 0.0);
	Translate(-r, 0.886*r, s+r);
	ReflectObject(true);
	ObjectColor(4);
	AllowSort(true);
	Mirrored(false);

	AddObject("SPHERE.DAT");
	Scale(r, r, r);
	Rotate(0.0, 0.0, 0.0);
	Translate(r, 0.866*r, s+r);
	ReflectObject(true);
	ObjectColor(5);
	AllowSort(true);
	Mirrored(false);

	AddObject("SPHERE.DAT");
	Scale(r, r, r);
	Rotate(0.0, 0.0, 0.0);
	Translate(0.0, 2.732*r, s+r);
	ReflectObject(true);
	ObjectColor(6);
	AllowSort(true);
	Mirrored(false);

	AddObject("SPHERE.DAT");
	Scale(r, r, r);
	Rotate(0.0, 0.0, 0.0);
	Translate(-r, -0.293*r, s+2.6*r);
	ReflectObject(true);
	ObjectColor(7);
	AllowSort(true);
	Mirrored(false);

	AddObject("SPHERE.DAT");
	Scale(r, r, r);
	Rotate(0.0, 0.0, 0.0);
	Translate(r, -0.293*r, s+2.6*r);
	ReflectObject(true);
	ObjectColor(1);
	AllowSort(true);
	Mirrored(false);

	AddObject("SPHERE.DAT");
	Scale(r, r, r);
	Rotate(0.0, 0.0, 0.0);
	Translate(0.0, 1.5*r, s+2.6*r);
	ReflectObject(true);
	ObjectColor(2);
	AllowSort(true);
	Mirrored(false);

	AddObject("SPHERE.DAT");
	Scale(r, r, r);
	Rotate(0.0, 0.0, 0.0);
	Translate(0.0, 0.5*r, s+4.4*r);
	ReflectObject(true);
	ObjectColor(3);
	AllowSort(true);
	Mirrored(false);
}

void AddObjectsToSceneFromProcedure()
{
	InitPerspective(true, 0, -25, 450, 500);
	InitPloting(240, 18);
	GetViewVector();
	InitLightDirection(45, 45);
	GetLightVector();
	VertSort(true);
	AddEdgeReflectorsAtZero();
	StackedSpheres();
}








