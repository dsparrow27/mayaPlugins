#pragma once

#include "utils.h"

#include "maya/MMatrix.h"
#include "maya/MTransformationMatrix.h"
#include "maya/MEulerRotation.h"
#include "maya/MVector.h"
#include "maya/MDataBlock.h"
#include "maya/MPxNode.h"
#include "maya/MFnNumericAttribute.h"
#include "maya/MFnNumericData.h"
#include "maya/MFnMatrixAttribute.h"
#include "maya/MFnUnitAttribute.h"
#include "maya/MFnEnumAttribute.h"
#include "maya/MFnCompoundAttribute.h"

class ParentSingle : public MPxNode
{

public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new ParentSingle; };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();
	static MTypeId kId;
	static MString kName;

	static MObject aParentInverse;
	static MObject aOffsetMatrix;
	static MObject aWorldMatrix;
	static MObject aRotationOrder;
	static MObject aNegateX;
	static MObject aNegateY;
	static MObject aNegateZ;

	// outputs
	static MObject aOutRotationOrder;
	static MObject aOutMatrix;
	//compound to house all other outputs
	static MObject aOutSrt;
	
		static MObject aOutRotate;
			static MObject aOutRotateX;
			static MObject aOutRotateY;
			static MObject aOutRotateZ;
		static MObject aOutTranslate;
			static MObject aOutTranslateX;
			static MObject aOutTranslateY;
			static MObject aOutTranslateZ;
		static MObject aOutScale;

};