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
/*******      3dMath.h     Constants and Structs             ********/
/********************************************************************/
#ifndef _3DMATH_H_
#define _3DMATH_H_

//#include <stdio.h>
//#include <math.h>
#define Ln10            2.30258509299405E+00
#define Pi              3.1415927
#define PiOver180       1.74532925199433E-002
#define PiUnder180      5.72957795130823E+001

typedef enum {false,true}  Boolean;
typedef unsigned char      Byte;
typedef unsigned int       Word;

typedef float TDA[3];
typedef int   TDIA[3];
typedef float FDA[4];
typedef float Matx4x4[4][4];



/********************************************************************/
/********      3dMath.h    Functions and Interfaces          ********/
/********************************************************************/

int   Round(float x);
int   Trunc(float x);
float SqrFP(float x);
int   Sqr(int x);
float Radians(float Angle);
float Degrees(float Angle);
float CosD(float Angle);
float SinD(float Angle);
float Power(float Base, int Exponent);
float Log(float x);
float Exp10(float x);
float Sign(float x);
int   IntSign(int x);
int   IntSqrt(int x);
int   IntPower(int Base, int Exponent);
void  Vec(float r,float s, float t,TDA A);
void  VecInt(int r, int s, int t,TDIA A);
void  UnVec(TDA A, float *r,float *s,float *t);
void  UnVecInt(TDIA A, int *r,int *s,int *t);
float VecDot(TDA A,TDA B);
void  VecCross(TDA A,TDA B,TDA C);
float VecLen(TDA A);
void  VecNormalize(TDA A);
void  VecMatxMult(FDA A, Matx4x4 Matrix, FDA B);
void  VecSub(TDA A, TDA B, TDA C);
void  VecSubInt(TDIA A, TDIA B, TDA C);
void  VecAdd(TDA A, TDA B, TDA C);
void  VecAdd3(TDA A, TDA B, TDA C,TDA D);
void  VecCopy(TDA A, TDA B);
void  VecLinComb(float r, TDA A, float s,TDA B, TDA C);
void  VecScalMult(float r, TDA A, TDA B);
void  VecScalMultI(float r, TDIA A, TDA B);
void  VecScalMultInt(float r, TDA A, TDIA B);
void  VecAddScalMult(float r, TDA A, TDA B, TDA C);
void  VecNull(TDA A);
void  VecNullInt(TDIA A);
void  VecElemMult(float r, TDA A, TDA B, TDA C);
void  ZeroMatrix(Matx4x4 A);
void  Translate3D(float tx, float ty,float tz,Matx4x4 A);
void  Scale3D(float sx,float sy,float sz, Matx4x4 A);
void  Rotate3D(int m, float Theta, Matx4x4 A);
void  Multiply3DMatricies(Matx4x4 A, Matx4x4 B, Matx4x4 C);
void  MatCopy(Matx4x4 a, Matx4x4 b);
void  PrepareMatrix(float Tx, float Ty, float Tz,
					 float Sx, float Sy, float Sz,
					 float Rx, float Ry, float Rz,
					 Matx4x4 XForm);
void  PrepareInvMatrix(float Tx,float Ty,float Tz,
					 float Sx,float Sy,float Sz,
					 float Rx,float Ry,float Rz,
					 Matx4x4 XForm);
void Transform(TDA A,Matx4x4 M,TDA B);

#endif