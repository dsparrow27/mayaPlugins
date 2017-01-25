#pragma once

#include "utils.h"

#include "maya/MMatrix.h"
#include "maya/MDataBlock.h"
#include "maya/MDataHandle.h"
#include "maya/MFnMatrixAttribute.h"
#include "maya/MFnNumericAttribute.h"
#include "maya/MPxNode.h"


class ParentDual :public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& datablock);
	static void* creator() { return new ParentDual; };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();
	static MTypeId kId;
	static MString kName;

	static MObject aParentInverse;
	static MObject blend;
	static MObject aMatrixInA;
	static MObject aMatrixInB;
	static MObject aRotationOrder;

	static MObject aOutSrt;
		static MObject aOutRotate;
		static MObject aOutRotateX;
		static MObject aOutRotateY;
		static MObject aOutRotateZ;
		static MObject aOutTranslate;
		static MObject aOutScale;
		static MObject aOutRotationOrder;
};	