#include "aimConstraint.h"


MTypeId AimConstraint::id(0x00124506);

// node id 
MObject AimConstraint::inputTranslateX;
MObject AimConstraint::inputTranslateY;
MObject AimConstraint::inputTranslate;
MObject AimConstraint::outputRotateX;
MObject AimConstraint::outputRotateY;
MObject AimConstraint::outputRotateZ;
MObject AimConstraint::driverMatrix;
MObject AimConstraint::upVectorMatrix;


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

