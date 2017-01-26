#include "ParentDual.h"

MObject ParentDual::aParentInverse;
MObject ParentDual::aMatrixInA;
MObject ParentDual::aMatrixInB;
MObject ParentDual::aBlend;
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
	if (plug == aOutTranslate || plug.parent() == aOutTranslate || plug == aOutRotate || plug.parent() == aOutRotate
		|| plug == aOutScale || plug.parent() == aOutScale|| plug == aOutSrt || plug == aOutRotationOrder)
	{
		MMatrix inParentInverseMatrix = dataBlock.inputValue(aParentInverse).asMatrix();
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
		float lerpedScale[3];
		for (int i = 0; i < 3; i++)
		{
			lerpedScale[i] = utils::lerp((float)scaleB[i], (float)scaleA[i], inBlend);
		}
		//rotate
		transMatA.reorderRotation(utils::rotationOrderByIndex(rotOrder));
		transMatB.reorderRotation(utils::rotationOrderByIndex(rotOrder));
		MQuaternion quat = utils::slerp(transMatA.rotation(), transMatB.rotation(), inBlend);

		dataBlock.outputValue(aOutRotationOrder).set(rotOrder);
		MDataHandle hTranslate = dataBlock.outputValue(aOutTranslate);
		hTranslate.set(translate);
		hTranslate.setClean();

		MDataHandle hScale = dataBlock.outputValue(aOutScale);
		hScale.set(lerpedScale[0], lerpedScale[1], lerpedScale[2]);
		hScale.setClean();

		MDataHandle hRotate = dataBlock.outputValue(aOutRotate);
		hRotate.set(quat.asEulerRotation().asVector());
		hRotate.setClean();

		
		dataBlock.outputValue(aOutSrt).setClean();
		return MS::kSuccess;
	}

	return status;
}


MStatus ParentDual::initialize()
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

	aMatrixInA = mAttr.create("matrixInA", "matrixInA", MFnMatrixAttribute::kDouble, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	mAttr.setKeyable(true); mAttr.setWritable(true); mAttr.setStorable(true);
	mAttr.setConnectable(true);
	addAttribute(aMatrixInA);

	aMatrixInB = mAttr.create("matrixInB", "matrixInB", MFnMatrixAttribute::kDouble, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	mAttr.setKeyable(true); mAttr.setWritable(true); mAttr.setStorable(true);
	mAttr.setConnectable(true);
	addAttribute(aMatrixInA);

	aBlend = nAttr.create("blend", "blend", MFnNumericData::kFloat, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setWritable(true); nAttr.setStorable(true);
	nAttr.setConnectable(true);
	addAttribute(aBlend);


	aRotationOrder = eAttr.create("rotationOrder", "ro", 0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	eAttr.setKeyable(true); eAttr.setConnectable(true); eAttr.setChannelBox(true);
	eAttr.setWritable(true); eAttr.setStorable(true);
	eAttr.addField("xyz", 0); eAttr.addField("yzx", 1); eAttr.addField("zxy", 2);
	eAttr.addField("xzy", 3); eAttr.addField("yxz", 4); eAttr.addField("zyx", 5);
	addAttribute(aRotationOrder);

	//outputs
	aOutRotationOrder = eAttr.create("outRotationOrder", "oro", 0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	eAttr.setKeyable(false); eAttr.setWritable(false); eAttr.setStorable(false);
	eAttr.addField("xyz", 0); eAttr.addField("yzx", 1); eAttr.addField("zxy", 2);
	eAttr.addField("xzy", 3); eAttr.addField("yxz", 4); eAttr.addField("zyx", 5);
	addAttribute(aOutRotationOrder);

	aOutSrt = cAttr.create("outSrt", "osrt", &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	cAttr.setChannelBox(false);

	aOutTranslate = nAttr.createPoint("outTranslate", "ot", &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(false); nAttr.setStorable(false); nAttr.setWritable(false);

	aOutRotateX = uAttr.create("outRotateX", "orx", MFnUnitAttribute::kAngle, 0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	uAttr.setStorable(false); uAttr.setKeyable(false); uAttr.setWritable(false);
	addAttribute(aOutRotateX);

	aOutRotateY = uAttr.create("outRotateY", "ory", MFnUnitAttribute::kAngle, 0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	uAttr.setStorable(false); uAttr.setKeyable(false); uAttr.setWritable(false);
	addAttribute(aOutRotateY);

	aOutRotateZ = uAttr.create("outRotateZ", "orz", MFnUnitAttribute::kAngle, 0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	uAttr.setStorable(false); uAttr.setKeyable(false); uAttr.setWritable(false);
	addAttribute(aOutRotateZ);

	aOutRotate = nAttr.create("outRotate", "or", aOutRotateX, aOutRotateY, aOutRotateZ, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(false); nAttr.setStorable(false); nAttr.setWritable(false);

	aOutScale = nAttr.createPoint("outScale", "os", &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(false); nAttr.setStorable(false); nAttr.setWritable(false);

	cAttr.addChild(aOutTranslate);
	cAttr.addChild(aOutRotate);
	cAttr.addChild(aOutScale);
	addAttribute(aOutSrt);

	attributeAffects(aParentInverse, aOutRotate);
	attributeAffects(aMatrixInA, aOutRotate);
	attributeAffects(aMatrixInB, aOutRotate);
	attributeAffects(aRotationOrder, aOutRotate);
	attributeAffects(aBlend, aOutRotate);

	attributeAffects(aParentInverse, aOutTranslate);
	attributeAffects(aMatrixInA, aOutTranslate);
	attributeAffects(aMatrixInB, aOutTranslate);
	attributeAffects(aRotationOrder, aOutTranslate);
	attributeAffects(aBlend, aOutTranslate);
	
	attributeAffects(aParentInverse, aOutScale);
	attributeAffects(aMatrixInA, aOutScale);
	attributeAffects(aMatrixInB, aOutScale);
	attributeAffects(aRotationOrder, aOutScale);
	attributeAffects(aBlend, aOutScale);

	attributeAffects(aParentInverse, aOutRotationOrder);
	attributeAffects(aMatrixInA, aOutRotationOrder);
	attributeAffects(aMatrixInB, aOutRotationOrder);
	attributeAffects(aRotationOrder, aOutRotationOrder);
	attributeAffects(aBlend, aOutRotationOrder);
	attributeAffects(aParentInverse, aOutSrt);
	attributeAffects(aMatrixInA, aOutSrt);
	attributeAffects(aMatrixInB, aOutSrt);
	attributeAffects(aRotationOrder, aOutSrt);
	attributeAffects(aBlend, aOutSrt);


	return MS::kSuccess;
}

