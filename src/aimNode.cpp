#include "aimNode.h"
#include "utils.h"

// node id 
MObject AimNode::aInputTranslate;
MObject AimNode::aOutputRotateX;
MObject AimNode::aOutputRotateY;
MObject AimNode::aOutputRotateZ;
MObject AimNode::aOutputRotate;
MObject AimNode::aDriverMatrix;
MObject AimNode::aUpVectorMatrix;
MObject AimNode::aParentInverseMatrix;


void* AimNode::creator()
{
	return new AimNode();
}


MStatus AimNode::compute(const MPlug& plug, MDataBlock& dataBlock)
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
		MMatrix parentInverse = dataBlock.inputValue(aParentInverseMatrix).asMatrix();

		driverMatrix *= parentInverse;
		upVectorMatrix *= parentInverse;
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
		
		//upVector *= parentInverse;
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


MStatus AimNode::initialize()
{
	MStatus status;
	MFnNumericAttribute nAttr;
	MFnMatrixAttribute mAttr;
	MFnUnitAttribute uAttr;

	aDriverMatrix = mAttr.create("driverMatrix", "dvm");
	AS_INPUT(mAttr);
	addAttribute(aDriverMatrix);

	aUpVectorMatrix = mAttr.create("upVectorMatrix", "uvm");
	AS_INPUT(mAttr);
	addAttribute(aUpVectorMatrix);

	//translateX
	//translate
	aInputTranslate = nAttr.createPoint("translate", "t");
	addAttribute(aInputTranslate);
	
	//rotateX
	aOutputRotateX = uAttr.create("rotateX", "rx", MFnUnitAttribute::kAngle, 0);
	AS_OUTPUT(uAttr);
	addAttribute(aOutputRotateX);
	//rotateY
	aOutputRotateY = uAttr.create("rotateY", "ry", MFnUnitAttribute::kAngle, 0);
	AS_OUTPUT(uAttr);
	nAttr.setStorable(true);
	nAttr.setKeyable(true);
	nAttr.setWritable(true);
	addAttribute(aOutputRotateY);
	//rotateZ
	aOutputRotateZ = uAttr.create("rotateZ", "rz", MFnUnitAttribute::kAngle, 0);
	AS_OUTPUT(uAttr);
	nAttr.setStorable(true);
	nAttr.setKeyable(true);
	nAttr.setWritable(true);
	addAttribute(aOutputRotateZ);
	//rotate
	aOutputRotate = nAttr.create("rotate", "ro", aOutputRotateX, aOutputRotateY, aOutputRotateZ);
	addAttribute(aOutputRotate);

	//parent inverse matrix
	aParentInverseMatrix = mAttr.create("parentInverse", "parinv");
	AS_INPUT(mAttr);
	mAttr.setDefault(MMatrix::identity);
	addAttribute(aParentInverseMatrix);


	attributeAffects(aParentInverseMatrix, aOutputRotate);
	attributeAffects(aDriverMatrix, aOutputRotate);
	attributeAffects(aUpVectorMatrix, aOutputRotate);
	attributeAffects(aInputTranslate, aOutputRotate);

	return MS::kSuccess;
}

