#include "pointOnCurve.h"

MObject PointOnCurve::aInputValue;
MObject PointOnCurve::aInputCurve;
MObject PointOnCurve::aOutPosition;
MObject PointOnCurve::aUseRotation;
MObject PointOnCurve::aRotationOrder;
MObject PointOnCurve::aOutRotationOrder;
MObject PointOnCurve::aOutRotation;
MObject PointOnCurve::aOutRotationX;
MObject PointOnCurve::aOutRotationY;
MObject PointOnCurve::aOutRotationZ;
MObject PointOnCurve::aUpVectorMatrix;

void PointOnCurve::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus PointOnCurve::compute(const MPlug& plug, MDataBlock& dataBlock)
{	
	MStatus	status;
	if (plug != aOutPosition || plug != aOutRotation || plug != aOutRotationX
		|| plug != aOutRotationY || plug != aOutRotationZ)
	{	
		return MS::kSuccess;
	}

	//get values from datablock
	MObject crvV = dataBlock.inputValue(aInputCurve).asNurbsCurve();
	double inVal = dataBlock.inputValue(aInputValue).asDouble();
	bool useRotation = dataBlock.inputValue(aUseRotation).asBool();
	
	MPoint outPos;
	MFnNurbsCurve crvfn(crvV);

	double outVal = crvfn.findParamFromLength(inVal, &status);

	crvfn.getPointAtParam(outVal, outPos, MSpace::kWorld);

	//rotations
	if (useRotation == true)
	{	
		MPoint aimPos;
		MMatrix upVectorMat = dataBlock.inputValue(aUpVectorMatrix).asMatrix();
		int rotationOrder = dataBlock.inputValue(aRotationOrder).asShort();

		MVector tangent = crvfn.tangent(outVal, MSpace::kWorld);
		double outParam = crvfn.findParamFromLength(inVal+0.001);
		crvfn.getPointAtParam(outParam, aimPos);
		MTransformationMatrix upVectorTransform = MTransformationMatrix(upVectorMat);
		MVector upvecPos = upVectorTransform.translation(MSpace::kWorld);
		
		MVector aimVector = aimPos - outPos;
		MVector upVector = upvecPos - outPos;
		aimVector.normalize();
		upVector.normalize();
		MVector cross = aimVector ^ upVector;
		upVector = cross ^ aimVector;

		double tmMatrix[4][4]{ {aimVector.x, aimVector.y, aimVector.z, 0},
								{upVector.x, upVector.y, upVector.z, 0},
								{ cross.x, cross.y, cross.z, 0 },
								{outPos.x, outPos.y, outPos.z, 0} };

		MMatrix rotationMatrix(tmMatrix);
		MTransformationMatrix matrixfn(rotationMatrix);
		matrixfn.reorderRotation(utils::rotationOrderByIndex(rotationOrder));
		MVector euler = matrixfn.eulerRotation().asVector();

		MDataHandle outRotation = dataBlock.outputValue(aOutRotation);
		MDataHandle outOrder = dataBlock.outputValue(aOutRotationOrder);

		outOrder.set(rotationOrder);
		outRotation.set(euler);

		outOrder.setClean();
		outRotation.setClean();
	}
	//set the output 
	MDataHandle hOutPos = dataBlock.outputValue(aOutPosition);

	hOutPos.set(outPos.x, outPos.y, outPos.z);
	hOutPos.setClean();

	return MS::kSuccess;

}




MStatus PointOnCurve::initialize()
{
	MStatus status;
	//pointers for attributes
	MFnNumericAttribute nAttr;
	MFnTypedAttribute tAttr;
	MFnUnitAttribute uAttr;
	MFnMatrixAttribute mAttr;
	MFnEnumAttribute eAttr;
	//attribute setup
	aInputValue = nAttr.create("inputValue", "inputValue", MFnNumericData::kDouble, 0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true);
	nAttr.setStorable(true);
	nAttr.setWritable(true);
	addAttribute(aInputValue);

	aInputCurve = tAttr.create("inputCurve", "inputCurve", MFnData::kNurbsCurve, MObject::kNullObj, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	tAttr.setKeyable(true);
	tAttr.setStorable(true);
	tAttr.setWritable(true);
	addAttribute(aInputCurve);

	
	aOutPosition = nAttr.createPoint("position", "position", &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setWritable(false); nAttr.setStorable(false);
	addAttribute(aOutPosition);
	
	aUpVectorMatrix = mAttr.create("upVectorMatrix", "upVectorMatrix", MFnMatrixAttribute::kDouble, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	mAttr.setKeyable(true); mAttr.setStorable(true); mAttr.setWritable(true);
	mAttr.setConnectable(true);
	addAttribute(aUpVectorMatrix);

	aUseRotation = nAttr.create("useRotation", "useRotation", MFnNumericData::kBoolean, 1.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true); nAttr.setWritable(true);
	nAttr.setConnectable(true);
	addAttribute(aUseRotation);

	aOutRotationX = uAttr.create("outRotationX", "outRotationX", MFnUnitAttribute::kAngle, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	uAttr.setWritable(false); uAttr.setStorable(false);
	addAttribute(aOutRotationX);

	aOutRotationY = uAttr.create("outRotationY", "outRotationY", MFnUnitAttribute::kAngle, 0.0, &status);;
	CHECK_MSTATUS_AND_RETURN_IT(status);
	uAttr.setWritable(false); uAttr.setStorable(false);
	addAttribute(aOutRotationY);

	aOutRotationZ = uAttr.create("outRotationZ", "outRotationZ", MFnUnitAttribute::kAngle, 0.0, &status);;
	CHECK_MSTATUS_AND_RETURN_IT(status);
	uAttr.setWritable(false); uAttr.setStorable(false);
	addAttribute(aOutRotationZ);

	aOutRotation = nAttr.create("outRotation", "outRotation", aOutRotationX, aOutRotationY, aOutRotationZ, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setWritable(false); nAttr.setStorable(false);
	addAttribute(aOutRotation);

	aRotationOrder = eAttr.create("rotationOrder", "rotationOrder", 0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	eAttr.setKeyable(true); eAttr.setWritable(true); eAttr.setStorable(true);
	eAttr.setConnectable(true); eAttr.setChannelBox(true);
	eAttr.addField("xyz", 0); eAttr.addField("yzx", 1); eAttr.addField("zxy", 2);
	eAttr.addField("xzy", 3); eAttr.addField("yxz", 4); eAttr.addField("zyx", 5);
	addAttribute(aRotationOrder);

	aOutRotationOrder = eAttr.create("outRotationOrder", "outRotationOrder", 0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	eAttr.setWritable(false); eAttr.setStorable(false);
	eAttr.addField("xyz", 0); eAttr.addField("yzx", 1); eAttr.addField("zxy", 2);
	eAttr.addField("xzy", 3); eAttr.addField("yxz", 4); eAttr.addField("zyx", 5);
	addAttribute(aOutRotationOrder);
	
	attributeAffects(aInputCurve, aOutPosition);
	attributeAffects(aInputValue, aOutPosition);
	attributeAffects(aRotationOrder, aOutPosition);
	attributeAffects(aUseRotation, aOutPosition);
	attributeAffects(aUpVectorMatrix, aOutPosition);
	
	attributeAffects(aInputCurve, aOutRotation);
	attributeAffects(aInputValue, aOutRotation);
	attributeAffects(aRotationOrder, aOutRotation);
	attributeAffects(aUseRotation, aOutRotation);
	attributeAffects(aUpVectorMatrix, aOutRotation);

	attributeAffects(aInputCurve, aOutRotationOrder);
	attributeAffects(aInputValue, aOutRotationOrder);
	attributeAffects(aRotationOrder, aOutRotationOrder);
	attributeAffects(aUseRotation, aOutRotationOrder);
	attributeAffects(aUpVectorMatrix, aOutRotationOrder);
	
	return MS::kSuccess;
}

