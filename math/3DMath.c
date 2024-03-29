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
	  

/* In order to have OS independent Math functions   */
/* We have written our own math functions to use    */
/* and developed our own Math Library we can port   */
/* across to any type of platform with less problem */


#include "3DMath.h"                               

int Round(float x)
{
	return((int)(x+0.5));
}

int Trunc(float x)
{
	return ((int)(x));
}

float SqrFP(float x)
{
	return (x*x);
}

int Sqr(int x)
{
	return (x*x);
}

float Radians(float Angle)
{
	return(Angle*PiOver180);
}

float Degrees(float Angle)
{
	return(Angle*PiUnder180);
}

float CosD(float Angle)
{
	return(cos(Radians(Angle)));
}

float SinD(float Angle)
{
	return(sin(Radians(Angle)));
}

float Power(float Base, int Exponent)
{
	float BPower;
	int   t;

	if(Exponent == 0)
	{
		return(1);
	}
	else
	{
		BPower = 1.0;
		for(t=1; t<=Exponent; t++)
		{
			BPower*=Base;
		}
		return(BPower);
	}
}


float Log(float x)
{
	return(log(x)/Ln10);
}

float Exp10(float x)
{
	return(exp(x*Ln10));
}

float Sign(float x)
{
	if(x<0)
		return(-1);
	else
	{
		if(x>0)
			return(1);
		else
		{
			return(0);
		}
	}
}

int IntSign(int x)
{
	if(x<0)
		return(-1);
	else
	{
		if(x>0)
			return(1);
		else
		{
			return(0);
		}
	}
}

int IntSqrt(int x)
{
	int OddInt, OldArg, FirstSqrt;

	OddInt=1;
	OldArg=x;
	while(x>=0)
	{
		x-=OddInt;
		OddInt+=2;
	}
	FirstSqrt= OddInt >> 1;
	if((Sqr(FirstSqrt) - FirstSqrt + 1) > OldArg)
		return(FirstSqrt -1);
	else
		return(FirstSqrt);
}

int IntPower(int Base, int Exponent)
{
	if(Exponent == 0)
	{
		return(1);
	}
	else
		return(Base*IntPower(Base, Exponent -1));
}

/* Maths have Vector and Matrix Routines */
/* We have to implement Matrix functions */
/* as 3D representation needs all matrix */
/* functionality been available          */


void Vec(float r, float s, float t, TDA A)
{
	A[0]=r;
	A[1]=s;
	A[2]=t;
}

void VecInt(int r, int s, int t,TDIA A)
{
	A[0]=r;
	A[1]=s;
	A[2]=t;
}

void UnVec(TDA A, float *r,float *s,float *t)
{
	*r=A[0];
	*s=A[1];
	*t=A[2];
}

void UnVecInt(TDIA A, int *r,int *s,int *t)
{
	*r=A[0];
	*s=A[1];
	*t=A[2];
}

float VecDot(TDA A,TDA B)
{
	return(A[0]*B[0] + A[1]*B[1] + A[2]*B[2]);
}

void VecCross(TDA A,TDA B,TDA C)
{
	C[0]=A[1]*B[2] - A[2]*B[1];
	C[1]=A[2]*B[0] - A[0]*B[2];
	C[2]=A[0]*B[1] - A[1]*B[0];
}

float VecLen(TDA A)
{
	return(sqrt(SqrFP(A[0])+SqrFP(A[1])+SqrFP(A[2])));
}

void VecNormalize(TDA A)
{
	float dist, invdist;

	dist=VecLen(A);
	 if(!(dist == 1.0))
	{
		invdist = 1/dist;
		A[0]*=invdist;
		A[1]*=invdist;
		A[2]*=invdist;
	}
	else
	{
		printf("Zero Length Vectors cannot be Normalized");
/*		exit(1); */
	}
}

void VecMatxMult(FDA A, Matx4x4 Matrix, FDA B)
{
	int mRow,mCol;

	for(mCol=0; mCol<4; mCol++)
	{
		B[mCol]=0;
		for(mRow=0; mRow<4; mRow++)
		{
			B[mCol]+=A[mRow]*Matrix[mRow][mCol];
		}
	}
}

void VecSub(TDA A, TDA B, TDA C)
{
	C[0] = A[0] - B[0];
	C[1] = A[1] - B[1];
	C[2] = A[2] - B[2];
}

void VecSubInt(TDIA A, TDIA B, TDA C)
{
	C[0] = A[0] - B[0];
	C[1] = A[1] - B[1];
	C[2] = A[2] - B[2];
}

void VecAdd(TDA A, TDA B, TDA C)
{
	C[0] = A[0] + B[0];
	C[1] = A[1] + B[1];
	C[2] = A[2] + B[2];
}

void VecAdd3(TDA A, TDA B, TDA C,TDA D)
{
	D[0] = C[0] + A[0] + B[0];
	D[1] = C[1] + A[1] + B[1];
	D[2] = C[2] + A[2] + B[2];
}

void VecCopy(TDA A, TDA B)
{
	int i;
	for(i=0; i<3; i++)
	{
		B[i] = A[i];
	}
}

void VecLinComb(float r, TDA A, float s,TDA B, TDA C)
{
	C[0]=r*A[0]+s*B[0];
	C[1]=r*A[1]+s*B[1];
	C[2]=r*A[2]+s*B[2];
}

void VecScalMult(float r, TDA A, TDA B)
{
	B[0]=r*A[0];
	B[1]=r*A[1];
	B[2]=r*A[2];
}

void VecScalMultI(float r, TDIA A, TDA B)
{
	B[0]=r*A[0];
	B[1]=r*A[1];
	B[2]=r*A[2];
}

void VecScalMultInt(float r, TDA A, TDIA B)
{
	B[0]=Round(r*A[0]);
	B[1]=Round(r*A[1]);
	B[2]=Round(r*A[2]);
}

void VecAddScalMult(float r, TDA A, TDA B, TDA C)
{
	C[0]=r*A[0]+B[0];
	C[1]=r*A[1]+B[1];
	C[2]=r*A[2]+B[2];
}

void VecNull(TDA A)
{
	A[0]=0.0;
	A[1]=0.0;
	A[2]=0.0;
}

void VecNullInt(TDIA A)
{
	A[0]=0;
	 A[1]=0;
	 A[2]=0;
}

void VecElemMult(float r, TDA A, TDA B, TDA C)
{
	C[0]=r*A[0]*B[0];
	C[1]=r*A[1]*B[1];
	C[2]=r*A[2]*B[2];
}


/* Transformation Routines */

void ZeroMatrix(Matx4x4 A)
{
	int i,j;

	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			A[i][j]=0.0;
		}
	}
}

void Translate3D(float tx, float ty,float tz,Matx4x4 A)
{
	int i;

	ZeroMatrix(A);
	for(i=0; i<4; i++)
		A[i][i] = 1.0;
	A[0][3]=-tx;
	A[1][3]=-ty;
	A[2][3]=-tz;
}

void Scale3D(float sx,float sy,float sz, Matx4x4 A)
{
	ZeroMatrix(A);
	A[0][0]=sx;
	A[1][1]=sy;
	A[2][2]=sz;
	A[3][3]=1.0;
}

void Rotate3D(int m, float Theta, Matx4x4 A)
{
	int m1,m2;
	float c,s;

	ZeroMatrix(A);
	A[m-1][m-1]=1.0;
	A[3][3]=1.0;
	m1=(m%3)+1;
	m2=(m1%3);
	m1-=1;
	c=CosD(Theta);
	s=SinD(Theta);
	A[m1][m1]=c;
	A[m1][m2]=s;
	A[m2][m2]=c;
	A[m2][m1]=-s;
}

void Multiply3DMatricies(Matx4x4 A, Matx4x4 B, Matx4x4 C)
{
	int i,j,k;
	float ab;

	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			ab=0;
			for(k=0; k<4; k++)
				ab+=A[i][k]*B[k][j];
			C[i][j]=ab;
		}
	}
}

void MatCopy(Matx4x4 a, Matx4x4 b)
{
	Byte i,j;

	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
			b[i][j]=a[i][j];
	}
}


void PrepareMatrix(float Tx, float Ty, float Tz,
					float Sx, float Sy, float Sz,
					float Rx, float Ry, float Rz,
					Matx4x4 XForm)
{
	Matx4x4 M1,M2,M3,M4,M5,M6,M7,M8,M9;

	Scale3D(Sx,Sy,Sz,M1);
	Rotate3D(1,Rx,M2);
	Rotate3D(2,Ry,M3);
	Rotate3D(3,Rz,M4);
	Translate3D(Tx,Ty,Tz,M5);
	Multiply3DMatricies(M2,M1,M6);
	Multiply3DMatricies(M3,M6,M7);
	Multiply3DMatricies(M4,M7,M8);
	Multiply3DMatricies(M5,M8,M9);
	MatCopy(M9,XForm);
}

void PrepareInvMatrix(float Tx,float Ty,float Tz,
					  float Sx,float Sy,float Sz,
					  float Rx,float Ry,float Rz,
					  Matx4x4 XForm)
{
	Matx4x4 M1,M2,M3,M4,M5,M6,M7,M8,M9;

	Scale3D(Sx,Sy,Sz,M1);
	Rotate3D(1,Rx,M2);
	Rotate3D(2,Ry,M3);
	Rotate3D(3,Rz,M4);
	Translate3D(Tx,Ty,Tz,M5);
	Multiply3DMatricies(M4,M5,M6);
	Multiply3DMatricies(M3,M6,M7);
	Multiply3DMatricies(M2,M7,M8);
	Multiply3DMatricies(M1,M8,M9);
	MatCopy(M9,XForm);
}

void Transform(TDA A,Matx4x4 M,TDA B)
{
	B[0]=M[0][0]*A[0]+M[0][1]*A[1]+M[0][2]*A[2]+M[0][3];
	B[1]=M[1][0]*A[0]+M[1][1]*A[1]+M[1][2]*A[2]+M[1][3];
	B[2]=M[2][0]*A[0]+M[2][1]*A[1]+M[2][2]*A[2]+M[2][3];
}
