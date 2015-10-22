#include "pushDeformer.h"
MTypeId	PushDeformer::id(0x00124502);
MObject PushDeformer::aAmount;
MObject PushDeformer::aStressMap;
MObject PushDeformer::aUseStress;

PushDeformer::PushDeformer()
{

}
void* PushDeformer::creator()
{
	return new PushDeformer();
}

MStatus PushDeformer::deform(MDataBlock& dataBlock,
								MItGeometry& itGeo,
								const MMatrix& localToWorldMatrix,
								unsigned int geomIndex)
{
	MStatus status;
	//get attribute handles
	double bulgeAmount = dataBlock.inputValue(aAmount, &status).asDouble();
	CHECK_MSTATUS_AND_RETURN_IT(status);
	double env = dataBlock.inputValue(envelope, &status).asDouble();
	CHECK_MSTATUS_AND_RETURN_IT(status);
	bool useStressV = dataBlock.inputValue(aUseStress, &status).asBool();
	CHECK_MSTATUS_AND_RETURN_IT(status);
	if (env == 0.0)
	{
		return MS::kSuccess;
	}
	// if the use stress plug is turned on pull 
	MDoubleArray stressV;
	if (useStressV == true)
	{
		//pull out the raw data as an Mobject
		MObject stressMap = dataBlock.inputValue(aStressMap, &status).data();
		CHECK_MSTATUS_AND_RETURN_IT(status);
		MFnDoubleArrayData stressDataFn(stressMap);
		stressV = stressDataFn.array();

	}

	//retrieve the handle to the output array attribute
	MArrayDataHandle hInput = dataBlock.outputArrayValue(input, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	//get the input array index handle
	status = hInput.jumpToElement(geomIndex);
	//get the handle of geomIndex attribute
	MDataHandle hInputElement = hInput.outputValue(&status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	//Get the MObject of the input geometry of geomindex
	MObject oInputGeom = hInputElement.child(inputGeom).asMesh();
	MFnMesh fnMesh(oInputGeom, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	MFloatVectorArray normals;
	MPointArray points;
	fnMesh.getNormals(normals, MSpace::kWorld);
	itGeo.allPositions(points, MSpace::kWorld);
	
	//weights
	double w;

	for (; !itGeo.isDone(); itGeo.next())
	{
		w = weightValue(dataBlock, geomIndex, itGeo.index());
		if (useStressV == true)
		{
			//deform
			points[itGeo.index()] += (MVector(normals[itGeo.index()]) * bulgeAmount * env * stressV[itGeo.index()]);
			points[itGeo.index()] += (MVector(normals[itGeo.index()]) * bulgeAmount);
		}
		else
		{
			//deform
			points[itGeo.index()] += (MVector(normals[itGeo.index()]) * bulgeAmount * env * w);
			points[itGeo.index()] += (MVector(normals[itGeo.index()]) * bulgeAmount);

		}
	}
	itGeo.setAllPositions(points);
	return MS::kSuccess;

}


MStatus PushDeformer::initialize()
{
	MStatus status;

	MFnNumericAttribute nAttr;
	MFnTypedAttribute tAttr;
	//add bulge attribute which affects the output geom
	aAmount = nAttr.create("amount", "amt", MFnNumericData::kDouble, 0.0);
	nAttr.setKeyable(true);
	addAttribute(aAmount);

	aStressMap = tAttr.create("aStressMap", "stMap", MFnData::kDoubleArray);
	tAttr.setKeyable(true);
	tAttr.setWritable(true);
	tAttr.setStorable(true);
	addAttribute(aStressMap);

	aUseStress = nAttr.create("useStress", "useStress", MFnNumericData::kBoolean, 0);
	nAttr.setKeyable(true);
	nAttr.setStorable(true);
	addAttribute(aUseStress);

	attributeAffects(aAmount, outputGeom);
	attributeAffects(aStressMap, outputGeom);
	attributeAffects(aUseStress, outputGeom);
	// make paintable deformer
	MGlobal::executeCommand("makePaintable -attrType multiFloat -sm deformer pushDeformer weights");

	return MS::kSuccess;
}