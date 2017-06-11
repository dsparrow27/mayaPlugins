#pragma once

#include "maya/MTransformationMatrix.h"
#include "maya/MFnNumericData.h"
#include "maya/MFnTypedAttribute.h"
#include "maya/MFnNumericAttribute.h"
#include "maya/MString.h"
#include "maya/MVector.h"
#include "maya/MQuaternion.h"

#define AS_INPUT(attr)        \
    attr.setKeyable(true);      \
    attr.setChannelBox(true);  \
    attr.setStorable(true);     \
    attr.setWritable(true);     \
	attr.setConnectable(true);

#define AS_OUTPUT(attr)       \
    attr.setKeyable(false);     \
    attr.setChannelBox(false);  \
    attr.setStorable(true);    \
    attr.setWritable(false);    \
	attr.setConnectable(true);

namespace utils
{
	MTransformationMatrix::RotationOrder rotationOrderByIndex(int rotOrder);
	float remap(float value, float oldMin, float oldMax, float newMin, float newMax);
	bool almostEqual(float x, float y, int tailCount);
	MVector lerp(MVector goal, MVector current, float blend);
	float lerp(float goal, float current, float blend);
	double lerp(double goal, double current, double blend);
	MQuaternion slerp(MQuaternion qa, MQuaternion qb, float blend);
	double dot(MQuaternion qa, MQuaternion qb);
	MQuaternion aimVector(MVector sourcePosition, MVector targetPosition, MVector aimVector, MVector upVector);
};
