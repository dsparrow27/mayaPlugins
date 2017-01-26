#pragma once

#include "utils.h"

#include "maya/MMatrix.h"
#include "maya/MDataBlock.h"
#include "maya/MDataHandle.h"
#include "maya/MFnMatrixAttribute.h"
#include "maya/MFnNumericAttribute.h"
#include "maya/MFnEnumAttribute.h"
#include "maya/MFnUnitAttribute.h"
#include "maya/MFnCompoundAttribute.h"
#include "maya/MEulerRotation.h"
#include "maya/MPxNode.h"


class MatrixBlend :public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& datablock);
	static void* creator() { return new MatrixBlend; };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();
	static MTypeId kId;
	static MString kName;


	static MObject aBlend;
	static MObject aMatrixInA;
	static MObject aMatrixInB;
	static MObject aRotationOrder;

	static MObject aOutMatrix;
	static MObject aOutRotationOrder;

};	