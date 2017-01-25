#include "angularOps.h"

MObject AngularCosine::aResult;
MObject AngularCosine::aValue;
MObject AngularSine::aResult;
MObject AngularSine::aValue;
MObject AngularTan::aResult;
MObject AngularTan::aValue;


void AngularSine::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}
MStatus AngularSine::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;
	if (plug == aResult)
	{
		MAngle value = dataBlock.inputValue(aValue).asAngle();
		MDataHandle out = dataBlock.outputValue(aResult);
		out.set(sin(value.asDegrees() * M_PI / 180));
		out.setClean();
	}
	return status;
}
MStatus AngularSine::initialize()
{
	MStatus status;
	MFnNumericAttribute nAttr;
	MFnUnitAttribute uAttr;
	aValue = uAttr.create("value", "value", MFnUnitAttribute::kAngle, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	uAttr.setKeyable(true); uAttr.setStorable(true);
	uAttr.setWritable(true); uAttr.setChannelBox(true);
	uAttr.setConnectable(true);
	addAttribute(aValue);
	aResult = nAttr.create("result", "result", MFnNumericData::kDouble, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(false); nAttr.setStorable(false);
	nAttr.setWritable(false);
	addAttribute(aResult);

	attributeAffects(aValue, aResult);

	return status;
}
void AngularCosine::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}
MStatus AngularCosine::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;
	if (plug == aResult)
	{
		MAngle value = dataBlock.inputValue(aValue).asAngle();
		MDataHandle out = dataBlock.outputValue(aResult);
		out.set(cos(value.asDegrees() * M_PI / 180));
		out.setClean();
	}
	return status;
}
MStatus AngularCosine::initialize()
{
	MStatus status;
	MFnNumericAttribute nAttr;
	MFnUnitAttribute uAttr;

	aValue = uAttr.create("value", "value", MFnUnitAttribute::kAngle, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	uAttr.setKeyable(true); uAttr.setStorable(true);
	uAttr.setWritable(true); uAttr.setChannelBox(true);
	uAttr.setConnectable(true);
	addAttribute(aValue);
	aResult = nAttr.create("result", "result", MFnNumericData::kDouble, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(false); nAttr.setStorable(false);
	nAttr.setWritable(false);
	addAttribute(aResult);

	attributeAffects(aValue, aResult);
	return status;
}

void AngularTan::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}
MStatus AngularTan::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;
	if (plug == aResult)
	{
		MAngle value = dataBlock.inputValue(aValue).asAngle();

		MDataHandle out = dataBlock.outputValue(aResult);
		out.set(tan(value.asDegrees() * M_PI / 180));
		out.setClean();
	}
	return status;
}

MStatus AngularTan::initialize()
{
	MStatus status;
	MFnNumericAttribute nAttr;
	MFnUnitAttribute uAttr;

	aValue = uAttr.create("value", "value", MFnUnitAttribute::kAngle, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	uAttr.setKeyable(true); uAttr.setStorable(true);
	uAttr.setWritable(true); uAttr.setChannelBox(true);
	uAttr.setConnectable(true);
	addAttribute(aValue);
	aResult = nAttr.create("result", "result", MFnNumericData::kDouble, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(false); nAttr.setStorable(false);
	nAttr.setWritable(false);
	addAttribute(aResult);

	attributeAffects(aValue, aResult);
	return status;
}