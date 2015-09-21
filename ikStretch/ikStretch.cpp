#include "ikStretch.h"


MTypeId IkStretch::id(0x00124506);
MObject IkStretch::aStartMatrix;
MObject IkStretch::aEndMatrix;
MObject IkStretch::aPoleVectorMatrix;
MObject IkStretch::aUpInitLength;
MObject IkStretch::aDownInitLength;
MObject IkStretch::aUpScale;
MObject IkStretch::aDownScale;
MObject IkStretch::aStretch;
MObject IkStretch::aSlide;
MObject IkStretch::aGlobalScale;
MObject IkStretch::aPoleVectorLock;
MObject IkStretch::aDownStretch;
MObject IkStretch::aUpStretch;


IkStretch::IkStretch()
{

}


void* IkStretch::creator()
{
	return new IkStretch();
}


MStatus IkStretch::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus	status;

	if (plug != aUpScale || (plug != aDownScale))
	{
		return MS::kSuccess;
	}
	// get the input matrices
	MMatrix startMatrixV = dataBlock.inputValue(aStartMatrix).asMatrix();
	MMatrix endMatrixV = dataBlock.inputValue(aEndMatrix).asMatrix();
	MMatrix poleVectormatrixV = dataBlock.inputValue(aPoleVectorMatrix).asMatrix();
	// get the inital bone input lengths 
	double upInitLengthV = dataBlock.inputValue(aUpInitLength).asDouble();
	double downInitLengthV = dataBlock.inputValue(aDownInitLength).asDouble();
	//get all parameter inputs
	double stretchV = dataBlock.inputValue(aStretch).asDouble();
	double upStretchV = dataBlock.inputValue(aUpStretch).asDouble();
	double downStretchV = dataBlock.inputValue(aDownStretch).asDouble();
	double slideV = dataBlock.inputValue(aSlide).asDouble();
	double globalScaleV = dataBlock.inputValue(aGlobalScale).asDouble();
	double poleVectorLockV = dataBlock.inputValue(aPoleVectorLock).asDouble();

	//compute the total chain length (original)
	double chainLength = upInitLengthV + downInitLengthV;


	//compute the bone vectors
	MVector startVector(startMatrixV[3][0], startMatrixV[3][1], startMatrixV[3][2]);
	MVector endVector(endMatrixV[3][0], endMatrixV[3][1], endMatrixV[3][2]);
	MVector currentLengthVector = endVector - startVector;

	//compute length vector 
	chainLength *= globalScaleV;
	double currentLength = currentLengthVector.length();


	//create needed output varible
	double upScaleOut = upInitLengthV;
	double downScaleOut = downInitLengthV;
	double ratio, delta;
	/*
	Possible spot for smooth ik.
	*/

	if (stretchV > 0.001)
	{
		//get the ratio
		delta = currentLength / chainLength;
		// compute the stretch delta otherwise delta is 1
		if (delta > 1)
		{
			delta = ((delta - 1) * stretchV) + 1;
		}
		else
		{
			delta = 1;
		}

		upScaleOut *= delta;
		downScaleOut *= delta;

	}
	/*
		Calulate independent bone stretch for up and down bones,
		We're keeping this seperate from the stretch factor condition as this give a bit 
		more flexibility for the user.
	*/
	if (upStretchV > 0)
	{
		upScaleOut *= upStretchV ;
	}
	if (downStretchV > 0)
	{
		downScaleOut *= downStretchV;
	}

	//compute slide
	if (slideV >= 0)
	{
		ratio = chainLength / upInitLengthV;
		delta = (((ratio - 1) * slideV));
		upScaleOut = (delta + 1) * upScaleOut;
		downScaleOut = (1 - slideV) * downScaleOut;
	}
	else
	{
		ratio = chainLength / downInitLengthV;
		delta = (((ratio - 1) * -slideV));
		downScaleOut = (delta + 1) * downScaleOut;
		upScaleOut = (1 + slideV) * upScaleOut;
	}

	//elbow lock
	if (poleVectorLockV > 0.001)
	{
		MVector polePos(poleVectormatrixV[3][0],
		poleVectormatrixV[3][1],
		poleVectormatrixV[3][2]);
		//compute the length of the vector needed to snap
		MVector startPole = polePos - startVector;
		MVector endPole = endVector - polePos;
		double startPosLen = startPole.length() / globalScaleV;
		double endPosLen = endPole.length() / globalScaleV;

		//linear interpolate
		upScaleOut = (upScaleOut * (1 - poleVectorLockV)) + (startPosLen * poleVectorLockV);
		downScaleOut = (downScaleOut * (1 - poleVectorLockV)) + (endPosLen * poleVectorLockV);

	}
		

	//output
	dataBlock.outputValue(aDownScale).set(downScaleOut);
	dataBlock.outputValue(aDownScale).setClean();
	dataBlock.outputValue(aUpScale).set(upScaleOut);
	dataBlock.outputValue(aUpScale).setClean();


	return MS::kSuccess;
}


MStatus IkStretch::initialize()
{
	MStatus status;
	//pointers for attributes
	MFnNumericAttribute nAttr;
	MFnMatrixAttribute mAttr;
	
	//attribute setup
	//start matrix
	aStartMatrix = mAttr.create("startMatrix", "smt", MFnMatrixAttribute::kDouble, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	mAttr.setStorable(true);
	mAttr.setKeyable(true);
	addAttribute(aStartMatrix);
	//end matrix
	aEndMatrix = mAttr.create("endMatrix", "enm", MFnMatrixAttribute::kDouble, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	mAttr.setStorable(true);
	mAttr.setKeyable(true);
	addAttribute(aEndMatrix);
	//polevector matrix
	aPoleVectorMatrix = mAttr.create("poleVectorMatrix", "pvm", MFnMatrixAttribute::kDouble, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	mAttr.setStorable(true);
	mAttr.setKeyable(true);
	addAttribute(aPoleVectorMatrix);
	//poleVector lock 
	aPoleVectorLock = nAttr.create("poleVectorLock", "pvl", MFnNumericData::kDouble, 0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setStorable(true);
	nAttr.setKeyable(true);
	nAttr.setMin(0.0);
	nAttr.setMax(1.0);
	addAttribute(aPoleVectorLock);
	
	// init up length
	aUpInitLength = nAttr.create("upInitLength", "uil", MFnNumericData::kDouble, 0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setStorable(true);
	nAttr.setKeyable(true);
	nAttr.setMin(0.001);
	addAttribute(aUpInitLength);
	//init down length
	aDownInitLength = nAttr.create("downInitLength", "dil", MFnNumericData::kDouble, 0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setStorable(true);
	nAttr.setKeyable(true);
	nAttr.setMin(0.001);
	addAttribute(aDownInitLength);
	//slide
	aSlide = nAttr.create("slide", "sld", MFnNumericData::kDouble, 0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setStorable(true);
	nAttr.setKeyable(true);
	nAttr.setMin(-1.0);
	nAttr.setMax(1.0);
	addAttribute(aSlide);

	//stretch
	aStretch = nAttr.create("stretch", "str", MFnNumericData::kDouble, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setStorable(true);
	nAttr.setKeyable(true);
	nAttr.setMin(0.0);
	nAttr.setMax(1.0);
	addAttribute(aStretch);
	
	//upStretch
	aUpStretch = nAttr.create("upStretch", "ustr", MFnNumericData::kDouble, 1.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setStorable(true);
	nAttr.setKeyable(true);
	nAttr.setMin(0.001);
	addAttribute(aUpStretch);
	//downStretch
	aDownStretch = nAttr.create("downStretch", "dstr", MFnNumericData::kDouble, 1.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setStorable(true);
	nAttr.setKeyable(true);
	nAttr.setMin(0.001);
	addAttribute(aDownStretch);
	
	//globalScale
	aGlobalScale = nAttr.create("globalScale", "gs", MFnNumericData::kDouble, 1.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setStorable(true);
	nAttr.setKeyable(true);
	nAttr.setMin(0.001);
	addAttribute(aGlobalScale);
	//upScale
	aUpScale = nAttr.create("upScale", "us", MFnNumericData::kDouble, 1.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setStorable(false);
	nAttr.setKeyable(false);
	nAttr.setWritable(false);
	addAttribute(aUpScale);
	//downScale
	aDownScale = nAttr.create("downScale", "ds", MFnNumericData::kDouble, 1.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setStorable(false);
	nAttr.setWritable(false);
	nAttr.setKeyable(false);
	addAttribute(aDownScale);

	//upScale affection
	attributeAffects(aStartMatrix, aUpScale);
	attributeAffects(aEndMatrix, aUpScale);
	attributeAffects(aPoleVectorMatrix, aUpScale);
	attributeAffects(aStretch, aUpScale);
	attributeAffects(aUpStretch, aUpScale);
	attributeAffects(aSlide, aUpScale);
	attributeAffects(aGlobalScale, aUpScale);
	attributeAffects(aPoleVectorLock, aUpScale);
	attributeAffects(aUpInitLength, aUpScale);

	//downScale affection
	attributeAffects(aStartMatrix, aDownScale);
	attributeAffects(aEndMatrix, aDownScale);
	attributeAffects(aPoleVectorMatrix, aDownScale);
	attributeAffects(aStretch, aDownScale);
	attributeAffects(aDownStretch, aDownScale);
	attributeAffects(aSlide, aDownScale);
	attributeAffects(aGlobalScale, aDownScale);
	attributeAffects(aPoleVectorLock, aDownScale);
	attributeAffects(aDownInitLength, aDownScale);

	return MS::kSuccess;
}

