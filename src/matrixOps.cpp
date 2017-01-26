#include "MatrixOps.h"


MObject MatrixBlend::aMatrixInA;
MObject MatrixBlend::aMatrixInB;
MObject MatrixBlend::aBlend;
MObject MatrixBlend::aRotationOrder;
MObject MatrixBlend::aOutRotationOrder;
MObject MatrixBlend::aOutMatrix;
MObject MatrixToSrt::aInMatrix;
MObject MatrixToSrt::aOutSrt;
MObject MatrixToSrt::aOutRotate;
MObject MatrixToSrt::aOutRotateX;
MObject MatrixToSrt::aOutRotateY;
MObject MatrixToSrt::aOutRotateZ;
MObject MatrixToSrt::aOutTranslate;
MObject MatrixToSrt::aOutScale;

MObject SrtToMatrix::aOutMatrix;
MObject SrtToMatrix::aInRotate;
MObject SrtToMatrix::aInRotateX;
MObject SrtToMatrix::aInRotateY;
MObject SrtToMatrix::aInRotateZ;
MObject SrtToMatrix::aInTranslate;
MObject SrtToMatrix::aInScale;
MObject MatrixConstant::aMatix;

void MatrixToSrt::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus MatrixToSrt::compute(const MPlug& plug, MDataBlock& datablock)
{
	return MS::kSuccess;
}
MStatus MatrixToSrt::initialize()
{
	return MS::kSuccess;
};
void SrtToMatrix::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus SrtToMatrix::compute(const MPlug& plug, MDataBlock& datablock)
{
	return MS::kSuccess;
}
MStatus SrtToMatrix::initialize()
{
	return MS::kSuccess;
}
void MatrixConstant::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus MatrixConstant::compute(const MPlug& plug, MDataBlock& datablock)
{
	return MS::kSuccess;
}
MStatus MatrixConstant::initialize()
{
	return MS::kSuccess;
}


void MatrixBlend::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus MatrixBlend::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;
	if (plug == aOutMatrix || plug == aOutRotationOrder)
	{
		MMatrix inMatrixA = dataBlock.inputValue(aMatrixInA).asMatrix();
		MMatrix inMatrixB = dataBlock.inputValue(aMatrixInB).asMatrix();
		int rotOrder = dataBlock.inputValue(aRotationOrder).asShort();
		float inBlend = dataBlock.inputValue(aBlend).asFloat();

		//translate
		MTransformationMatrix transMatA = MTransformationMatrix(inMatrixA);
		MTransformationMatrix transMatB = MTransformationMatrix(inMatrixB);
		MVector translate = utils::lerp(transMatB.translation(MSpace::kWorld), transMatA.translation(MSpace::kWorld), inBlend);

		//scale
		double scaleA[3];
		double scaleB[3];
		transMatA.getScale(scaleA, MSpace::kWorld);
		transMatB.getScale(scaleB, MSpace::kWorld);
		double lerpedScale[3];
		for (int i = 0; i < 3; i++)
		{
			lerpedScale[i] = (double)utils::lerp((float)scaleA[i], (float)scaleB[i], inBlend);
		}
		//rotate
		transMatA.reorderRotation(utils::rotationOrderByIndex(rotOrder));
		transMatB.reorderRotation(utils::rotationOrderByIndex(rotOrder));
		MQuaternion quat = utils::slerp(transMatA.rotation(), transMatB.rotation(), inBlend);
		MTransformationMatrix totalTrans;
		totalTrans.rotateTo(quat.asEulerRotation());
		totalTrans.setTranslation(translate, MSpace::kWorld);
		totalTrans.setScale(lerpedScale, MSpace::kWorld);
		dataBlock.outputValue(aOutRotationOrder).set(rotOrder);
		MDataHandle outMH = dataBlock.outputValue(aOutMatrix);
		outMH.setMMatrix(totalTrans.asMatrix());
		outMH.setClean();
		status = MS::kSuccess;
	}
	return status;
}


MStatus MatrixBlend::initialize()
{
	MStatus status;
	MFnNumericAttribute nAttr;
	MFnMatrixAttribute mAttr;
	MFnEnumAttribute eAttr;

	aMatrixInA = mAttr.create("matrixInA", "matrixInA", MFnMatrixAttribute::kDouble, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	mAttr.setKeyable(true); mAttr.setWritable(true); mAttr.setStorable(false);
	mAttr.setConnectable(true);
	addAttribute(aMatrixInA);

	aMatrixInB = mAttr.create("matrixInB", "matrixInB", MFnMatrixAttribute::kDouble, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	mAttr.setKeyable(true); mAttr.setWritable(true); mAttr.setStorable(false);
	mAttr.setConnectable(true);
	addAttribute(aMatrixInB);

	aBlend = nAttr.create("blend", "blend", MFnNumericData::kFloat, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setWritable(true); nAttr.setStorable(false);
	nAttr.setConnectable(true); nAttr.setMin(0); nAttr.setMax(1);
	addAttribute(aBlend);


	aRotationOrder = eAttr.create("rotationOrder", "ro", 0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	eAttr.setKeyable(true); eAttr.setConnectable(true); eAttr.setChannelBox(true);
	eAttr.setWritable(true); eAttr.setStorable(false);
	eAttr.addField("xyz", 0); eAttr.addField("yzx", 1); eAttr.addField("zxy", 2);
	eAttr.addField("xzy", 3); eAttr.addField("yxz", 4); eAttr.addField("zyx", 5);
	addAttribute(aRotationOrder);

	//outputs
	aOutRotationOrder = eAttr.create("outRotationOrder", "oro", 0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	eAttr.setKeyable(false); eAttr.setWritable(false); eAttr.setStorable(false);
	eAttr.setReadable(true);
	eAttr.addField("xyz", 0); eAttr.addField("yzx", 1); eAttr.addField("zxy", 2);
	eAttr.addField("xzy", 3); eAttr.addField("yxz", 4); eAttr.addField("zyx", 5);
	addAttribute(aOutRotationOrder);

	aOutMatrix = mAttr.create("outMatrix", "outMatrix", MFnMatrixAttribute::kDouble, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	mAttr.setKeyable(false); mAttr.setWritable(false); mAttr.setStorable(false);
	mAttr.setReadable(true);
	addAttribute(aOutMatrix);

	attributeAffects(aMatrixInA, aOutRotationOrder);
	attributeAffects(aMatrixInB, aOutRotationOrder);
	attributeAffects(aRotationOrder, aOutRotationOrder);
	attributeAffects(aBlend, aOutRotationOrder);

	attributeAffects(aMatrixInA, aOutMatrix);
	attributeAffects(aMatrixInB, aOutMatrix);
	attributeAffects(aRotationOrder, aOutMatrix);
	attributeAffects(aBlend, aOutMatrix);


	return MS::kSuccess;
}

