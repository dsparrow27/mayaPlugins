#include "scalarOps.h"

MObject Sum::aOperands;
MObject Sum::aResult;
MObject Substract::aOperands;
MObject Substract::aResult;
MObject Multiply::aOperands;
MObject Multiply::aResult;
MObject Divide::aDivisor;
MObject Divide::aValue;
MObject Divide::aResult;
MObject Power::aBase;
MObject Power::aExponent;
MObject Power::aResult;
MObject Clamp::aOperands;
MObject Clamp::aResult;
MObject Clamp::aMin;
MObject Clamp::aMax;
MObject Floor::aValue;
MObject Floor::aResult;
MObject Ceiling::aValue;
MObject Ceiling::aResult;
MObject Round::aValue;
MObject Round::aResult;
MObject Truncate::aValue;
MObject Truncate::aResult;
MObject BlendPair::aBlend;
MObject BlendPair::aValueA;
MObject BlendPair::aValueB;
MObject BlendPair::aResult;
MObject Gaussian::aResult;
MObject Gaussian::aInValue;
MObject Gaussian::aMagnitude;
MObject Gaussian::aMean;
MObject Gaussian::aVariance;
MObject Remap::aResult;
MObject Remap::aInValue;
MObject Remap::aOldMin;
MObject Remap::aOldMax;
MObject Remap::aNewMin;
MObject Remap::aNewMax;





void Sum::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus Sum::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;

	if (plug == aResult)
	{

		MArrayDataHandle inOperands = dataBlock.inputArrayValue(aOperands);
		int elementCount = inOperands.elementCount();
		inOperands.jumpToArrayElement(0);
		double result = inOperands.inputValue().asDouble();
		for (int i = 1; i < elementCount; i++)
		{
			inOperands.jumpToArrayElement(i);
			result += inOperands.inputValue().asDouble();
		}
		dataBlock.outputValue(aResult).set(result);
		dataBlock.outputValue(aResult).setClean();
		status = MS::kSuccess;
	}
	return status;
}

MStatus Sum::initialize()
{
	MStatus status;
	
	MFnNumericAttribute nAttr;

	aOperands = nAttr.create("operands", "ops", MFnNumericData::kDouble, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setArray(true);
	nAttr.setUsesArrayDataBuilder(false); nAttr.setChannelBox(true);
	nAttr.setConnectable(true);
	addAttribute(aOperands);

	aResult = nAttr.create("result", "r", MFnNumericData::kDouble, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(false); nAttr.setStorable(false);
	nAttr.setWritable(false);
	addAttribute(aResult);

	attributeAffects(aOperands, aResult);

	return MS::kSuccess;
}


void Substract::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus Substract::compute(const MPlug& plug, MDataBlock& dataBlock)
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
		double result = inOperands.inputValue().asDouble();
		for (int i = 0; i < elementCount; i++)
		{
			inOperands.jumpToArrayElement(i);
			result -= inOperands.inputValue().asDouble();
		}
		outHandle.set(result);
		outHandle.setClean();

		status = MS::kSuccess;
	}
	return status;
}

MStatus Substract::initialize()
{
	MStatus status;

	MFnNumericAttribute nAttr;

	aOperands = nAttr.create("operands", "ops", MFnNumericData::kDouble, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setArray(true);
	nAttr.setUsesArrayDataBuilder(false); nAttr.setChannelBox(true);
	nAttr.setConnectable(true);
	addAttribute(aOperands);

	aResult = nAttr.create("result", "r", MFnNumericData::kDouble, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(false); nAttr.setStorable(false);
	nAttr.setWritable(false);
	addAttribute(aResult);

	attributeAffects(aOperands, aResult);

	return MS::kSuccess;
}


void Multiply::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus Multiply::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;

	if (plug == aResult)
	{

		MArrayDataHandle inOperands = dataBlock.inputArrayValue(aOperands);
		int elementCount = inOperands.elementCount();
		inOperands.jumpToArrayElement(0);
		double result = inOperands.inputValue().asDouble();
		for (int i = 1; i < elementCount; i++)
		{
			inOperands.jumpToArrayElement(i);
			result *= inOperands.inputValue().asDouble();
		}
		dataBlock.outputValue(aResult).set(result);
		dataBlock.outputValue(aResult).setClean();
		status = MS::kSuccess;
	}
	return status;
}

MStatus Multiply::initialize()
{
	MStatus status;

	MFnNumericAttribute nAttr;

	aOperands = nAttr.create("operands", "ops", MFnNumericData::kDouble, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setArray(true);
	nAttr.setUsesArrayDataBuilder(false); nAttr.setChannelBox(true);
	nAttr.setConnectable(true);
	addAttribute(aOperands);

	aResult = nAttr.create("result", "r", MFnNumericData::kDouble, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(false); nAttr.setStorable(false);
	nAttr.setWritable(false);
	addAttribute(aResult);

	attributeAffects(aOperands, aResult);

	return MS::kSuccess;
}

void Divide::postConstructor()
{
	this->setExistWithoutOutConnections(true);
	this->setExistWithoutInConnections(true);
}

MStatus Divide::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;
	if (plug == aResult)
	{
		float value = dataBlock.inputValue(aValue).asFloat();
		float divisor = dataBlock.inputValue(aDivisor).asFloat();
		MDataHandle out = dataBlock.outputValue(aResult);
		
		if (utils::almostEqual(divisor, 0.0f, 2))
		{
			out.set(0.0f);
			out.setClean();
			return MS::kSuccess;
		}
		out.set(value / divisor);
		out.setClean();
		status = MS::kSuccess;
	}
	return status;
}
MStatus Divide::initialize()
{
	MStatus status;
	MFnNumericAttribute nAttr;

	aValue = nAttr.create("value", "val", MFnNumericData::kFloat, 0.0, &status);
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

	aResult = nAttr.create("result", "r", MFnNumericData::kFloat, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(false); nAttr.setStorable(false);
	nAttr.setWritable(false);
	addAttribute(aResult);

	attributeAffects(aValue, aResult);
	attributeAffects(aDivisor, aResult);

	return MS::kSuccess;

}


void Power::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus Power::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;
	if (plug == aResult)
	{
		double base = dataBlock.inputValue(aBase).asDouble();
		double exponent = dataBlock.inputValue(aExponent).asDouble();
		MDataHandle output = dataBlock.outputValue(aResult);
		output.set(pow(base, exponent));
		output.setClean();

		status = MS::kSuccess;
	}
	return status;
}

MStatus Power::initialize()
{
	MStatus status;
	MFnNumericAttribute nAttr;

	aResult = nAttr.create("result", "result", MFnNumericData::kDouble, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(false); nAttr.setStorable(false);
	nAttr.setWritable(false); nAttr.setChannelBox(false);
	addAttribute(aResult);

	aBase = nAttr.create("base", "base", MFnNumericData::kDouble, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setChannelBox(true);
	nAttr.setConnectable(true);
	addAttribute(aBase);

	aExponent = nAttr.create("exponent", "exp", MFnNumericData::kDouble, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setChannelBox(true);
	nAttr.setConnectable(true);
	addAttribute(aExponent);

	attributeAffects(aBase, aResult);
	attributeAffects(aExponent, aResult);

	return MS::kSuccess;
}

void Clamp::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus Clamp::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;
	if (plug == aResult)
	{
	
		double mn = dataBlock.inputValue(aMin).asDouble();
		double mx = dataBlock.inputValue(aMax).asDouble();

		MArrayDataHandle inOperands = dataBlock.inputArrayValue(aOperands);
		MArrayDataHandle inResult = dataBlock.outputValue(aResult, &status);
		unsigned int inCount = inOperands.elementCount();
		MArrayDataBuilder resultBuilder = inResult.builder();

		for (unsigned int i = 0; i < inResult.elementCount(); i++)
		{
			resultBuilder.removeElement(i);
		}
		resultBuilder.growArray(inCount);
		for (unsigned int i = 0; i < inCount; i++)
		{
			MDataHandle currentDataHandle = resultBuilder.addElement(i);
			inOperands.jumpToArrayElement(i);
			currentDataHandle.setDouble(max(mn, min(inOperands.inputValue().asDouble(), mx)));

		}
		inResult.set(resultBuilder);
		inResult.setAllClean();
		status = MS::kSuccess;
	}
	return status;
}

MStatus Clamp::initialize()
{
	MStatus status;
	MFnNumericAttribute nAttr;
	
	aResult = nAttr.create("result", "result", MFnNumericData::kDouble, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(false); nAttr.setStorable(false);
	nAttr.setWritable(false); nAttr.setArray(true);
	nAttr.setUsesArrayDataBuilder(true);
	nAttr.setUsesArrayDataBuilder(true);
	addAttribute(aResult);

	aMin = nAttr.create("min", "mn", MFnNumericData::kDouble, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setChannelBox(true);
	nAttr.setConnectable(true);
	addAttribute(aMin);
	
	aMax = nAttr.create("max", "mx", MFnNumericData::kDouble, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setChannelBox(true);
	nAttr.setConnectable(true);
	addAttribute(aMax);

	aOperands = nAttr.create("operands", "ops", MFnNumericData::kDouble, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setArray(true);
	nAttr.setChannelBox(true); nAttr.setConnectable(true);
	addAttribute(aOperands);

	attributeAffects(aOperands, aResult);
	attributeAffects(aMin, aResult);
	attributeAffects(aMax, aResult);
	return status;
}


void Floor::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}
MStatus Floor::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;
	if (plug == aResult)
	{
		double value = dataBlock.inputValue(aValue).asDouble();
		MDataHandle output = dataBlock.outputValue(aResult);
		output.set(floor(value));
		output.setClean();
		status = MS::kSuccess;
	}
	return status;
}
MStatus Floor::initialize()
{
	MStatus status;
	MFnNumericAttribute nAttr;
	aValue = nAttr.create("value", "v", MFnNumericData::kDouble, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setChannelBox(true);
	nAttr.setConnectable(true);
	addAttribute(aValue);

	aResult = nAttr.create("result", "result", MFnNumericData::kDouble, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(false); nAttr.setStorable(false);
	nAttr.setWritable(false);
	addAttribute(aResult);

	attributeAffects(aValue, aResult);
	return status;
}


void Ceiling::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}
MStatus Ceiling::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;
	if (plug == aResult)
	{
		double value = dataBlock.inputValue(aValue).asDouble();
		MDataHandle output = dataBlock.outputValue(aResult);
		output.set(ceil(value));
		output.setClean();
		status = MS::kSuccess;
	}
	return status;
}
MStatus Ceiling::initialize()
{
	MStatus status;
	MFnNumericAttribute nAttr;
	aValue = nAttr.create("value", "v", MFnNumericData::kDouble, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setChannelBox(true);
	nAttr.setConnectable(true);
	addAttribute(aValue);

	aResult = nAttr.create("result", "result", MFnNumericData::kDouble, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(false); nAttr.setStorable(false);
	nAttr.setWritable(false);
	addAttribute(aResult);

	attributeAffects(aValue, aResult);
	return status;
}


void Round::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus Round::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;
	if (plug == aResult)
	{
		double value = dataBlock.inputValue(aValue).asDouble();
		MDataHandle output = dataBlock.outputValue(aResult);
		output.set(round(value));
		output.setClean();
		status = MS::kSuccess;
	}
	return status;

}
MStatus Round::initialize()
{
	MStatus status;
	MFnNumericAttribute nAttr;

	aValue = nAttr.create("value", "v", MFnNumericData::kDouble, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setChannelBox(true);
	nAttr.setConnectable(true);
	addAttribute(aValue);

	aResult = nAttr.create("result", "result", MFnNumericData::kDouble, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(false); nAttr.setStorable(false);
	nAttr.setWritable(false);
	addAttribute(aResult);

	attributeAffects(aValue, aResult);

	return status;
}


void Truncate::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus Truncate::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;
	if (plug == aResult)
	{
		double value = dataBlock.inputValue(aValue).asDouble();
		MDataHandle output = dataBlock.outputValue(aResult);
		output.set(trunc(value));
		output.setClean();
		status = MS::kSuccess;
	}
	return status;

}
MStatus Truncate::initialize()
{
	MStatus status;
	MFnNumericAttribute nAttr;

	aValue = nAttr.create("value", "v", MFnNumericData::kDouble, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setChannelBox(true);
	nAttr.setConnectable(true);
	addAttribute(aValue);

	aResult = nAttr.create("result", "result", MFnNumericData::kDouble, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(false); nAttr.setStorable(false);
	nAttr.setWritable(false);
	addAttribute(aResult);

	attributeAffects(aValue, aResult);

	return status;
}



void BlendPair::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus BlendPair::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;
	if (plug == aResult)
	{
		float valueA = dataBlock.inputValue(aValueA).asFloat();
		float valueB = dataBlock.inputValue(aValueB).asFloat();
		float blend = dataBlock.inputValue(aBlend).asFloat();
		MDataHandle result = dataBlock.outputValue(aResult);

		result.set(utils::lerp(valueB, valueA, blend));
		result.setClean();
		status = MS::kSuccess;
	}
	return status;

}
MStatus BlendPair::initialize()
{
	MStatus status;
	MFnNumericAttribute nAttr;

	aResult = nAttr.create("result", "r", MFnNumericData::kFloat, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(false); nAttr.setStorable(false);
	nAttr.setWritable(false);
	addAttribute(aResult);

	aBlend = nAttr.create("blend", "b", MFnNumericData::kFloat, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setChannelBox(true);
	nAttr.setConnectable(true);
	addAttribute(aBlend);

	aValueA = nAttr.create("valueA", "va", MFnNumericData::kFloat, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setChannelBox(true);
	nAttr.setConnectable(true);
	addAttribute(aValueA);

	aValueB = nAttr.create("valueB", "vb", MFnNumericData::kFloat, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setChannelBox(true);
	nAttr.setConnectable(true);
	addAttribute(aValueB);

	attributeAffects(aValueA, aResult);
	attributeAffects(aValueB, aResult);
	attributeAffects(aBlend, aResult);

	return status;
}


void Gaussian::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus Gaussian::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;
	if (plug == aResult)
	{
		float inValue = dataBlock.inputValue(aInValue).asFloat();
		float magnitude = dataBlock.inputValue(aMagnitude).asFloat();
		float mean = dataBlock.inputValue(aMean).asFloat();
		float variance = dataBlock.inputValue(aVariance).asFloat();

		MDataHandle out = dataBlock.outputValue(aResult);

		if (variance <= 0.0f)
		{
			variance = 0.001f;
		}
		float xMinusB = inValue - mean;
		float output = magnitude * exp(-(xMinusB * xMinusB) /(2.0f*variance));
		out.setFloat(output);
		out.setClean();

		status = MS::kSuccess;
	}
	return status;

}

MStatus Gaussian::initialize()
{
	MStatus status;
	MFnNumericAttribute nAttr;

	aResult = nAttr.create("result", "r", MFnNumericData::kFloat, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(false); nAttr.setStorable(false);
	nAttr.setWritable(false);
	addAttribute(aResult);
	
	aInValue = nAttr.create("value", "v", MFnNumericData::kFloat, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setChannelBox(true);
	nAttr.setConnectable(true);
	addAttribute(aInValue);

	aMagnitude = nAttr.create("magnitude", "mag", MFnNumericData::kFloat, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setChannelBox(true);
	nAttr.setConnectable(true);
	addAttribute(aMagnitude);

	aMean = nAttr.create("mean", "vb", MFnNumericData::kFloat, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setChannelBox(true);
	nAttr.setConnectable(true);
	addAttribute(aMean);

	aVariance = nAttr.create("variance", "var", MFnNumericData::kFloat, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setChannelBox(true);
	nAttr.setConnectable(true);
	addAttribute(aVariance);

	attributeAffects(aInValue, aResult);
	attributeAffects(aMagnitude, aResult);
	attributeAffects(aMean, aResult);
	attributeAffects(aInValue, aResult);

	return status;
}


void Remap::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus Remap::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;
	if (plug == aResult)
	{
		MDataHandle result = dataBlock.outputValue(aResult);
		float oldMin = dataBlock.inputValue(aOldMin).asFloat();
		float oldMax = dataBlock.inputValue(aOldMax).asFloat();
		float newMin = dataBlock.inputValue(aNewMin).asFloat();
		float newMax = dataBlock.inputValue(aNewMax).asFloat();
		float value = dataBlock.inputValue(aInValue).asFloat();

		result.setFloat(utils::remap(value, oldMin, oldMax, newMin, newMax));
		result.setClean();

		status = MS::kSuccess;
	}
	return status;

}

MStatus Remap::initialize()
{
	MStatus status;
	MFnNumericAttribute nAttr;
	aResult = nAttr.create("result", "result", MFnNumericData::kFloat, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(false); nAttr.setStorable(false);
	nAttr.setWritable(false);
	addAttribute(aResult);

	aInValue = nAttr.create("value", "value", MFnNumericData::kFloat, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setChannelBox(true);
	nAttr.setConnectable(true);
	addAttribute(aInValue);

	
	aOldMin = nAttr.create("oldMin", "oldMin", MFnNumericData::kFloat, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setChannelBox(true);
	nAttr.setConnectable(true);
	addAttribute(aOldMin);

	
	aOldMax = nAttr.create("oldMax", "oldMax", MFnNumericData::kFloat, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setChannelBox(true);
	nAttr.setConnectable(true);
	addAttribute(aOldMax);

	aNewMin = nAttr.create("newMin", "newMin", MFnNumericData::kFloat, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setChannelBox(true);
	nAttr.setConnectable(true);
	addAttribute(aNewMin);

	aNewMax = nAttr.create("newMax", "newMax", MFnNumericData::kFloat, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true); nAttr.setStorable(true);
	nAttr.setWritable(true); nAttr.setChannelBox(true);
	nAttr.setConnectable(true);
	addAttribute(aNewMax);

	attributeAffects(aInValue, aResult);
	attributeAffects(aOldMax, aResult);
	attributeAffects(aOldMin, aResult);
	attributeAffects(aNewMin, aResult);
	attributeAffects(aNewMax, aResult);
	
	return status;
}
