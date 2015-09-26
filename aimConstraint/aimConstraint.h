#ifndef aimConstraint_H
#define aimConstraint_H

#include <maya/MPxNode.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnNurbsCurve.h>
#include <maya/MPoint.h>
#include <maya/MMatrix.h>
#include <maya/MVector.h>
#include <maya/MFnMatrixAttribute.h>

class AimConstraint : public MPxNode
{
public:
		//standard node creation functions
		static void*	creator();
		static MStatus	initialize();


		//main compute function
		virtual	MStatus compute(const MPlug& plug, MDataBlock& dataBlock);


public:
		// node id 
		static MTypeId id;
		/*
			This is the x attribute of the input translate 
		*/
		static MObject inputTranslateX;
		/*
		This is the y attribute of the input translate
		*/
		static MObject inputTranslateY;
		/*
		This is the z attribute of the input translate
		*/
		static MObject inputTranslateZ;
		/*
		This is the array attribute of the input translate
		*/
		static MObject inputTranslate;

		/*
		This is the x attribute of the output rotate
		*/
		static MObject outputRotateX;
		/*
		This is the y attribute of the output rotate
		*/
		static MObject outputRotateY;
		/*
		This is the z attribute of the output rotate
		*/
		static MObject outputRotateZ;
		/*
		This is the input matrix used for the driver of the constraint
		*/
		static MObject driverMatrix;
		/*
		This is the input matrix used for the upVector of the constraint
		*/
		static MObject upVectorMatrix;

};	

#endif // !aimConstraint_H
