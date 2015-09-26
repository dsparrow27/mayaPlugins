#ifndef aimConstraint_H
#define aimConstraint_H

#include <maya/MPxNode.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnUnitAttribute.h>
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
		static MObject aInputTranslateX;
		/*
		This is the y attribute of the input translate
		*/
		static MObject aInputTranslateY;
		/*
		This is the z attribute of the input translate
		*/
		static MObject aInputTranslateZ;
		/*
		This is the array attribute of the input translate
		*/
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
		static MObject aOutputRotate;
		/*
		This is the input matrix used for the driver of the constraint
		*/
		static MObject aDriverMatrix;
		/*
		This is the input matrix used for the upVector of the constraint
		*/
		static MObject aUpVectorMatrix;

};	

#endif // !aimConstraint_H
