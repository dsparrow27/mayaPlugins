#include "ParentSingle.h"

MObject ParentSingle::aParentInverse;
MObject ParentSingle::aOffsetMatrix;
MObject ParentSingle::aWorldMatrix;
MObject ParentSingle::aRotationOrder;
MObject ParentSingle::aNegateX;
MObject ParentSingle::aNegateY;
MObject ParentSingle::aNegateZ;

MObject ParentSingle::aOutMatrix;

MObject ParentSingle::aOutSrt;
	MObject ParentSingle::aOutRotationOrder;
	MObject ParentSingle::aOutRotate;
		MObject ParentSingle::aOutRotateX;
		MObject ParentSingle::aOutRotateY;
		MObject ParentSingle::aOutRotateZ;

	MObject ParentSingle::aOutTranslate;
		MObject ParentSingle::aOutTranslateX;
		MObject ParentSingle::aOutTranslateY;
		MObject ParentSingle::aOutTranslateZ;
	MObject ParentSingle::aOutScale;


void ParentSingle::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}
MStatus ParentSingle::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;
	
	if (plug == aOutTranslate || plug.parent() == aOutTranslate || plug == aOutRotate || plug.parent() == aOutRotate
		|| plug == aOutScale || plug.parent() == aOutScale || plug == aOutSrt || plug == aOutRotationOrder || plug == aOutMatrix)
	{
		MMatrix inParentInverse = dataBlock.inputValue(aParentInverse).asMatrix();
		MMatrix inOffsetMatrix = dataBlock.inputValue(aOffsetMatrix).asMatrix();
		MMatrix inWorldMatrix = dataBlock.inputValue(aWorldMatrix).asMatrix();
		int rotOrder = dataBlock.inputValue(aRotationOrder).asShort();
		bool negX = dataBlock.inputValue(aNegateX).asBool();
		bool negY = dataBlock.inputValue(aNegateY).asBool();
		bool negZ = dataBlock.inputValue(aNegateZ).asBool();

		MMatrix totalMatrix = inOffsetMatrix * inWorldMatrix * inParentInverse;
		MTransformationMatrix transMat(totalMatrix);
		MDataHandle HoutTranslate = dataBlock.outputValue(aOutTranslate);
		HoutTranslate.set(totalMatrix[3][0], totalMatrix[3][1], totalMatrix[3][2]);
		HoutTranslate.setClean();
		
		double outScale[3];
		transMat.getScale(outScale, MSpace::kWorld);
		if (negX == true)
		{
			outScale[0] *= -1;
		}
		if (negY == true)
		{
			outScale[1] *= -1;
		}
		if (negZ == true)
		{
			outScale[2] *= -1;
		}
		MDataHandle outScaleH = dataBlock.outputValue(aOutScale);
		MDataHandle outaOutRotationOrderH = dataBlock.outputValue(aOutRotationOrder);
		outScaleH.set((float)outScale[0], (float)outScale[1], (float)outScale[2]);
		outScaleH.setClean();
		outaOutRotationOrderH.set(rotOrder);
		outaOutRotationOrderH.setClean();

		transMat.reorderRotation(utils::rotationOrderByIndex(rotOrder));
		MVector euler = transMat.eulerRotation().asVector();
		MDataHandle aOutRotateH = dataBlock.outputValue(aOutRotate);
		aOutRotateH.set(euler);
		aOutRotateH.setClean();
		dataBlock.outputValue(aOutSrt).setClean();
		MDataHandle hOutMatrix = dataBlock.outputValue(aOutMatrix);
		hOutMatrix.setMMatrix(transMat.asMatrix());
		hOutMatrix.setClean();
		
		status = MS::kSuccess;
	}
	
	return status;
}

MStatus ParentSingle::initialize()
{
	MStatus status;
	MFnNumericAttribute nAttr;
	MFnMatrixAttribute mAttr;
	MFnUnitAttribute uAttr;
	MFnEnumAttribute eAttr;
	MFnCompoundAttribute cAttr;
	
	aParentInverse = mAttr.create("parentInverse", "pi", MFnMatrixAttribute::kDouble, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	mAttr.setKeyable(true); mAttr.setWritable(true); mAttr.setStorable(true);
	mAttr.setConnectable(true);
	addAttribute(aParentInverse);

	aOffsetMatrix = mAttr.create("offsetMatrix", "om", MFnMatrixAttribute::kDouble, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	mAttr.setKeyable(true); mAttr.setWritable(true); mAttr.setStorable(true);
	mAttr.setConnectable(true);
	addAttribute(aOffsetMatrix);

	aWorldMatrix = mAttr.create("worldMatrix", "wm", MFnMatrixAttribute::kDouble, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	mAttr.setKeyable(true); mAttr.setWritable(true); mAttr.setStorable(true);
	mAttr.setConnectable(true);
	addAttribute(aWorldMatrix);
	aOutMatrix = mAttr.create("outMatrix", "outMatrix", MFnMatrixAttribute::kDouble, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setStorable(false); nAttr.setKeyable(false); nAttr.setWritable(false);
	cAttr.setChannelBox(false);
	addAttribute(aOutMatrix);

	aRotationOrder = eAttr.create("rotationOrder", "ro", 0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	eAttr.setKeyable(true); eAttr.setConnectable(true); eAttr.setChannelBox(true);
	eAttr.setWritable(true); eAttr.setStorable(true);
	eAttr.addField("xyz", 0);eAttr.addField("yzx", 1); eAttr.addField("zxy", 2);
	eAttr.addField("xzy", 3);eAttr.addField("yxz", 4);eAttr.addField("zyx", 5);
	addAttribute(aRotationOrder);

	aNegateX = nAttr.create("negateX", "nx", MFnNumericData::kBoolean, 0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setConnectable(true); nAttr.setChannelBox(true);
	nAttr.setWritable(true); nAttr.setStorable(true);
	addAttribute(aNegateX);

	aNegateY = nAttr.create("negateY", "ny", MFnNumericData::kBoolean, 0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setConnectable(true); nAttr.setChannelBox(true);
	nAttr.setWritable(true); nAttr.setStorable(true);
	addAttribute(aNegateY);

	aNegateZ = nAttr.create("negateZ", "nz", MFnNumericData::kBoolean, 0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setConnectable(true); nAttr.setChannelBox(true);
	nAttr.setWritable(true); nAttr.setStorable(true);
	addAttribute(aNegateZ);
	
	//outputs
	aOutRotationOrder = eAttr.create("outRotationOrder", "oro", 0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	eAttr.setKeyable(false); eAttr.setWritable(false); eAttr.setStorable(false);
	eAttr.addField("xyz", 0);eAttr.addField("yzx", 1);eAttr.addField("zxy", 2);
	eAttr.addField("xzy", 3);eAttr.addField("yxz", 4);eAttr.addField("zyx", 5);
	addAttribute(aOutRotationOrder);

	aOutSrt = cAttr.create("outSrt", "osrt", &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	cAttr.setChannelBox(false); nAttr.setKeyable(false); nAttr.setStorable(false);
	nAttr.setWritable(false);
	
	
	aOutTranslateX = nAttr.create("outTranslateX", "outTranslateX", MFnNumericData::kDouble, 0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setStorable(false); nAttr.setKeyable(false); nAttr.setWritable(false);
	cAttr.setChannelBox(false);
	addAttribute(aOutTranslateX);

	aOutTranslateY= nAttr.create("outTranslateY", "outTranslateY", MFnNumericData::kDouble, 0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setStorable(false); nAttr.setKeyable(false); nAttr.setWritable(false);
	cAttr.setChannelBox(false);
	addAttribute(aOutTranslateY);

	aOutTranslateZ = nAttr.create("outTranslateZ", "outTranslateZ", MFnNumericData::kDouble, 0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setStorable(false); nAttr.setKeyable(false); nAttr.setWritable(false);
	cAttr.setChannelBox(false);
	addAttribute(aOutTranslateZ);

	aOutTranslate = nAttr.create("outTranslate", "outTranslate", aOutTranslateX, aOutTranslateY, aOutTranslateZ, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(false); nAttr.setStorable(false); nAttr.setWritable(false);
	cAttr.setChannelBox(false);


	aOutRotateX = uAttr.create("outRotateX", "orx", MFnUnitAttribute::kAngle, 0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	uAttr.setStorable(false); uAttr.setKeyable(false); uAttr.setWritable(false);
	cAttr.setChannelBox(false);
	addAttribute(aOutRotateX);

	aOutRotateY = uAttr.create("outRotateY", "ory", MFnUnitAttribute::kAngle, 0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	uAttr.setStorable(false); uAttr.setKeyable(false); uAttr.setWritable(false);
	cAttr.setChannelBox(false);
	addAttribute(aOutRotateY);

	aOutRotateZ = uAttr.create("outRotateZ", "orz", MFnUnitAttribute::kAngle, 0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	uAttr.setStorable(false); uAttr.setKeyable(false); uAttr.setWritable(false);
	cAttr.setChannelBox(false);
	addAttribute(aOutRotateZ);

	aOutRotate = nAttr.create("outRotate", "or", aOutRotateX, aOutRotateY, aOutRotateZ, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(false); nAttr.setStorable(false); nAttr.setWritable(false);
	cAttr.setChannelBox(false);

	aOutScale = nAttr.createPoint("outScale", "os", &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(false); nAttr.setStorable(false); nAttr.setWritable(false);
	cAttr.setChannelBox(false);
	
	cAttr.addChild(aOutTranslate);
	cAttr.addChild(aOutRotate);
	cAttr.addChild(aOutScale);
	addAttribute(aOutSrt);

	attributeAffects(aParentInverse, aOutRotate);
	attributeAffects(aWorldMatrix, aOutRotate);
	attributeAffects(aOffsetMatrix, aOutRotate);
	attributeAffects(aRotationOrder, aOutRotate);
	attributeAffects(aNegateX, aOutRotate);
	attributeAffects(aNegateY, aOutRotate);
	attributeAffects(aNegateZ, aOutRotate);
	
	attributeAffects(aParentInverse, aOutTranslate);
	attributeAffects(aWorldMatrix, aOutTranslate);
	attributeAffects(aOffsetMatrix, aOutTranslate);
	attributeAffects(aRotationOrder, aOutTranslate);
	attributeAffects(aNegateX, aOutTranslate);
	attributeAffects(aNegateY, aOutTranslate);
	attributeAffects(aNegateZ, aOutTranslate);

	attributeAffects(aParentInverse, aOutScale);
	attributeAffects(aWorldMatrix, aOutScale);
	attributeAffects(aOffsetMatrix, aOutScale);
	attributeAffects(aRotationOrder, aOutScale);
	attributeAffects(aNegateX, aOutScale);
	attributeAffects(aNegateY, aOutScale);
	attributeAffects(aNegateZ, aOutScale);

	attributeAffects(aParentInverse, aOutRotationOrder);
	attributeAffects(aWorldMatrix, aOutRotationOrder);
	attributeAffects(aOffsetMatrix, aOutRotationOrder);
	attributeAffects(aRotationOrder, aOutRotationOrder);
	attributeAffects(aNegateX, aOutRotationOrder);
	attributeAffects(aNegateY, aOutRotationOrder);
	attributeAffects(aNegateZ, aOutRotationOrder);
	
	attributeAffects(aParentInverse, aOutSrt);
	attributeAffects(aWorldMatrix, aOutSrt);
	attributeAffects(aOffsetMatrix, aOutSrt);
	attributeAffects(aRotationOrder, aOutSrt);
	attributeAffects(aNegateX, aOutSrt);
	attributeAffects(aNegateY, aOutSrt);
	attributeAffects(aNegateZ, aOutSrt);

	attributeAffects(aParentInverse, aOutMatrix);
	attributeAffects(aWorldMatrix, aOutMatrix);
	attributeAffects(aOffsetMatrix, aOutMatrix);
	attributeAffects(aRotationOrder, aOutMatrix);
	attributeAffects(aNegateX, aOutMatrix);
	attributeAffects(aNegateY, aOutMatrix);
	attributeAffects(aNegateZ, aOutMatrix);
	

	return MS::kSuccess;
}

