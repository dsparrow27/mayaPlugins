#include "rippleDeformer.h"
#include "math.h"

MTypeId RippleDeformer::id(0x00000424);
MObject RippleDeformer::aAmplitude;
MObject RippleDeformer::aDisplace;


RippleDeformer::RippleDeformer()
{

}

RippleDeformer::~RippleDeformer()
{

}

void* RippleDeformer::creator()
{
	return new RippleDeformer();
}


MStatus RippleDeformer::deform(MDataBlock& dataBlock,
								MItGeometry& itGeo,
								const MMatrix& localToWorldMatrix,
								unsigned int geomIndex)
{
	MStatus status;
	
	//get attriubtes as a datahandle
	float env = dataBlock.inputValue(envelope).asFloat();
	float amplitude = dataBlock.inputValue(aAmplitude).asFloat();
	float displace = dataBlock.inputValue(aDisplace).asFloat();
	//get the mesh 
	//retrieve the handle to the input attribute
	MArrayDataHandle hInput = dataBlock.outputArrayValue(input, &status);
	//get the input array index handle
	status = hInput.jumpToElement(geomIndex);
	//get the handle of geomIndex attribute
	MDataHandle hInputElement = hInput.outputValue(&status);
	//Get the MObject of the input geometry of geomindex
	MObject oInputGeom = hInputElement.child(inputGeom).asMesh();

	MFnMesh fnMesh(oInputGeom, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	MFloatVectorArray normals;
	fnMesh.getVertexNormals(false, normals);


	MPoint pointPos;
	float weight;
	for (; !itGeo.isDone(); itGeo.next())
	{
		//get current point position
		pointPos = itGeo.position();
		weight = weightValue(dataBlock, geomIndex, itGeo.index());
		pointPos.x = pointPos.x + sin(itGeo.index() + displace) * amplitude * normals[itGeo.index()].x * weight * env;
		pointPos.y = pointPos.y + sin(itGeo.index() + displace) * amplitude * normals[itGeo.index()].y * weight * env;
		pointPos.z = pointPos.z + sin(itGeo.index() + displace) * amplitude * normals[itGeo.index()].z * weight * env;
		//setPosition
		itGeo.setPosition(pointPos);
	}	
	
	return MS::kSuccess;
}


MStatus RippleDeformer::initalize()
{
	MStatus status;
	
	MFnNumericAttribute nAttr;
	
	aAmplitude = nAttr.create("amplitude","amp", MFnNumericData::kFloat, 0.0);
	nAttr.setKeyable(true);
	addAttribute(aAmplitude);
	attributeAffects(aAmplitude, outputGeom);

	aDisplace = nAttr.create("displace", "displace", MFnNumericData::kFloat, 0.0);
	nAttr.setKeyable(true);
	addAttribute(aDisplace);
	attributeAffects(aDisplace, outputGeom);

	MGlobal::executeCommand("makePaintable -attrType multiFloat -sm deformer rippleDeformer");
	
	return MS::kSuccess;
}

