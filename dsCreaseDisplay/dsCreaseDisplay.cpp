#include "dsCreaseDisplay.h"

MTypeId CreaseDisplay::id(0x00124508);
MObject CreaseDisplay::aIsDrawing;
MObject CreaseDisplay::aColorRamp;
MObject CreaseDisplay::aTransparent;
MObject CreaseDisplay::aInMesh;
MObject CreaseDisplay::aDrawOptions;
MObject CreaseDisplay::aMinCreaseValue;
MObject CreaseDisplay::aMaxCreaseValue;


CreaseDisplay::CreaseDisplay()
{
}


CreaseDisplay::~CreaseDisplay()
{

}

void CreaseDisplay::postConstructor()
{
	//rename the locator shape post construction
	MObject oThis = thisMObject();
	MFnDependencyNode fnNode(oThis);
	fnNode.setName("creaseDisplay#");

}

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
	//clear the start and endpoints each compute so we don't double up 
	startPoints.clear();
	endPoints.clear();
	for (unsigned int edgeIter=0; edgeIter < creaseEdgesIdArray.length(); ++edgeIter)
	{	
		MPoint edgeStart, edgeEnd;
		int2 edgeVertexIndex;
		fnMesh.getEdgeVertices(creaseEdgesIdArray[edgeIter], edgeVertexIndex);
		fnMesh.getPoint(edgeVertexIndex[0], edgeStart);
		fnMesh.getPoint(edgeVertexIndex[1], edgeEnd);
		//append edge start and end
		startPoints.append(edgeStart);
		endPoints.append(edgeEnd);
	}
	

	return MS::kSuccess;

}


void CreaseDisplay::draw(M3dView& view,
						const MDagPath&,
						M3dView::DisplayStyle style,
						M3dView::DisplayStatus status)
{
	MObject currentObject = thisMObject();
	//draw plug function,we only want to draw if the plug is true
	MPlug pDrawit(currentObject, aIsDrawing);
	bool drawItV;

	pDrawit.getValue(drawItV);
	if (drawItV == false)
		return;

	//get the plug values for settings including rampcolor
	MPlug rPlug(currentObject, aColorRamp);
	
	//min creaseValue
	MPlug minCreasePlug(currentObject, aMinCreaseValue);
	double minCreaseVal;
	minCreasePlug.getValue(minCreaseVal);
	//max creaseValue
	MPlug maxCreasePlug(currentObject, aMaxCreaseValue);
	double maxCreaseVal;
	maxCreasePlug.getValue(maxCreaseVal);
	//transparent values
	MPlug aTranPlug(currentObject, aTransparent);
	double transparentV;
	aTranPlug.getValue(transparentV);


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
	}
	//apply color and transparencey
	//draw the edges and text
	for (unsigned int pointIter = 0; pointIter < startPoints.length(); ++pointIter)
	{
	// edgeDisplay stuff
		// color is dependent on color ramp , smoothed shading between min and max
		glBegin(GL_LINES);
		glColor4f(solidColor.r, solidColor.g, solidColor.b, transparentV);
		//create the edge based on the start and end points
		glVertex3d(startPoints[pointIter].x, startPoints[pointIter].y, startPoints[pointIter].z);
		glVertex3d(endPoints[pointIter].x, endPoints[pointIter].y, endPoints[pointIter].z);

		//need to get center of edge = startPoint + (endPoint-startPoint) *.5 , to display the crease value
		MPoint midPointEdge = startPoints[pointIter] + (endPoints[pointIter] - startPoints[pointIter])* 0.5;
		//values display here using glText,
		MString textStr;
		//convert to string
		textStr.set(creaseValues[pointIter]);
		//draw the text at the centreish of the edge
		view.drawText(textStr, midPointEdge);
	}
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
	MFnTypedAttribute tAttr;
	MRampAttribute rAttr;
	MFnEnumAttribute eAttr;

	//output attribute
	aInMesh = tAttr.create("inMesh", "im", MFnData::kMesh);
	tAttr.setStorable(true);
	tAttr.setWritable(true);

	aIsDrawing = nAttr.create("draw", "d", MFnNumericData::kBoolean, 1);
	nAttr.setWritable(true);
	nAttr.setStorable(true);
	nAttr.setKeyable(true);
	addAttribute(aIsDrawing);
	
	aTransparent = nAttr.create("transparent", "transp", MFnNumericData::kDouble, 1);
	nAttr.setMin(0.0);
	nAttr.setMax(1.0);
	nAttr.setWritable(true);
	nAttr.setStorable(true);
	nAttr.setKeyable(true);
	addAttribute(aTransparent);

	aColorRamp = MRampAttribute::createColorRamp("colorRamp", "colr");
	addAttribute(aColorRamp);

	aDrawOptions = eAttr.create("drawOptions", "do", 0);
	eAttr.addField("text&geo", 0);
	eAttr.addField("text", 1);
	addAttribute(aDrawOptions);

	aMinCreaseValue = nAttr.create("minCreaseValue","minVal", MFnNumericData::kDouble, 0.0);
	nAttr.setStorable(true);
	nAttr.setKeyable(true);
	nAttr.setWritable(true);
	addAttribute(aMinCreaseValue);

	aMaxCreaseValue = nAttr.create("maxCreaseValue", "maxVal", MFnNumericData::kDouble, 10.0);
	nAttr.setStorable(true);
	nAttr.setKeyable(true);
	nAttr.setWritable(true);
	addAttribute(aMaxCreaseValue);

	return MS::kSuccess;
}
