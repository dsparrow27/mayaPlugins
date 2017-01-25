#include "ParentDual.h"

MObject ParentDual::aParentInverse;
MObject ParentDual::aMatrixInA;
MObject ParentDual::aMatrixInB;
MObject ParentDual::blend;
MObject ParentDual::aRotationOrder;
MObject ParentDual::aOutRotationOrder;

MObject ParentDual::aOutSrt;
	MObject ParentDual::aOutRotate;
		MObject ParentDual::aOutRotateX;
		MObject ParentDual::aOutRotateY;
		MObject ParentDual::aOutRotateZ;
	MObject ParentDual::aOutTranslate;
	MObject ParentDual::aOutScale;


void ParentDual::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus ParentDual::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;
	return status;
}

