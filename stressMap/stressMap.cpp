#include "stressMap.h"


MTypeId	StressMap::id(0x00124511);
MObject StressMap::aIsDrawing;
MObject StressMap::aIsTransparent;

StressMap::StressMap()
{
}


StressMap::~StressMap()
{

}


void StressMap::postConstructor()
{
	//rename the locator shape post construction
	MObject oThis = thisMObject();
	MFnDependencyNode fnNode(oThis);
	fnNode.setName("stressMapLoc#");

}


void* StressMap::creator()
{
	return new StressMap;
}


MStatus StressMap::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus	status;

	return MS::kSuccess;
}

void StressMap::draw(M3dView& view,
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
	//glStart
	view.beginGL();
	//setup states
	glPushAttrib(GL_CURRENT_BIT);
	glDepthMask(GL_FALSE);
	//setup for draw colors for maya(active, lead etc)
	MColor solidColor;

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
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	glPopAttrib();
	view.endGL();
}


bool StressMap::isBounded() const
{
	return false;
}


bool StressMap::isTransparent() const
{
	MPlug plug(thisMObject(), aIsTransparent);
	bool value;
	plug.getValue(value);
	return value;

}

MStatus StressMap::initialize()
{
	//standard attribute creation for the locator node 
	MStatus status;
	return MS::kSuccess;
}

void StressMap::buildConnectTree(std::vector<StressPoint>&pointTree,
								MDoubleArray &stressmapValues,
								MObject referenceMesh)
{
}
void StressMap::stressLine(MPoint& p,
							double& stress,
							const double* squashColor,
							const double* stretchColor,
							const double& mult)
{
}