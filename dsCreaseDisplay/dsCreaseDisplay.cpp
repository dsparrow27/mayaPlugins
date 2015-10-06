#include "dsCreaseDisplay.h"

MTypeId CreaseDisplay::id(0x00124508);
MObject CreaseDisplay::aIsDrawing;
MObject CreaseDisplay::aColorRamp;
MObject CreaseDisplay::aTransparent;
MObject CreaseDisplay::aInMesh;
MObject CreaseDisplay::aColorRamp;
MObject CreaseDisplay::aMinCreaseValue;
MObject CreaseDisplay::aMaxCreaseValue;


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
	fnMesh.getCreaseEdges(creaseEdgesIdArray, creaseValues);
	MPoint edgeStart, edgeEnd;
	/*
	for (unsigned int edgeIter=0; edgeIter < creaseEdgesIdArray.length; ++edgeIter)
	{	
		fnMesh.getEdgeVertices(creaseEdgesIdArray[edgeIter], edgeVertexIndex);
		fnMesh.getPoint(edgeVertexIndex[0], edgeStart);
		fnMesh.getPoint(edgeVertexIndex[0], edgeEnd);
		//append edge start and end
	}
	*/

	return MS::kSuccess;

}


void CreaseDisplay::draw(M3dView& view,
						const MDagPath&,
						M3dView::DisplayStyle style,
						M3dView::DisplayStatus status)
{
	MObject currentObject = thisMObject();
	//draw plug function
	MPlug pDrawit(currentObject, aIsDrawing);
	bool drawItV;
	pDrawit.getValue(drawItV);

	if (drawItV == false)
		return;
	//get the plug values for settings including rampcolor

	//glStart
	view.beginGL();
	//setup states
	glPushAttrib(GL_CURRENT_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);

	//setup for draw colors for maya(active, lead etc)
	MColor solidColor, wireColor;

	switch (status)
	{
	case M3dView::kActive:
		//white
		solidColor = MColor(1.0f, 1.0f, 1.0f, 0.1f);
		break;
	case M3dView::kLead:
		//green
		solidColor = MColor(0.26f, 1.0f, 0.64f, 0.1f);
		break;

	case M3dView::kActiveAffected:
		// maya magenta
		solidColor = MColor(0.78f, 1.0f, 0.78f);
		break;

	case M3dView::kTemplate:
		// maya template gray
		solidColor = MColor(0.47f, 0.47f, 0.47f);
		break;

	case M3dView::kActiveTemplate:
		// maya selected template pink
		solidColor = MColor(1.0f, 0.47f, 0.47f);
		break;
	/*
	apply color and transparencey

	//draw the edges and text
	for (unsigned int pointIter = 0; pointIter < startPoints.length(); ++pointIter)
	{
	// edgeDisplay stuff
		// color is dependent on color ramp , smoothed shading between min and max
		glBegin(GL_LINES);
		glColor4f(solidColor.r, solidColor.g, solidColor.b, solidColor.a);
		glVertex3d(startPoints[pointIter]);
		glVertex3d(endPoints[pointIter]);
		MPoint midPointEdge = startPoints[pointIter] + (endPoints[pointIter] - startPoints[pointIter] * 0.5)
		
		view.drawText(creaseValues[pointIter])

	// values display here using glText , need to get center of edge = startPoint + (endPoint-startPoint) *.5
		
	}
	*/
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	glPopAttrib();
	view.endGL();
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
