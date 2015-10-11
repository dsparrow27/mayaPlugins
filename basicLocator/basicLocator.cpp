#include "basicLocator.h"

MObject BasicLocator::aIsDrawing;
MTypeId BasicLocator::id(0x00124508);
MObject BasicLocator::aShapeType;
MObject BasicLocator::aShapeColor;
MObject BasicLocator::aIsTransparent;

BasicLocator::BasicLocator()
{
}


BasicLocator::~BasicLocator()
{

}


void BasicLocator::postConstructor()
{
	//rename the locator shape post construction
	MObject oThis = thisMObject();
	MFnDependencyNode fnNode(oThis);
	fnNode.setName("basicLocator#");

}


void* BasicLocator::creator()
{
	return new BasicLocator;
}


MStatus BasicLocator::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus	status;

	return MS::kSuccess;

}


void BasicLocator::draw(M3dView& view,
						const MDagPath&,
						M3dView::DisplayStyle style,
						M3dView::DisplayStatus status)
{
	MPlug pDrawit(thisMObject(), aIsDrawing);
	bool drawItV;
	pDrawit.getValue(drawItV);

	if (drawItV == false)
		return;

	MPlug pTransparent(thisMObject(), aIsTransparent);
	MPlug pShapeColor(thisMObject(), aShapeColor);
	MPlug pShapeType(thisMObject(), aShapeType);
	float r, g, b, a;
	MObject color;


	//glStart
	view.beginGL();
	//setup states
	glPushAttrib(GL_CURRENT_BIT);

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

	default:
	
		pShapeColor.getValue(color);
		MFnNumericData data(color);
		data.getData(r, g, b);
		pTransparent.getValue(a);
	
		if (a < 1.0f)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		solidColor = MColor(r, g, b, a);
		//draw the solidColor
		glColor4f(solidColor.r, solidColor.g, solidColor.b, solidColor.a);
	}
	int sType;
	
	pShapeType.getValue(sType);
	switch (sType)
	{
	case 0:
		drawArrow();
		break;
	case 1:
		drawDisc(1.0, 32, true);
		break;
	}
	
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	glPopAttrib();
	view.endGL();

}


bool BasicLocator::isBounded() const
{
	return true;
}


bool BasicLocator::isTransparent() const
{
	MPlug plug(thisMObject(), aIsTransparent);
	bool value;
	plug.getValue(value);
	return value;

}

MBoundingBox BasicLocator::boundingBox() const
{
	MBoundingBox bbox;
	MFloatPointArray points;
	points.clear();
	points.setSizeIncrement(4);
	points.append(-1.0, 0.0, 0.0);
	points.append(1.0, 0.0, 0.0);
	points.append(0.0, 0.0, 1.0);
	points.append(0.0, 0.0, -1.0);

	for (unsigned int i = 0; i < points.length(); i++)
		bbox.expand(points[i]);

	return bbox;
}


void BasicLocator::drawArrow()
{
	glBegin(GL_TRIANGLES);
		glVertex3d(-2, 1, 0);
		glVertex3d(-2, -1, 0);
		glVertex3d(2, 1, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
		glVertex3d(-2, -1, 0);
		glVertex3d(2, -1, 0);
		glVertex3d(2, 1, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
		glVertex3d(2, 1.5, 0);
		glVertex3d(2, -1.5, 0);
		glVertex3d(3, 0, 0);
	glEnd();


}

void BasicLocator::drawDisc(float radius, int divisions, bool filled)
{
	//setup
	int renderState = filled ? GL_POLYGON : GL_LINE_LOOP;
	float degreesPerDiv = 360.0f / divisions;
	float radiansPerDiv = degreesPerDiv * 0.0174532925f;
	MFloatPointArray points(divisions);
	//calculate disc shape 
	for (int i = 0; i < divisions; i++)
	{
		float angle = i * radiansPerDiv;
		float x = cos(angle) * radius;
		float z = sin(angle) * radius;
		points[i].x = x;
		points[i].z = z;
	}

	//draw the disc
	glBegin(renderState);
	for (int i = 0; i < divisions; i++)
	{
		//use x,z from previous math to draw each vertex
		glVertex3f(points[i].x, 0.0f, points[i].z);
	}
	glEnd();
}

MStatus BasicLocator::initialize()
{
	//standard attribute creation for the locator node 
	MStatus status;

	MFnNumericAttribute nAttr;
	MFnEnumAttribute eAttr;
	//output attribute
	aIsDrawing = nAttr.create("draw", "d", MFnNumericData::kBoolean, 1);
	nAttr.setWritable(true);
	nAttr.setStorable(true);
	addAttribute(aIsDrawing);
	
	aIsTransparent = nAttr.create("transparent", "tpart", MFnNumericData::kFloat, 0.5);
	nAttr.setMin(0.0);
	nAttr.setMax(1.0);
	nAttr.setWritable(true);
	nAttr.setStorable(true);
	addAttribute(aIsTransparent);

	aShapeColor = nAttr.createColor("color", "col");
	nAttr.setDefault(0.1, 0.1, 0.8);
	nAttr.setStorable(true);
	nAttr.setWritable(true);
	addAttribute(aShapeColor);

	aShapeType = eAttr.create("shapeType", "styp");
	eAttr.setStorable(true);
	eAttr.setKeyable(true);
	eAttr.addField("arrow", 0);
	eAttr.addField("disc", 1);
	eAttr.setDefault(0);
	addAttribute(aShapeType);

	return MS::kSuccess;
}