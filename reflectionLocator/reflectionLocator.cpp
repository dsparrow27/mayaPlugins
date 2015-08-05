#include "reflectionLocator.h"
#include "math.h"
MObject ReflectionLocator::aPlaneMatrix;
MObject ReflectionLocator::aPoint;
MObject ReflectionLocator::aReflectedPoint;
MObject ReflectionLocator::aReflectionMatrix;
MObject ReflectionLocator::aScale;

ReflectionLocator::ReflectionLocator()
{
}

ReflectionLocator::~ReflectionLocator()
{
}

void* ReflectionLocator::creator()
{
	return new ReflectionLocator;
}


MStatus ReflectionLocator::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus	status;
	// make sure current compute plug is valid 
	if (plug != aReflectedPoint && plug.parent() != aReflectedPoint)
	{
		return MS::kSuccess;
	}

	//get attributes
	MMatrix planeMatrix = dataBlock.inputValue(aPlaneMatrix).asMatrix;
	MMatrix reflectedParentInverse= dataBlock.inputValue(aReflectionMatrix).asMatrix;
	MMatrix inputMatrix = dataBlock.inputValue(aPoint).asMatrix();
	//extract the translation from the matrices 
	MVector planePos = MTransformationMatrix(planeMatrix).getTranslation(MSpace::kPostTransform);
MVector inputPoint = MTransformationMatrix(inputMatrix).getTranslation(MSpace::kPostTransform);
double scale = dataBlock.inputValue(aScale).asDouble;

/////////Reflection math///////
//formula = R = 2 * (V dot N) * N - V
//N vector
MVector normal(0.0, 1.0, 0.0);
normal *= planeMatrix;
normal.normalize();

//vector to reflect
MVector V = inputPoint - planePos;

//Reflected vector
MVector r = 2 * ((normal * V) * normal) - V;
r.normalize();
r *= scale;

//reflected point position
mDestPoint = planePos + r;

//place into localSpace
mDestPoint *= reflectedParentInverse;

//setOutput
MDataHandle hOutput = dataBlock.outputValue(aReflectedPoint);
hOutput.set3Float((float)mDestPoint.x, (float)mDestPoint.y, (float)mDestPoint.z);
hOutput.setClean();
dataBlock.setClean(plug);

//setup points for openGl(being in objectSpace)
MMatrix planeMatrixInverse = planeMatrix.inverse();
mSrcPoint = MPoint(inputPoint) * planeMatrixInverse;
mPlanePoint = MPoint(planePos) * planeMatrixInverse;
mDestPoint *= planeMatrixInverse;

return MS::kSuccess;

}


void ReflectionLocator::draw(M3dView& view,
	const MDagPath&,
	M3dView::DisplayStyle style,
	M3dView::DisplayStatus status)
{
	//glStart
	view.beginGL();
	//setup states
	glPushAttrib(GL_CURRENT_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);

	//setup for draw colors for maya(active, lead etc)
	MColor solidColor, wireColor;
	if (status == M3dView::kActive)
	{
		//white
		solidColor = MColor(1.0f, 1.0f, 1.0f, 0.1f);
		wireColor = MColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else if (status == M3dView::kLead)
	{
		//green
		solidColor = MColor(0.26f, 1.0f, 0.64f, 0.1f);
		wireColor = MColor(0.26f, 1.0f, 0.64f, 1.0f);
	}
	else
	{
		//blue
		solidColor = MColor(0.26f, 1.0f, 0.0f, 0.1f);
		wireColor = MColor(0.26f, 1.0f, 0.0f, 1.0f);
	}

	//draw the disc 
	glColor4f(solidColor.r, solidColor.g, solidColor.b, solidColor.a);
	drawDisc(1.0f, 32, true);

	//wireFrames
	glColor4f(wireColor.r, wireColor.g, wireColor.b, wireColor.a);
	drawReflection(mSrcPoint, mDestPoint);
	drawDisc(1.0f, 32, false);

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	glPopAttrib();
	view.endGL();

}

void ReflectionLocator::drawDisc(float radius, int divisions, bool filled)
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
		float x = cos(angle) * angle;
		float y = sin(angle) * angle;
		points[i].x = x;
		points[i].y = y;
	}

	//draw the disc
	glBegin(renderState);
	for (int i = 0; i < divisions; i++)
	{
		//use x,z from previous math to draw each vertex
		glVertex3f(points[i].x, 0.0f, points[i].y);
	}
	glEnd();
}

void ReflectionLocator::drawReflection(const MPoint& src, const MPoint& dest)
{

}