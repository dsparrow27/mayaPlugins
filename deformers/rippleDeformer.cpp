#include "rippleDeformer.h"


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
	
	MDataHandle hinMesh = dataBlock.inputValue(inMesh);
	//get vertex normals so we can deform along them 
	MVector mNormalVectorArray;
	hinMesh.getVertexNormals(false, mNormalVectorArray, MSpace.kObject);

	MPoint pointPos;
	float weight;

	for (; !itGeo.isDone(); itGeo.next())
	{
		//get current point position
		pointPos = itGeo.position();
		weight = weightValue(dataBlock, geomIndex, itGeo.index());
		pointPos.x = pointPos.x + sin(itGeo.index() + displace) * amplitude * mNormalVectorArray[itGeo.index()].x * weight * envelope;
		pointPos.y = pointPos.y + sin(itGeo.index() + displace) * amplitude * mNormalVectorArray[itGeo.index()].y * weight * envelope;
		pointPos.z = pointPos.z + sin(itGeo.index() + displace) * amplitude * mNormalVectorArray[itGeo.index()].z * weight * envelope;
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

