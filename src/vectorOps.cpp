#include "vectorOps.h"

MObject VectorSum::aOperands;
MObject VectorSum::aResult;
MObject VectorSubstract::aOperands;
MObject VectorSubstract::aResult;
MObject VectorMultiply::aVector;
MObject VectorMultiply::aScalar;
MObject VectorMultiply::aResult;
MObject VectorDivide::aValue;
MObject VectorDivide::aDivisor;
MObject VectorDivide::aResult;
MObject VectorCross::aVecA;
MObject VectorCross::aVecB;
MObject VectorCross::aResult;
MObject VectorDot::aVecA;
MObject VectorDot::aVecB;
MObject VectorDot::aResult;
MObject VectorBlendPair::aValueA;
MObject VectorBlendPair::aValueB;
MObject VectorBlendPair::aBlend;
MObject VectorBlendPair::aResult;

void VectorSum::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus VectorSum::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;
	
	if (plug == aResult)
	{

		MArrayDataHandle inOperands = dataBlock.inputArrayValue(aOperands);
		MDataHandle out = dataBlock.outputValue(aResult);
		int elementCount = inOperands.elementCount();
		MVector result;
		for (int i = 0; i < elementCount; i++)
		{
			inOperands.jumpToArrayElement(i);
			result += inOperands.inputValue().asVector();
		}
		out.setMVector(result);
		out.setClean();
		status = MS::kSuccess;
	}
	
	return status;
}

MStatus VectorSum::initialize()
{
	MStatus status;
	
	MFnNumericAttribute nAttr;

	aOperands = nAttr.createPoint("operands", "ops", &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setChannelBox(true);
	nAttr.setConnectable(true); nAttr.setArray(true);
	nAttr.setUsesArrayDataBuilder(false);
	addAttribute(aOperands);

	aResult = nAttr.createPoint("result", "r", &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(false); nAttr.setStorable(false);
	nAttr.setWritable(false);
	addAttribute(aResult);

	attributeAffects(aOperands, aResult);
	
	return MS::kSuccess;
}



void VectorSubstract::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus VectorSubstract::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;

	if (plug == aResult)
	{

		MArrayDataHandle inOperands = dataBlock.inputArrayValue(aOperands);
		int elementCount = inOperands.elementCount();
		MDataHandle outHandle = dataBlock.outputValue(aResult);

		if (elementCount < 1)
		{
			outHandle.set(-1);
			outHandle.setClean();
			return MS::kSuccess;
		}
		inOperands.jumpToArrayElement(0);
		MVector result = inOperands.inputValue().asVector();
		for (int i = 0; i < elementCount; i++)
		{
			inOperands.jumpToArrayElement(i);
			result -= inOperands.inputValue().asVector();
		}
		outHandle.setMVector(result);
		outHandle.setClean();

		status = MS::kSuccess;
	}
	return status;
}

MStatus VectorSubstract::initialize()
{
	MStatus status;

	MFnNumericAttribute nAttr;

	aOperands = nAttr.createPoint("operands", "ops", &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setArray(true);
	nAttr.setUsesArrayDataBuilder(false); nAttr.setChannelBox(true);
	nAttr.setConnectable(true);
	addAttribute(aOperands);

	aResult = nAttr.createPoint("result", "r", &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(false); nAttr.setStorable(false);
	nAttr.setWritable(false);
	addAttribute(aResult);

	attributeAffects(aOperands, aResult);

	return MS::kSuccess;
}


void VectorMultiply::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus VectorMultiply::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;

	if (plug == aResult)
	{

		MVector vec = dataBlock.inputValue(aVector).asVector();
		double scalar = dataBlock.inputValue(aVector).asDouble();
		MDataHandle out = dataBlock.outputValue(aResult);
		out.setMVector(vec*scalar);
		out.setClean();

		status = MS::kSuccess;
	}
	return status;
}

MStatus VectorMultiply::initialize()
{
	MStatus status;

	MFnNumericAttribute nAttr;

	aVector = nAttr.createPoint("vector", "vec", &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setChannelBox(true);
	nAttr.setConnectable(true);
	addAttribute(aVector);

	aScalar = nAttr.create("scalar", "scalar", MFnNumericData::kDouble, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setChannelBox(true);
	nAttr.setConnectable(true);
	addAttribute(aScalar);

	aResult = nAttr.createPoint("result", "r", &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(false); nAttr.setStorable(false);
	nAttr.setWritable(false);
	addAttribute(aResult);

	attributeAffects(aVector, aResult);
	attributeAffects(aScalar, aResult);

	return MS::kSuccess;
}

void VectorDivide::postConstructor()
{
	this->setExistWithoutOutConnections(true);
	this->setExistWithoutInConnections(true);
}

MStatus VectorDivide::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;
	if (plug == aResult)
	{
		MVector value = dataBlock.inputValue(aValue).asVector();
		float divisor = dataBlock.inputValue(aDivisor).asFloat();
		MDataHandle out = dataBlock.outputValue(aResult);

		if (utils::almostEqual(divisor, 0.0f, 2))
		{
			out.setMVector(MVector(0,0,0));
			out.setClean();
			return MS::kSuccess;
		}
		out.setMVector(value / divisor);
		out.setClean();
		status = MS::kSuccess;
	}
	return status;
}
MStatus VectorDivide::initialize()
{
	MStatus status;
	MFnNumericAttribute nAttr;

	aValue = nAttr.createPoint("value", "val", &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setChannelBox(true);
	nAttr.setConnectable(true);
	addAttribute(aValue);

	aDivisor = nAttr.create("divisor", "div", MFnNumericData::kFloat, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setChannelBox(true);
	nAttr.setConnectable(true);
	addAttribute(aDivisor);

	aResult = nAttr.createPoint("result", "r", &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(false); nAttr.setStorable(false);
	nAttr.setWritable(false);
	addAttribute(aResult);

	attributeAffects(aValue, aResult);
	attributeAffects(aDivisor, aResult);

	return MS::kSuccess;

}

void VectorCross::postConstructor()
{
	this->setExistWithoutOutConnections(true);
	this->setExistWithoutInConnections(true);
}

MStatus VectorCross::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;
	if (plug == aResult)
	{
		MVector vecA = dataBlock.inputValue(aVecA).asVector();
		MVector vecB = dataBlock.inputValue(aVecB).asVector();
		MDataHandle out = dataBlock.outputValue(aResult);
		MVector result;
		result.x = vecA.y*vecB.z - vecA.z*vecB.y;
		result.y = vecA.z*vecB.x - vecA.x*vecB.z;
		result.z = vecA.x*vecB.y - vecA.y*vecB.x;

		out.setMVector(result);
		out.setClean();
		status = MS::kSuccess;
	}
	return status;
}
MStatus VectorCross::initialize()
{
	MStatus status;
	MFnNumericAttribute nAttr;

	aVecA = nAttr.createPoint("vectorB", "vecA", &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setChannelBox(true);
	nAttr.setConnectable(true);
	addAttribute(aVecA);

	aVecB = nAttr.createPoint("vectorB", "vecB", &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setChannelBox(true);
	nAttr.setConnectable(true);
	addAttribute(aVecB);

	aResult = nAttr.createPoint("result", "r", &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(false); nAttr.setStorable(false);
	nAttr.setWritable(false);
	addAttribute(aResult);

	attributeAffects(aVecA, aResult);
	attributeAffects(aVecB, aResult);

	return MS::kSuccess;

}


void VectorDot::postConstructor()
{
	this->setExistWithoutOutConnections(true);
	this->setExistWithoutInConnections(true);
}

MStatus VectorDot::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;
	if (plug == aResult)
	{
		MVector vecA = dataBlock.inputValue(aVecA).asVector();
		MVector vecB = dataBlock.inputValue(aVecB).asVector();
		MDataHandle out = dataBlock.outputValue(aResult);
		double result;
		result = vecA.x * vecB.x + vecA.y * vecB.y + vecA.z * vecB.z;
		out.set(result);
		out.setClean();
		status = MS::kSuccess;
	}
	return status;
}
MStatus VectorDot::initialize()
{
	MStatus status;
	MFnNumericAttribute nAttr;

	aVecA = nAttr.createPoint("vectorA", "vecA", &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setChannelBox(true);
	nAttr.setConnectable(true);
	addAttribute(aVecA);

	aVecB = nAttr.createPoint("vectorB", "vecB", &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setChannelBox(true);
	nAttr.setConnectable(true);
	addAttribute(aVecB);

	aResult = nAttr.create("result", "r", MFnNumericData::kDouble, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(false); nAttr.setStorable(false);
	nAttr.setWritable(false);
	addAttribute(aResult);

	attributeAffects(aVecA, aResult);
	attributeAffects(aVecB, aResult);

	return MS::kSuccess;

}

void VectorBlendPair::postConstructor()
{
	this->setExistWithoutOutConnections(true);
	this->setExistWithoutInConnections(true);
}

MStatus VectorBlendPair::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;
	if (plug == aResult)
	{
		MVector vecA = dataBlock.inputValue(aValueA).asVector();
		MVector vecB = dataBlock.inputValue(aValueB).asVector();
		float blend = dataBlock.inputValue(aBlend).asFloat();
		MDataHandle out = dataBlock.outputValue(aResult);
		MVector result = utils::lerp(vecB, vecA, blend);
		out.setMVector(result);
		out.setClean();
		status = MS::kSuccess;
	}
	return status;
}
MStatus VectorBlendPair::initialize()
{
	MStatus status;
	MFnNumericAttribute nAttr;

	aValueA = nAttr.createPoint("vectorA", "vecA", &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setChannelBox(true);
	nAttr.setConnectable(true);
	addAttribute(aValueA);

	aValueB = nAttr.createPoint("vectorB", "vecB", &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setChannelBox(true);
	nAttr.setConnectable(true);
	addAttribute(aValueB);
	aBlend = nAttr.create("blend", "blend", MFnNumericData::kFloat, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setChannelBox(true);
	nAttr.setConnectable(true);
	addAttribute(aBlend);

	aResult = nAttr.createPoint("result", "r", &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(false); nAttr.setStorable(false);
	nAttr.setWritable(false);
	addAttribute(aResult);

	attributeAffects(aValueA, aResult);
	attributeAffects(aValueB, aResult);
	attributeAffects(aBlend, aResult);

	return MS::kSuccess;

}