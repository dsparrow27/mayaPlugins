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
	if ((plug == aOutputRotate) || (plug == aOutputRotateX) ||
		(plug == aOutputRotateY) || (plug == aOutputRotateZ))
	{
		// the matrix to aim at 
		MMatrix driverMatrix = dataBlock.inputValue(aDriverMatrix).asMatrix();
		// the matrix to use as the upVector
		MMatrix upVectorMatrix = dataBlock.inputValue(aUpVectorMatrix).asMatrix();
		MVector inputTranslate = dataBlock.inputValue(aInputTranslate).asVector();

		//extract the translation from the matrices
		MVector driverMatrixPos(driverMatrix[3][0],
			driverMatrix[3][1],
			driverMatrix[3][2]);

		MVector upVectorMatrixPos(upVectorMatrix[3][0],
			upVectorMatrix[3][1],
			upVectorMatrix[3][2]);

		//get the vectors
		MVector aimVector = driverMatrixPos - inputTranslate;
		MVector upVector = upVectorMatrixPos - inputTranslate;
		aimVector.normalize();
		upVector.normalize();

		//perpendicter vector
		MVector cross = aimVector ^ upVector;
		upVector = cross ^ aimVector;

		//build rotationMatrix
		double tmpMatrix[4][4]{{aimVector.x, aimVector.y, aimVector.z, 0},
									{upVector.x, upVector.y, upVector.z, 0},
									{cross.x, cross.y, cross.z, 0},
									{inputTranslate[0], inputTranslate[1], inputTranslate[2], 1}};

		//eulerRotations
		MMatrix rotationMatrix(tmpMatrix);
		MTransformationMatrix matrixfn(rotationMatrix);
		MEulerRotation eular = matrixfn.eulerRotation();

		dataBlock.outputValue(aOutputRotate).set(eular.x, eular.y, eular.z);
		dataBlock.outputValue(aOutputRotate).setClean();

	}

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

	//translateX
	aInputTranslateX = nAttr.create("translateX", "tx", MFnNumericData::kDouble, 0);
	nAttr.setStorable(true);
	nAttr.setKeyable(true);
	nAttr.setWritable(true);
	addAttribute(aInputTranslateX);
	//translateY
	aInputTranslateY = nAttr.create("translateY", "ty", MFnNumericData::kDouble, 0);
	nAttr.setStorable(true);
	nAttr.setKeyable(true);
	nAttr.setWritable(true);
	addAttribute(aInputTranslateY);
	//translateZ
	aInputTranslateZ = nAttr.create("translateZ", "tz", MFnNumericData::kDouble, 0);
	nAttr.setStorable(true);
	nAttr.setKeyable(true);
	nAttr.setWritable(true);
	addAttribute(aInputTranslateZ);
	//translate
	aInputTranslate = nAttr.create("translate", "t", aInputTranslateX, aInputTranslateY, aInputTranslateZ);
	addAttribute(aInputTranslate);
	
	//rotateX
	aOutputRotateX = uAttr.create("rotateX", "rx", MFnUnitAttribute::kAngle, 0);
	nAttr.setStorable(true);
	nAttr.setKeyable(true);
	nAttr.setWritable(true);
	addAttribute(aOutputRotateX);
	//rotateY
	aOutputRotateY = uAttr.create("rotateY", "ry", MFnUnitAttribute::kAngle, 0);
	nAttr.setStorable(true);
	nAttr.setKeyable(true);
	nAttr.setWritable(true);
	addAttribute(aOutputRotateY);
	//rotateZ
	aOutputRotateZ = uAttr.create("rotateX", "rz", MFnUnitAttribute::kAngle, 0);
	nAttr.setStorable(true);
	nAttr.setKeyable(true);
	nAttr.setWritable(true);
	addAttribute(aOutputRotateZ);
	//rotate
	aOutputRotate = nAttr.create("rotate", "ro", aOutputRotateX, aOutputRotateY, aOutputRotateZ);
	addAttribute(aOutputRotate);

	return MS::kSuccess;
}

