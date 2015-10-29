/* 
*/
#ifndef curvePathArray_H
#define curvePathArray_H

#include "maya/MGlobal.h"
#include <maya/MPxNode.h>
#include <maya/MDataBlock.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnNurbsCurve.h>
#include <maya/MPointArray.h>
#include <maya/MVector.h>
#include <maya/MDataHandle.h>
#include <maya/MMatrix.h>

class CurvePathArray : public MPxNode
{
public:

		//main compute function
		virtual	MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
		
		//standard node creation function
		static void*	creator();
		static MStatus	initialize();

		// node id 
		static MTypeId id;

		//attribute values that get accessed in the compute function


};

#endif // !curvePathArray_H
