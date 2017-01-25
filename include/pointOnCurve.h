/* 
This node computes the position and rotation by using the curve length
*/
#pragma once

#include "utils.h"


#include "maya/MGlobal.h"
#include "maya/MPxNode.h"
#include "maya/MDataBlock.h"
#include "maya/MFnDependencyNode.h"
#include "maya/MFnNumericAttribute.h"
#include "maya/MFnTypedAttribute.h"
#include "maya/MFnUnitAttribute.h"
#include "maya/MFnCompoundAttribute.h"
#include "maya/MFnMatrixAttribute.h"
#include "maya/MTransformationMatrix.h"
#include "maya/MFnEnumAttribute.h"
#include "maya/MEulerRotation.h"
#include "maya/MFnNurbsCurve.h"
#include "maya/MPointArray.h"
#include "maya/MVector.h"
#include "maya/MDataHandle.h"
#include "maya/MMatrix.h"

class PointOnCurve : public MPxNode
{
public:
		virtual void postConstructor();
		virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
		static void* creator() { return new PointOnCurve(); };
		virtual const int schedulingType() { return kParallel; };
		static MStatus initialize();
		static MTypeId kId;
		static MString kName;

		//attribute values that get accessed in the compute function
		static MObject aInputValue;
		static MObject aInputCurve;
		static MObject aOutPosition;
		static MObject aUseRotation;
		static MObject aUpVectorMatrix;
		static MObject aRotationOrder;
		static MObject aOutRotationOrder;
		static MObject aOutRotation;
			static MObject aOutRotationX;
			static MObject aOutRotationY;
			static MObject aOutRotationZ;


};
