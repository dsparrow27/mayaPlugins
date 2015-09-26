#include "aimConstraint.h"


MTypeId AimConstraint::id(0x00124506);

// node id 
MObject AimConstraint::aInputTranslateX;
MObject AimConstraint::aInputTranslateY;
MObject AimConstraint::aInputTranslateZ;
MObject AimConstraint::aInputTranslate;
MObject AimConstraint::aOutputRotateX;
MObject AimConstraint::aOutputRotateY;
MObject AimConstraint::aOutputRotateZ;
MObject AimConstraint::aOutputRotate;
MObject AimConstraint::aDriverMatrix;
MObject AimConstraint::aUpVectorMatrix;


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
	MFnNumericAttribute nAttr;
	MFnMatrixAttribute mAttr;
	MFnUnitAttribute uAttr;

	aDriverMatrix = mAttr.create("driverMatrix", "dvm");
	addAttribute(aDriverMatrix);

	aUpVectorMatrix = mAttr.create("upVectorMatrix", "uvm");
	addAttribute(aUpVectorMatrix);

	aInputTranslateX = nAttr.create("translateX", "tx", MFnNumericData::kDouble, 0);
	nAttr.setStorable(true);
	nAttr.setKeyable(true);
	nAttr.setWritable(true);
	addAttribute(aInputTranslateX);

	aInputTranslateY = nAttr.create("translateY", "ty", MFnNumericData::kDouble, 0);
	nAttr.setStorable(true);
	nAttr.setKeyable(true);
	nAttr.setWritable(true);
	addAttribute(aInputTranslateY);

	aInputTranslateZ = nAttr.create("translateZ", "tz", MFnNumericData::kDouble, 0);
	nAttr.setStorable(true);
	nAttr.setKeyable(true);
	nAttr.setWritable(true);
	addAttribute(aInputTranslateZ);

	aInputTranslate = nAttr.create("translate", "t", aInputTranslateX, aInputTranslateY, aInputTranslateZ);
	addAttribute(aInputTranslate);

	aOutputRotateX = uAttr.create("rotateX", "rx", MFnUnitAttribute::kAngle, 0);
	nAttr.setStorable(true);
	nAttr.setKeyable(true);
	nAttr.setWritable(true);
	addAttribute(aOutputRotateX);

	aOutputRotateY = uAttr.create("rotateY", "ry", MFnUnitAttribute::kAngle, 0);
	nAttr.setStorable(true);
	nAttr.setKeyable(true);
	nAttr.setWritable(true);
	addAttribute(aOutputRotateY);

	aOutputRotateZ = uAttr.create("rotateX", "rz", MFnUnitAttribute::kAngle, 0);
	nAttr.setStorable(true);
	nAttr.setKeyable(true);
	nAttr.setWritable(true);
	addAttribute(aOutputRotateZ);

	aOutputRotate = nAttr.create("rotate", "ro", aOutputRotateX, aOutputRotateY, aOutputRotateZ);
	addAttribute(aOutputRotate);

	return MS::kSuccess;
}

