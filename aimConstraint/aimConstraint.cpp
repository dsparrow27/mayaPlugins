#include "aimConstraint.h"


MTypeId AimConstraint::id(0x00124506);


void* AimConstraint::creator()
{
	return new AimConstraint();
}


MStatus AimConstraint::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus	status;

	return MS::kSuccess;

}


MStatus AimConstraint::initialize()
{
	MStatus status;
	return MS::kSuccess;
}

