#include "bulgeDeformer.h"
#include <IOSTREAM>
MTypeId	BulgeDeformer::id(0x00124502);
MObject BulgeDeformer::aBulgeAmount;


BulgeDeformer::BulgeDeformer()
{

}

BulgeDeformer::~BulgeDeformer()
{

}

void* BulgeDeformer::creator()
{
	return new BulgeDeformer();
}

MStatus BulgeDeformer::deform(MDataBlock& dataBlock,
								MItGeometry& itGeo,
								const MMatrix& localToWorldMatrix,
								unsigned int geomIndex)
{
	MStatus status;
	//get attribute handles
	float bulgeAmount = dataBlock.inputValue(aBulgeAmount).asFloat();
	float env = dataBlock.inputValue(envelope).asFloat();
	//retrieve the handle to the input attribute
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
	fnMesh.getNormals(normals, MSpace::kWorld);
	
	MPointArray points;
	itGeo.allPositions(points, MSpace::kWorld);
	
	//weights
	float w;

	for (int i=0; i<itGeo.exactCount(); i++)
	{
		w = weightValue(dataBlock, geomIndex, itGeo.index());
		//deform
		points[i] += (MVector(normals[i]) * bulgeAmount * w * env);
		
	}
	itGeo.setAllPositions(points);
	return MS::kSuccess;

}


MStatus BulgeDeformer::initialize()
{
	MStatus status;

	MFnNumericAttribute nAttr;

	//add bulge attribute which affects the output geom
	aBulgeAmount = nAttr.create("bulgeAmount", "bulgeAmount", MFnNumericData::kFloat, 0.0);
	nAttr.setKeyable(true);
	addAttribute(aBulgeAmount);
	attributeAffects(aBulgeAmount, outputGeom);

	// make paintable deformer
	MGlobal::executeCommand("makePaintable -attrType multiFloat -sm deformer bulgeDeformer weights");

	return MS::kSuccess;
}