#include "dsCreaseDisplay.h"

MTypeId CreaseDisplay::id(0x00124508);
MObject CreaseDisplay::aIsDrawing;
MObject CreaseDisplay::aColorRamp;
MObject CreaseDisplay::aTransparent;
MObject CreaseDisplay::aInMesh;
MObject CreaseDisplay::aColorRamp;

void* CreaseDisplay::creator()
{
	return new CreaseDisplay;
}


MStatus CreaseDisplay::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus	status;
	//get mesh
	MObject inMesh = dataBlock.inputValue(aInMesh).asMesh();
	MFnMesh fnMesh(inMesh, &status);
	//from the mesh get all the crease edges and values 
	MUintArray creaseEdgesArray;
	fnMesh.getCreaseEdges(creaseEdgesArray, creaseValues);
	
	for (unsigned int edgeIter =0; edgeIter < creaseEdgeIds.length; ++edgeIter)
	{
		//getedgeVertices(creaseEdgeUds[edgeIter], edgeVertexIndex)
		//Mpoint edgeStart, edgeEnd
		//inmesh.getPoint(edgeVertexIndex[0], edgeStart)
		//inmesh.getPoint(edgeVertexIndex[0], edgeEnd)
		//append edge start and end
	}
	return MS::kSuccess;

}


void CreaseDisplay::draw(M3dView& view,
						const MDagPath&,
						M3dView::DisplayStyle style,
						M3dView::DisplayStatus status)
{
	//draw plug function
	MPlug pDrawit(thisMObject(), aIsDrawing);
	bool drawItV;
	pDrawit.getValue(drawItV);

	if (drawItV == false)
		return;
	
	//some for loop here 
	//pointIter = 0; pointIter< startPoints.length(); ++ pointIter
	// edgeDisplay stuff
	// values display here using glText , need to get center of edge = startPoint + (endPoint-startPoint) *.5

}


bool CreaseDisplay::isBounded() const
{
	return false;
}


bool CreaseDisplay::isTransparent() const
{
	MPlug plug(thisMObject(), aTransparent);
	bool value;
	plug.getValue(value);
	return value;
}


MStatus CreaseDisplay::initialize()
{
	//standard attribute creation for the locator node 
	MStatus status;
	
	MFnNumericAttribute nAttr;
	//output attribute
	aIsDrawing = nAttr.create("draw", "d", MFnNumericData::kBoolean, 1);
	nAttr.setWritable(true);
	nAttr.setStorable(true);
	addAttribute(aIsDrawing);
	
	aTransparent = nAttr.create("transparent", "transp", MFnNumericData::kFloat, 1);
	nAttr.setMin(0.0);
	nAttr.setMax(1.0);
	nAttr.setWritable(true);
	nAttr.setStorable(true);
	addAttribute(aTransparent);

	aColorRamp = MRampAttribute::createColorRamp("colorRamp", "colr");
	addAttribute(aColorRamp);
	return MS::kSuccess;
}
