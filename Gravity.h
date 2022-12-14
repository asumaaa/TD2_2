#pragma once
#include "math.h"
#include "cmath"
#define G 6.674	//万有引力定数

class Gravity
{
public:
	void Initialize(float x_,float y_, float z_,float weight_);
	void Update(Gravity g);
public:
	float length(Gravity g);	//	長さを返す
	float VecGetX(Gravity g);	//正規化
	float VecGetY(Gravity g);	//正規化
	float VecGetZ(Gravity g);	//正規化
public:
	float weight;
	float x;		//重力を持たせる点の座標
	float y;
	float z;
	float x2;
	float y2;
	float z2;
	float r;
};

