#include "pushDeformer.h"

MObject PushDeformer::aAmount;




MStatus PushDeformer::deform(MDataBlock& dataBlock,
								MItGeometry& itGeo,
								const MMatrix& localToWorldMatrix,
								unsigned int geomIndex)
{
	MStatus status;
	//get attribute handles
	float bulgeAmount = dataBlock.inputValue(aAmount, &status).asFloat();
	CHECK_MSTATUS_AND_RETURN_IT(status);
	float env = dataBlock.inputValue(envelope, &status).asFloat();
	CHECK_MSTATUS_AND_RETURN_IT(status);
	if (utils::almostEqual(env, 0.0f, 2))
	{
		return MS::kSuccess;
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
	fnMesh.getVertexNormals(false, normals, MSpace::kWorld);
	itGeo.allPositions(points, MSpace::kWorld);
	
	//weights
	float w;

	for (; !itGeo.isDone(); itGeo.next())
	{
		w = weightValue(dataBlock, geomIndex, itGeo.index());
		//deform
		points[itGeo.index()] += normals[itGeo.index()] * bulgeAmount * env * w;
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

	attributeAffects(aAmount, outputGeom);
	// make paintable deformer
	MGlobal::executeCommand("makePaintable -attrType multiFloat -sm deformer pushDeformer weights");

	return MS::kSuccess;
}