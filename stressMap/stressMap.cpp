#include "stressMap.h"


MTypeId	StressMap::id(0x00124511);
MObject StressMap::aIsDrawing;
MObject StressMap::aIsTransparent;
MObject StressMap::aFakeOut;
MObject StressMap::aInputMesh;
MObject StressMap::aReferenceMesh;
MObject StressMap::aOutput;
MObject StressMap::aMultiplier;
MObject StressMap::aClampMax;
MObject StressMap::aNormalize;
MObject StressMap::aSquashColor;
MObject StressMap::aStretchColor;
MObject StressMap::aIntensity;


StressMap::StressMap()
{
	//constructor
	//if 0 then cache our data from the reference mesh else leave
	firstRun = 0;
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
	MStatus status;
	//standard attribute creation for the locator node 
	MFnEnumAttribute eAttr;
	MFnMatrixAttribute mAttr;
	MFnNumericAttribute nAttr;
	MFnCompoundAttribute cAttr;
	MFnTypedAttribute tAttr;

	//inputMesh
	aInputMesh = tAttr.create("inputMesh", "inputM", MFnData::kMesh);
	addAttribute(aInputMesh);
	//referenceMesh
	aReferenceMesh = tAttr.create("referenceMesh", "refM", MFnData::kMesh);
	tAttr.setStorable(true);
	addAttribute(aReferenceMesh);

	//drawing
	aIsDrawing = nAttr.create("draw", "draw", MFnNumericData::kBoolean, 1);
	nAttr.setKeyable(true);
	nAttr.setStorable(true);
	addAttribute(aIsDrawing);
	//transparent
	aIsTransparent = nAttr.create("transparent", "trp", MFnNumericData::kBoolean, 1);
	nAttr.setKeyable(true);
	nAttr.setStorable(true);
	addAttribute(aIsTransparent);

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