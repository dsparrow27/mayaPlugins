#include "vertSnapDeformer.h"

#define BIG_DIST 99999


MTypeId	VertSnapDeformer::id(0x00124508);
MObject VertSnapDeformer::aReferenceMesh;
MObject VertSnapDeformer::aIdMapping;
MObject VertSnapDeformer::aDriverMesh;
MObject VertSnapDeformer::aRebind;


void* VertSnapDeformer::creator()
{
	return new VertSnapDeformer();
}
VertSnapDeformer::VertSnapDeformer()
{
	//constructor
	//determines if the node is first time it's being running(initialized)
	initialized = 0;
	//number of vertices
	elemCount = 0;
	//an array for id association
	bindArray = MIntArray();
}


MStatus	VertSnapDeformer::deform(MDataBlock& dataBlock,
								MItGeometry& itGeo,
								const MMatrix& localToWorldMatrix,
								unsigned int geomIndex)
{
	MStatus status;
	//get the envelope
	double env = dataBlock.inputValue(envelope).asFloat();
	//get vertex mapping
	MArrayDataHandle mMapData = dataBlock.inputArrayValue(aIdMapping);
	mMapData.jumpToArrayElement(0);
	//get driverMesh
	MObject oDriverMesh = dataBlock.inputValue(aDriverMesh).asMesh();
	bool rebindV = dataBlock.inputValue(aRebind).asBool();

	if (oDriverMesh.isNull() || env == 0.0f || initialized == 0)
	{
		return MS::kNotImplemented;
	}

	
	//get vertices in world space
	MPointArray	driverPnts;
	MFnMesh fnMesh(oDriverMesh, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	fnMesh.getPoints(driverPnts, MSpace::kWorld);
	
	// get input point
	MPointArray pos;
	itGeo.allPositions(pos, MSpace::kWorld);

	//if rebind then recalulate vert association
	if (rebindV == 1)
	{
		initData(oDriverMesh, pos, bindArray, mMapData);
	}
	//
	if (elemCount == 0)
	{
		elemCount = itGeo.exactCount();
	}

	
	return MS::kSuccess;
}

MStatus	VertSnapDeformer::initialize()
{	
	//main  function for specifying node attribute's
	MStatus status;
	MFnTypedAttribute	tAttr;
	MFnNumericAttribute nAttr;
	
	aRebind = nAttr.create("rebind", "reb", MFnNumericData::kBoolean, 0);
	nAttr.setKeyable(true);
	nAttr.setWritable(true);
	addAttribute(aRebind);

	aReferenceMesh = tAttr.create("ReferenceMesh", "ReferenceMesh", MFnData::kMesh);
	addAttribute(aReferenceMesh);

	aIdMapping = nAttr.create("vertexMapping", "vertexMapping", MFnNumericData::kInt);
	nAttr.setHidden(true);
	nAttr.setArray(true);
	nAttr.setStorable(true);
	nAttr.setConnectable(false);
	addAttribute(aIdMapping);
	
	aDriverMesh = tAttr.create("driverMesh", "drm", MFnData::kMesh);
	addAttribute(aDriverMesh);

	attributeAffects(aDriverMesh, outputGeom);
	attributeAffects(aIdMapping, outputGeom);

	MGlobal::executeCommand("makepaintable -attrType multiFloat -sm deformer snapDeformer weights");

	return MS::kSuccess;
}