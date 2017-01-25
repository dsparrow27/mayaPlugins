#pragma once

#include <maya/MPxNode.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MFnNurbsCurve.h>
#include <maya/MMatrix.h>
#include <maya/MVector.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MEulerRotation.h>

class AimNode : public MPxNode
{
public:
		//standard node creation functions
		static void*	creator();
		static MStatus	initialize();


		//main compute function
		virtual	MStatus compute(const MPlug& plug, MDataBlock& dataBlock);


public:
		// node id 
		static MTypeId kId;
		static MString kName;
		static MObject aInputTranslate;

		/*
		This is the x attribute of the output rotate
		*/
		static MObject aOutputRotateX;
		/*
		This is the y attribute of the output rotate
		*/
		static MObject aOutputRotateY;
		/*
		This is the z attribute of the output rotate
		*/
		static MObject aOutputRotateZ;
		/*
		This is the array attribute of the output rotate
		*/
		static MObject aOutputRotate;
		/*
		This is the input matrix used for the driver of the constraint
		*/
		static MObject aDriverMatrix;
		/*
		This is the input matrix used for the upVector of the constraint
		*/
		static MObject aUpVectorMatrix;
		/*
		 This attribute is for the parentInverse matrix so that parenting can happen
		*/
		static MObject aParentInverseMatrix;

};	
