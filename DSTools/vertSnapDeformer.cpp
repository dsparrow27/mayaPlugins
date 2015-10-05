#include "vertSnapDeformer.h"

MTypeId	VertSnapDeformer::id(0x00124505);
MObject VertSnapDeformer::aSnapMesh;
MObject VertSnapDeformer::aMapping;


VertSnapDeformer::VertSnapDeformer()
{

}


VertSnapDeformer::~VertSnapDeformer()
{

}

void* VertSnapDeformer::creator()
{
	return new VertSnapDeformer();
}

MStatus	VertSnapDeformer::deform(MDataBlock& dataBlock,
								MItGeometry& itGeo,
								const MMatrix& localToWorldMatrix,
								unsigned int geomIndex)
{
	MStatus status;
	//get the envelope
	float env = dataBlock.inputValue(envelope).asFloat();

	//get snapMesh
	MObject oMesh = dataBlock.inputValue(aSnapMesh).asMesh();

	//get vertex mapping
	MObject oMapData = dataBlock.inputValue(aMapping).data();

	if (oMesh.isNull() || env == 0.0f || oMapData.isNull())
	{
		return MS::kSuccess;
	}

	MFnIntArrayData intData(oMapData, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	MIntArray vertexMapping = intData.array();

	//get vertices in world space
	MFnMesh fnMesh(oMesh, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	MPointArray	snapVertices;
	fnMesh.getPoints(snapVertices, MSpace::kWorld);
	unsigned int numSnapVerts = snapVertices.length();

	MMatrix worldToLocalMatrix = localToWorldMatrix.inverse();
	MPoint	pt;
	unsigned int snapVertexIndex;
	for (itGeo.reset(); !itGeo.isDone(); itGeo.next())
	{
		//get point position
		pt = itGeo.position();
		snapVertexIndex = vertexMapping[itGeo.index()];

		if (snapVertexIndex != -1)
		{
			pt += (((snapVertices[snapVertexIndex] * worldToLocalMatrix) - pt) * env);
		}
		itGeo.setPosition(pt);

	}
	return MS::kSuccess;
}

MStatus	VertSnapDeformer::initialize()
{	
	//main  function for specifying node attribute's
	MStatus status;
	MFnTypedAttribute	tAttr;
	
	aSnapMesh = tAttr.create("snapMesh", "snapMesh", MFnData::kMesh);
	addAttribute(aSnapMesh);
	attributeAffects(aSnapMesh, outputGeom);

	aMapping = tAttr.create("vertexMapping", "vertexMapping", MFnData::kIntArray);
	tAttr.setHidden(true);
	tAttr.setConnectable(false);
	addAttribute(aMapping);
	attributeAffects(aMapping, outputGeom);

	return MS::kSuccess;
}