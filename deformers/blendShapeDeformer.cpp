#include "blendShapeDeformer.h"


MTypeId	BlendShapeDeformer::id(0x00000123);
MObject BlendShapeDeformer::aBlendMesh;
MObject BlendShapeDeformer::aBlendWeight;


BlendShapeDeformer::BlendShapeDeformer()
{

}

BlendShapeDeformer::~BlendShapeDeformer()
{

}

void* BlendShapeDeformer::creator()
{
	return new BlendShapeDeformer();
}

MStatus BlendShapeDeformer::deform(MDataBlock& dataBlock,
								MItGeometry& itGeo,
								const MMatrix& localToWorldMatrix,
								unsigned int geomIndex)
{
	MStatus status;
	//get the envelope attribute as a dataHandle
	float env = dataBlock.inputValue(envelope).asFloat();
	float blendWeight = dataBlock.inputValue(aBlendWeight).asFloat();
	//get the blendMesh attribute as a dataHandle 
	MDataHandle hBlendMesh = dataBlock.inputValue(aBlendMesh, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	//get the Mobject from the mesh
	MObject oBlendMesh = hBlendMesh.asMesh();
	//check if oBlendMesh is valid 
	if (oBlendMesh.isNull())
	{
		return MS::kSuccess;
	}
	//
	MFnMesh fnMesh(oBlendMesh, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	//retrieve ppints from the mesh
	MPointArray blendPoints;
	fnMesh.getPoints(blendPoints);

	MPoint point;
	float w;

	for (; !itGeo.isDone(); itGeo.next())
	{
		//get vertex position
		point = itGeo.position();
		//get the painted weight value
		w = weightValue(dataBlock, geomIndex, itGeo.index());
		//perform the deformation
		point += (blendPoints[itGeo.index()] - point) * blendWeight * env * w;
		//set the new output point
		itGeo.setPosition(point);

	}
		

	return MS::kSuccess;

}


MStatus BlendShapeDeformer::initialize()
{
	MStatus status;

	//
	MFnNumericAttribute nAttr;
	MFnTypedAttribute tAttr;

	
	aBlendMesh = tAttr.create("BlendMesh", "blendMesh", MFnData::kMesh);
	addAttribute(aBlendMesh);
	attributeAffects(aBlendMesh, outputGeom);

	aBlendWeight = nAttr.create("blendValue", "blendValue", MFnNumericData::kFloat);
	nAttr.setKeyable(true);
	addAttribute(aBlendWeight);
	attributeAffects(aBlendWeight, outputGeom);

	// make the deformer weights paintable 
	MGlobal::executeCommand("makePaintable -attrType multiFloat -sm deformer blendShapeDeformer weights;");
	return MS::kSuccess;

}