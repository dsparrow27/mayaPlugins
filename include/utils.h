#pragma once

#include "maya/MTransformationMatrix.h"
#include "maya/MFnNumericData.h"
#include "maya/MFnTypedAttribute.h"
#include "maya/MFnNumericAttribute.h"
#include "maya/MString.h"
#include "maya/MVector.h"
#include "maya/MQuaternion.h"
namespace utils
{
	MTransformationMatrix::RotationOrder rotationOrderByIndex(int rotOrder);
	float remap(float value, float oldMin, float oldMax, float newMin, float newMax);
	bool almostEqual(float x, float y, int tailCount);
	MVector lerp(MVector goal, MVector current, float blend);
	float lerp(float goal, float current, float blend);
	MQuaternion slerp(MQuaternion qa, MQuaternion qb, double blend);
	double dot(MQuaternion qa, MQuaternion qb);
};
