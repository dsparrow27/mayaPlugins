#include "curvePathArray.h"


MTypeId CurvePathArray::id(0x00124506);


void* CurvePathArray::creator()
{
	return new CurvePathArray();
}


MStatus CurvePathArray::compute(const MPlug& plug, MDataBlock& dataBlock)
{	
	MStatus	status;
	return MS::kSuccess;

}


MStatus CurvePathArray::initialize()
{
	MStatus status;
	return MS::kSuccess;
}

