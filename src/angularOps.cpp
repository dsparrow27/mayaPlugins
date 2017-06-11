#include "angularOps.h"

MObject AngularCosine::aResult;
MObject AngularCosine::aValue;

MObject AngularSine::aResult;
MObject AngularSine::aValue;

MObject AngularTan::aResult;
MObject AngularTan::aValue;
MObject AngularSum::aOperands;
MObject AngularSum::aResult;

MObject AngularSubstract::aOperands;
MObject AngularSubstract::aResult;

MObject AngularMultiply::aOperands;
MObject AngularMultiply::aResult;

MObject AngularDivide::aDivisor;
MObject AngularDivide::aValue;
MObject AngularDivide::aResult;

MObject AngularPower::aBase;
MObject AngularPower::aExponent;
MObject AngularPower::aResult;

MObject AngularClamp::aOperands;
MObject AngularClamp::aResult;
MObject AngularClamp::aMin;
MObject AngularClamp::aMax;

MObject AngularFloor::aValue;
MObject AngularFloor::aResult;

MObject AngularCeiling::aValue;
MObject AngularCeiling::aResult;

MObject AngularRound::aValue;
MObject AngularRound::aResult;

MObject AngularTruncate::aValue;
MObject AngularTruncate::aResult;

MObject AngularBlendPair::aBlend;
MObject AngularBlendPair::aValueA;
MObject AngularBlendPair::aValueB;
MObject AngularBlendPair::aResult;

MObject AngularGaussian::aResult;
MObject AngularGaussian::aInValue;
MObject AngularGaussian::aMagnitude;
MObject AngularGaussian::aMean;
MObject AngularGaussian::aVariance;

MObject AngularRemap::aResult;
MObject AngularRemap::aInValue;
MObject AngularRemap::aOldMin;
MObject AngularRemap::aOldMax;
MObject AngularRemap::aNewMin;
MObject AngularRemap::aNewMax;

MObject AngularNegate::aOperands;
MObject AngularNegate::aResult;


void AngularSum::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus AngularSum::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;

	if (plug == aResult)
	{

		MArrayDataHandle inOperands = dataBlock.inputArrayValue(aOperands);
		int elementCount = inOperands.elementCount();
		inOperands.jumpToArrayElement(0);
		double result = inOperands.inputValue().asAngle().asDegrees();
		for (int i = 1; i < elementCount; i++)
		{
			inOperands.jumpToArrayElement(i);
			result += inOperands.inputValue().asAngle().asDegrees();
		}
		dataBlock.outputValue(aResult).setMAngle(MAngle(result, MAngle::kDegrees));
		dataBlock.outputValue(aResult).setClean();
		status = MS::kSuccess;
	}
	return status;
}

MStatus AngularSum::initialize()
{
	MStatus status;

	MFnUnitAttribute uAttr;

	aOperands = uAttr.create("operands", "ops", MFnUnitAttribute::kAngle, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_INPUT(uAttr);
	uAttr.setArray(true);
	uAttr.setUsesArrayDataBuilder(false);
	addAttribute(aOperands);

	aResult = uAttr.create("result", "r", MFnUnitAttribute::kAngle, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_OUTPUT(uAttr);
	addAttribute(aResult);

	attributeAffects(aOperands, aResult);

	return MS::kSuccess;
}


void AngularSubstract::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus AngularSubstract::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;

	if (plug == aResult)
	{

		MArrayDataHandle inOperands = dataBlock.inputArrayValue(aOperands);
		int elementCount = inOperands.elementCount();

		MDataHandle outHandle = dataBlock.outputValue(aResult);
		if (elementCount < 1)
		{
			outHandle.setMAngle(MAngle(-1.0, MAngle::kDegrees));
			outHandle.setClean();
			return MS::kSuccess;
		}
		inOperands.jumpToArrayElement(0);
		double result = inOperands.inputValue().asAngle().asDegrees();

		for (int i = 0; i < elementCount; i++)
		{
			inOperands.jumpToArrayElement(i);
			result -= inOperands.inputValue().asAngle().asDegrees();
		}
		outHandle.setMAngle(MAngle(result, MAngle::kDegrees));
		outHandle.setClean();

		status = MS::kSuccess;
	}
	return status;
}

MStatus AngularSubstract::initialize()
{
	MStatus status;

	MFnUnitAttribute uAttr;

	aOperands = uAttr.create("operands", "ops", MFnUnitAttribute::kAngle, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	uAttr.setArray(true); uAttr.setUsesArrayDataBuilder(false);
	AS_INPUT(uAttr);
	addAttribute(aOperands);

	aResult = uAttr.create("result", "r", MFnUnitAttribute::kAngle, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_OUTPUT(uAttr);
	addAttribute(aResult);

	attributeAffects(aOperands, aResult);

	return MS::kSuccess;
}


void AngularMultiply::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus AngularMultiply::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;

	if (plug == aResult)
	{

		MArrayDataHandle inOperands = dataBlock.inputArrayValue(aOperands);
		int elementCount = inOperands.elementCount();
		inOperands.jumpToArrayElement(0);
		double result = inOperands.inputValue().asAngle().asDegrees();
		for (int i = 1; i < elementCount; i++)
		{
			inOperands.jumpToArrayElement(i);
			result *= inOperands.inputValue().asAngle().asDegrees();
		}
		MDataHandle outHandle = dataBlock.outputValue(aResult);
		outHandle.setMAngle(MAngle(result, MAngle::kDegrees));
		outHandle.setClean();
		status = MS::kSuccess;
	}
	return status;
}

MStatus AngularMultiply::initialize()
{
	MStatus status;

	MFnUnitAttribute uAttr;

	aOperands = uAttr.create("operands", "ops", MFnUnitAttribute::kAngle, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	uAttr.setArray(true); uAttr.setUsesArrayDataBuilder(false);
	AS_INPUT(uAttr);
	addAttribute(aOperands);

	aResult = uAttr.create("result", "r", MFnUnitAttribute::kAngle, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_OUTPUT(uAttr);
	addAttribute(aResult);

	attributeAffects(aOperands, aResult);

	return MS::kSuccess;
}

void AngularDivide::postConstructor()
{
	this->setExistWithoutOutConnections(true);
	this->setExistWithoutInConnections(true);
}

MStatus AngularDivide::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;
	if (plug == aResult)
	{
		double value = dataBlock.inputValue(aValue).asAngle().asDegrees();
		double divisor = dataBlock.inputValue(aDivisor).asAngle().asDegrees();
		MDataHandle out = dataBlock.outputValue(aResult);

		if (utils::almostEqual(divisor, 0.0, 2))
		{
			out.setMAngle(MAngle(0.0, MAngle::kDegrees));
			out.setClean();
			return MS::kSuccess;
		}
		out.setMAngle(MAngle(value / divisor, MAngle::kDegrees));
		out.setClean();
		status = MS::kSuccess;
	}
	return status;
}
MStatus AngularDivide::initialize()
{
	MStatus status;
	MFnUnitAttribute uAttr;

	aValue = uAttr.create("value", "val", MFnUnitAttribute::kAngle, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_INPUT(uAttr);
	addAttribute(aValue);

	aDivisor = uAttr.create("divisor", "div", MFnUnitAttribute::kAngle, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_INPUT(uAttr);
	addAttribute(aDivisor);

	aResult = uAttr.create("result", "r", MFnUnitAttribute::kAngle, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_OUTPUT(uAttr);

	addAttribute(aResult);
	
	attributeAffects(aValue, aResult);
	attributeAffects(aDivisor, aResult);

	return MS::kSuccess;

}


void AngularPower::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus AngularPower::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;
	if (plug == aResult)
	{
		double base = dataBlock.inputValue(aBase).asAngle().asDegrees();
		double exponent = dataBlock.inputValue(aExponent).asAngle().asDegrees();
		MDataHandle output = dataBlock.outputValue(aResult);
		output.setMAngle(MAngle(pow(base, exponent), MAngle::kDegrees));
		output.setClean();

		status = MS::kSuccess;
	}
	return status;
}

MStatus AngularPower::initialize()
{
	MStatus status;
	MFnUnitAttribute uAttr;

	aResult = uAttr.create("result", "result", MFnUnitAttribute::kAngle, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_OUTPUT(uAttr);
	addAttribute(aResult);

	aBase = uAttr.create("base", "base", MFnUnitAttribute::kAngle, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_INPUT(uAttr);
	addAttribute(aBase);

	aExponent = uAttr.create("exponent", "exp", MFnUnitAttribute::kAngle, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_INPUT(uAttr);
	addAttribute(aExponent);

	attributeAffects(aBase, aResult);
	attributeAffects(aExponent, aResult);

	return MS::kSuccess;
}

void AngularClamp::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus AngularClamp::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;
	if (plug == aResult)
	{

		double mn = dataBlock.inputValue(aMin).asAngle().asDegrees();
		double mx = dataBlock.inputValue(aMax).asAngle().asDegrees();

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
			currentDataHandle.setMAngle(MAngle(max(mn, min(inOperands.inputValue().asAngle().asDegrees(), mx)), MAngle::kDegrees));

		}
		inResult.set(resultBuilder);
		inResult.setAllClean();
		status = MS::kSuccess;
	}
	return status;
}

MStatus AngularClamp::initialize()
{
	MStatus status;
	MFnUnitAttribute uAttr;
	MFnNumericAttribute nAttr;

	aResult = uAttr.create("result", "result", MFnUnitAttribute::kAngle, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	uAttr.setArray(true); uAttr.setUsesArrayDataBuilder(true);
	AS_OUTPUT(uAttr);
	addAttribute(aResult);

	aMin = uAttr.create("min", "mn", MFnUnitAttribute::kAngle, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_INPUT(uAttr);
	addAttribute(aMin);

	aMax = uAttr.create("max", "mx", MFnUnitAttribute::kAngle, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_INPUT(uAttr);
	addAttribute(aMax);

	aOperands = uAttr.create("operands", "ops", MFnUnitAttribute::kAngle, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	uAttr.setArray(true);
	AS_INPUT(uAttr);
	addAttribute(aOperands);

	attributeAffects(aOperands, aResult);
	attributeAffects(aMin, aResult);
	attributeAffects(aMax, aResult);
	return status;
}


void AngularFloor::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}
MStatus AngularFloor::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;
	if (plug == aResult)
	{
		double value = dataBlock.inputValue(aValue).asAngle().asDegrees();
		MDataHandle output = dataBlock.outputValue(aResult);
		output.setMAngle(MAngle(floor(value), MAngle::kDegrees));
		output.setClean();
		status = MS::kSuccess;
	}
	return status;
}
MStatus AngularFloor::initialize()
{
	MStatus status;
	MFnUnitAttribute uAttr;
	aValue = uAttr.create("value", "v", MFnUnitAttribute::kAngle, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_INPUT(uAttr);
	addAttribute(aValue);

	aResult = uAttr.create("result", "result", MFnUnitAttribute::kAngle, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_OUTPUT(uAttr);
	addAttribute(aResult);

	attributeAffects(aValue, aResult);
	return status;
}


void AngularCeiling::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}
MStatus AngularCeiling::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;
	if (plug == aResult)
	{
		double value = dataBlock.inputValue(aValue).asAngle().asDegrees();
		MDataHandle output = dataBlock.outputValue(aResult);
		output.setMAngle(MAngle(ceil(value), MAngle::kDegrees));
		output.setClean();
		status = MS::kSuccess;
	}
	return status;
}
MStatus AngularCeiling::initialize()
{
	MStatus status;
	MFnUnitAttribute uAttr;
	aValue = uAttr.create("value", "v", MFnUnitAttribute::kAngle, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_INPUT(uAttr);
	addAttribute(aValue);

	aResult = uAttr.create("result", "result", MFnUnitAttribute::kAngle, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_OUTPUT(uAttr);
	addAttribute(aResult);

	attributeAffects(aValue, aResult);
	return status;
}


void AngularRound::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus AngularRound::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;
	if (plug == aResult)
	{
		double value = dataBlock.inputValue(aValue).asAngle().asDegrees();
		MDataHandle output = dataBlock.outputValue(aResult);
		output.setMAngle(MAngle(round(value), MAngle::kDegrees));
		output.setClean();
		status = MS::kSuccess;
	}
	return status;

}
MStatus AngularRound::initialize()
{
	MStatus status;
	MFnUnitAttribute uAttr;

	aValue = uAttr.create("value", "v", MFnUnitAttribute::kAngle, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_INPUT(uAttr);
	addAttribute(aValue);

	aResult = uAttr.create("result", "result", MFnUnitAttribute::kAngle, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_OUTPUT(uAttr);
	addAttribute(aResult);

	attributeAffects(aValue, aResult);

	return status;
}


void AngularTruncate::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus AngularTruncate::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;
	if (plug == aResult)
	{
		double value = dataBlock.inputValue(aValue).asAngle().asDegrees();
		MDataHandle output = dataBlock.outputValue(aResult);
		output.setMAngle(MAngle(trunc(value), MAngle::kDegrees));
		output.setClean();
		status = MS::kSuccess;
	}
	return status;

}
MStatus AngularTruncate::initialize()
{
	MStatus status;
	MFnUnitAttribute uAttr;

	aValue = uAttr.create("value", "v", MFnUnitAttribute::kAngle, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_INPUT(uAttr);
	addAttribute(aValue);

	aResult = uAttr.create("result", "result", MFnUnitAttribute::kAngle, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_OUTPUT(uAttr);
	addAttribute(aResult);

	attributeAffects(aValue, aResult);

	return status;
}



void AngularBlendPair::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus AngularBlendPair::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;
	if (plug == aResult)
	{
		double valueA = dataBlock.inputValue(aValueA).asAngle().asDegrees();
		double valueB = dataBlock.inputValue(aValueB).asAngle().asDegrees();
		double blend = dataBlock.inputValue(aBlend).asDouble();
		MDataHandle result = dataBlock.outputValue(aResult);
		result.setMAngle(MAngle(utils::lerp(valueB, valueA, blend), MAngle::kDegrees));
		result.setClean();
		status = MS::kSuccess;
	}
	return status;

}
MStatus AngularBlendPair::initialize()
{
	MStatus status;
	MFnUnitAttribute uAttr;
	MFnNumericAttribute nAttr;


	aResult = uAttr.create("result", "r", MFnUnitAttribute::kAngle, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_OUTPUT(uAttr);
	addAttribute(aResult);

	aBlend = nAttr.create("blend", "b", MFnNumericData::kDouble, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_INPUT(nAttr);
	addAttribute(aBlend);

	aValueA = uAttr.create("valueA", "va", MFnUnitAttribute::kAngle, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_INPUT(uAttr);
	addAttribute(aValueA);

	aValueB = uAttr.create("valueB", "vb", MFnUnitAttribute::kAngle, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_INPUT(uAttr);
	addAttribute(aValueB);

	attributeAffects(aValueA, aResult);
	attributeAffects(aValueB, aResult);
	attributeAffects(aBlend, aResult);

	return status;
}


void AngularGaussian::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus AngularGaussian::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;
	if (plug == aResult)
	{
		double inValue = dataBlock.inputValue(aInValue).asAngle().asDegrees();
		double magnitude = dataBlock.inputValue(aMagnitude).asAngle().asDegrees();
		double mean = dataBlock.inputValue(aMean).asAngle().asDegrees();
		double variance = dataBlock.inputValue(aVariance).asAngle().asDegrees();

		MDataHandle out = dataBlock.outputValue(aResult);

		if (variance <= 0.0f)
		{
			variance = 0.001f;
		}
		double xMinusB = inValue - mean;
		double output = magnitude * exp(-(xMinusB * xMinusB) / (2.0*variance));
		out.setMAngle(MAngle(output, MAngle::kDegrees));
		out.setClean();

		status = MS::kSuccess;
	}
	return status;

}

MStatus AngularGaussian::initialize()
{
	MStatus status;
	MFnUnitAttribute uAttr;

	aResult = uAttr.create("result", "r", MFnUnitAttribute::kAngle, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_OUTPUT(uAttr);
	addAttribute(aResult);

	aInValue = uAttr.create("value", "v", MFnUnitAttribute::kAngle, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_INPUT(uAttr);
	addAttribute(aInValue);

	aMagnitude = uAttr.create("magnitude", "mag", MFnUnitAttribute::kAngle, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_INPUT(uAttr);
	addAttribute(aMagnitude);

	aMean = uAttr.create("mean", "vb", MFnUnitAttribute::kAngle, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_INPUT(uAttr);
	addAttribute(aMean);

	aVariance = uAttr.create("variance", "var", MFnUnitAttribute::kAngle, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_INPUT(uAttr);
	addAttribute(aVariance);

	attributeAffects(aInValue, aResult);
	attributeAffects(aMagnitude, aResult);
	attributeAffects(aMean, aResult);
	attributeAffects(aInValue, aResult);

	return status;
}


void AngularRemap::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus AngularRemap::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;
	if (plug == aResult)
	{
		MDataHandle result = dataBlock.outputValue(aResult);
		double oldMin = dataBlock.inputValue(aOldMin).asAngle().asDegrees();
		double oldMax = dataBlock.inputValue(aOldMax).asAngle().asDegrees();
		double newMin = dataBlock.inputValue(aNewMin).asAngle().asDegrees();
		double newMax = dataBlock.inputValue(aNewMax).asAngle().asDegrees();
		double value = dataBlock.inputValue(aInValue).asAngle().asDegrees();

		result.setMAngle(MAngle((double)utils::remap(value, oldMin, oldMax, newMin, newMax), MAngle::kDegrees));
		result.setClean();

		status = MS::kSuccess;
	}
	return status;

}

MStatus AngularRemap::initialize()
{
	MStatus status;
	MFnUnitAttribute uAttr;
	aResult = uAttr.create("result", "result", MFnUnitAttribute::kAngle, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_OUTPUT(uAttr);
	addAttribute(aResult);

	aInValue = uAttr.create("value", "value", MFnUnitAttribute::kAngle, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_INPUT(uAttr);
	addAttribute(aInValue);


	aOldMin = uAttr.create("oldMin", "oldMin", MFnUnitAttribute::kAngle, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_INPUT(uAttr);
	addAttribute(aOldMin);


	aOldMax = uAttr.create("oldMax", "oldMax", MFnUnitAttribute::kAngle, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_INPUT(uAttr);
	addAttribute(aOldMax);

	aNewMin = uAttr.create("newMin", "newMin", MFnUnitAttribute::kAngle, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_INPUT(uAttr);
	addAttribute(aNewMin);

	aNewMax = uAttr.create("newMax", "newMax", MFnUnitAttribute::kAngle, (0.0), &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_INPUT(uAttr);
	addAttribute(aNewMax);

	attributeAffects(aInValue, aResult);
	attributeAffects(aOldMax, aResult);
	attributeAffects(aOldMin, aResult);
	attributeAffects(aNewMin, aResult);
	attributeAffects(aNewMax, aResult);

	return status;
}

void AngularNegate::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus AngularNegate::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus status = MS::kUnknownParameter;
	if (plug == aResult)
	{
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
			currentDataHandle.setMAngle(MAngle(-inOperands.inputValue().asAngle().asDegrees(), MAngle::kDegrees));

		}
		inResult.set(resultBuilder);
		inResult.setAllClean();
		status = MS::kSuccess;
	}
	return status;
}
MStatus AngularNegate::initialize()
{
	MStatus status;
	MFnUnitAttribute uAttr;

	aOperands = uAttr.create("operands", "ops", MFnUnitAttribute::kAngle, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	uAttr.setArray(true);
	AS_INPUT(uAttr);
	addAttribute(aOperands);

	aResult = uAttr.create("result", "result", MFnUnitAttribute::kAngle, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	uAttr.setArray(true); uAttr.setUsesArrayDataBuilder(true);
	AS_OUTPUT(uAttr);
	addAttribute(aResult);

	attributeAffects(aOperands, aResult);

	return status;
}


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
		out.setMAngle(MAngle(sin(value.asDegrees() * M_PI / 180), MAngle::kDegrees));
		out.setClean();
		status = MS::kSuccess;
	}
	return status;
}
MStatus AngularSine::initialize()
{
	MStatus status;
	MFnUnitAttribute uAttr;
	aValue = uAttr.create("value", "value", MFnUnitAttribute::kAngle, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_INPUT(uAttr);
	addAttribute(aValue);
	aResult = uAttr.create("result", "result", MFnUnitAttribute::kAngle, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_OUTPUT(uAttr);
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
		out.setMAngle(MAngle(cos(value.asDegrees() * M_PI / 180), MAngle::kDegrees));
		out.setClean();
		status = MS::kSuccess;
	}
	return status;
}
MStatus AngularCosine::initialize()
{
	MStatus status;
	MFnUnitAttribute uAttr;

	aValue = uAttr.create("value", "value", MFnUnitAttribute::kAngle, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_INPUT(uAttr);
	addAttribute(aValue);
	aResult = uAttr.create("result", "result", MFnUnitAttribute::kAngle, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_OUTPUT(uAttr);
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
		out.setMAngle(MAngle(tan(value.asDegrees() * M_PI / 180), MAngle::kDegrees));
		out.setClean();
		status = MS::kSuccess;
	}
	return status;
}

MStatus AngularTan::initialize()
{
	MStatus status;
	MFnUnitAttribute uAttr;

	aValue = uAttr.create("value", "value", MFnUnitAttribute::kAngle, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_INPUT(uAttr);
	addAttribute(aValue);
	aResult = uAttr.create("result", "result", MFnUnitAttribute::kAngle, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	AS_OUTPUT(uAttr);
	addAttribute(aResult);

	attributeAffects(aValue, aResult);
	return status;
}