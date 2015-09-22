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

};	

#endif // !aimConstraint_H
