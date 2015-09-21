#include "DsPointOnCurve.h"


MTypeId DsPointOnCurve::id(0x00124506);

MObject DsPointOnCurve::aInputValue;
MObject DsPointOnCurve::aInputCurve;
MObject DsPointOnCurve::aPosition;

void* DsPointOnCurve::creator()
{
	return new DsPointOnCurve();
}

MStatus DsPointOnCurve::compute(const MPlug& plug, MDataBlock& dataBlock)
{	
	MStatus	status;
	if (plug != aPosition)
	{	
		return MS::kSuccess;
	}

	//get values from datablock
	MObject crvV = dataBlock.inputValue(aInputCurve).asNurbsCurve();
	double inVal = dataBlock.inputValue(aInputValue).asDouble();

	double outVal;
	MPoint outPos;

	MFnNurbsCurve crvfn(crvV);

	outVal = crvfn.findParamFromLength(inVal, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status)
	crvfn.getPointAtParam(outVal, outPos, MSpace::kWorld);
	//set the output 
	MDataHandle hOutPos = dataBlock.outputValue(aPosition, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	hOutPos.set((float)outPos.x, (float)outPos.y, (float)outPos.z);
	hOutPos.setClean();

	return MS::kSuccess;

}




MStatus DsPointOnCurve::initialize()
{
	MStatus status;
	//pointers for attributes
	MFnNumericAttribute nAttr;
	MFnTypedAttribute tAttr;
	//attribute setup

	
	aInputValue = nAttr.create("inputValue", "inputValue", MFnNumericData::kDouble, 0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true);
	nAttr.setStorable(true);
	tAttr.setWritable(true);
	addAttribute(aInputValue);

	aInputCurve = tAttr.create("inputCurve", "inputCurve", MFnData::kNurbsCurve, MObject::kNullObj, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	tAttr.setKeyable(true);
	tAttr.setStorable(true);
	tAttr.setWritable(true);
	addAttribute(aInputCurve);

	
	aPosition = nAttr.createPoint("position", "pos", &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(false);
	nAttr.setStorable(false);
	nAttr.setWritable(false);
	addAttribute(aPosition);

	attributeAffects(aInputCurve, aPosition);

	attributeAffects(aInputValue, aPosition);

	return MS::kSuccess;
}

