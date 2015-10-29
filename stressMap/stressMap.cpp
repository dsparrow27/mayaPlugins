#include "stressMap.h"


MTypeId	StressMap::id(0x00124511);

MObject StressMap::aFakeOut;
MObject StressMap::aInputMesh;
MObject StressMap::aReferenceMesh;
MObject StressMap::aOutput;

MObject StressMap::aMultiplier;
MObject StressMap::aClampMax;
MObject StressMap::aNormalize;

MObject StressMap::aIsDrawing;
MObject StressMap::aIsTransparent;
MObject StressMap::aSquashColor;
MObject StressMap::aStretchColor;
MObject StressMap::aIntensity;
MObject StressMap::aLineWidth;

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
	fnNode.setName("stressMapLocShape#");

}


void* StressMap::creator()
{
	return new StressMap;
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
	tAttr.setKeyable(true);
	addAttribute(aInputMesh);
	//referenceMesh
	aReferenceMesh = tAttr.create("referenceMesh", "refM", MFnData::kMesh);
	tAttr.setStorable(true);
	tAttr.setKeyable(true);
	addAttribute(aReferenceMesh);

	//drawing
	aIsDrawing = nAttr.create("draw", "draw", MFnNumericData::kBoolean, 1);
	nAttr.setKeyable(true);
	nAttr.setStorable(true);
	addAttribute(aIsDrawing);
	//transparent
	aIsTransparent = nAttr.create("transparent", "trp", MFnNumericData::kDouble, 1);
	nAttr.setKeyable(true);
	nAttr.setStorable(true);
	addAttribute(aIsTransparent);
	//fake output
	aFakeOut = nAttr.create("fakeOut", "fake", MFnNumericData::kBoolean, 1);
	nAttr.setKeyable(false);
	nAttr.setStorable(false);
	addAttribute(aFakeOut);
	//output
	aOutput = tAttr.create("output", "out", MFnData::kDoubleArray);
	tAttr.setKeyable(false);
	tAttr.setWritable(false);
	tAttr.setStorable(false);
	addAttribute(aOutput);
	//multiplier
	aMultiplier = nAttr.create("multiplier", "mult", MFnNumericData::kDouble, 1.0);
	nAttr.setKeyable(true);
	nAttr.setStorable(true);
	addAttribute(aMultiplier);
	//clampMax
	aClampMax = nAttr.create("clampMax", "clmax", MFnNumericData::kDouble, 1.0);
	nAttr.setKeyable(true);
	nAttr.setStorable(true);
	nAttr.setMin(0.0);
	nAttr.setMax(1.0);
	addAttribute(aClampMax);
	//normalize
	aNormalize = nAttr.create("normalize", "num", MFnNumericData::kBoolean, 0);
	nAttr.setKeyable(true);
	nAttr.setStorable(true);
	addAttribute(aNormalize);
	//squashColor
	aSquashColor = nAttr.createColor("squashColor", "sqCol");
	nAttr.setDefault(0.0f, 1.0f, 0.0f);
	nAttr.setKeyable(true);
	nAttr.setStorable(true);
	nAttr.setReadable(true);
	nAttr.setWritable(true);
	addAttribute(aSquashColor);
	//stretch color
	aStretchColor = nAttr.createColor("stretchColor", "stCol");
	nAttr.setDefault(1.0f, 0.0f, 0.0f);
	nAttr.setKeyable(true);
	nAttr.setStorable(true);
	nAttr.setReadable(true);
	nAttr.setWritable(true);
	addAttribute(aStretchColor);
	//intensity
	aIntensity = nAttr.create("colorIntensity", "colInt", MFnNumericData::kDouble, 1.0);
	nAttr.setKeyable(true);
	nAttr.setStorable(true);
	addAttribute(aIntensity);

	aLineWidth = nAttr.create("colorLineWidth", "colInt", MFnNumericData::kDouble, 2.0);
	nAttr.setKeyable(true);
	nAttr.setStorable(true);
	nAttr.setMin(0.001);
	addAttribute(aLineWidth);


	attributeAffects(aInputMesh, aOutput);
	attributeAffects(aReferenceMesh, aOutput);
	attributeAffects(aClampMax, aOutput);
	attributeAffects(aMultiplier, aOutput);
	attributeAffects(aSquashColor, aOutput);
	attributeAffects(aStretchColor, aOutput);
	attributeAffects(aIntensity, aOutput);
	attributeAffects(aNormalize, aOutput);

	attributeAffects(aInputMesh, aFakeOut);
	attributeAffects(aReferenceMesh, aFakeOut);
	attributeAffects(aClampMax, aFakeOut);
	attributeAffects(aMultiplier, aFakeOut);
	attributeAffects(aSquashColor, aFakeOut);
	attributeAffects(aStretchColor, aFakeOut);
	attributeAffects(aIntensity, aFakeOut);
	attributeAffects(aNormalize, aFakeOut);

	//AE TEMPLATENODE
	MString stressTemplateNode(MString() + "global proc AEstressMapTemplate(string $nodeName)\n" +
		"{editorTemplate -beginScrollLayout;\n" +

		"editorTemplate -beginLayout \"Setting Atttributes\" -collapse 0;\n" +
			"editorTemplate -addControl \"normalize\";\n" +
			"editorTemplate -addControl \"clampMax\";\n" +
			"editorTemplate -addControl \"multiplier\";\n" +
		"editorTemplate -endLayout;\n" +

		"editorTemplate -beginLayout \"Drawing Atttributes\" -collapse 0;\n" +
			"editorTemplate -addControl \"draw\";\n" +
			"editorTemplate -addControl \"colorIntensity\";\n" +
			"editorTemplate -addControl \"squashColor\";\n" +
			"editorTemplate -addControl \"stretchColor\";\n" +
			"editorTemplate -addControl \"colorLineWidth\";\n" + 
		"editorTemplate -endLayout;\n" +

		"editorTemplate -addExtraControls;\n" +
		"editorTemplate -endScrollLayout;\n}");

	MGlobal::executeCommand(stressTemplateNode);

	return MS::kSuccess;
}

bool StressMap::isBounded() const
{
	return false;
}


bool StressMap::isTransparent() const
{
	//determine if locator is transparent
	MPlug plug(thisMObject(), aIsTransparent);
	bool value;
	plug.getValue(value);
	return value;

}

MStatus StressMap::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus	status;
	//check and return if kMesh plug are not connected 
	MPlug inputMeshP(thisMObject(), aInputMesh);
	if (inputMeshP.isConnected() == false)
	{
		return MS::kNotImplemented;
	}

	MPlug referenceMeshP(thisMObject(), aReferenceMesh);
	if (referenceMeshP.isConnected() == false)
	{
		return MS::kNotImplemented;
	}
	MObject referenceMeshV = dataBlock.inputValue(aReferenceMesh).asMesh();
	MObject inputMeshV = dataBlock.inputValue(aInputMesh).asMesh();
	double multiplierV = dataBlock.inputValue(aMultiplier).asDouble();
	double clampMaxV = dataBlock.inputValue(aClampMax).asDouble();
	bool normalizeV = dataBlock.inputValue(aNormalize).asBool();

	//build tree if needed
	if ((firstRun == 0) || (pointStoredTree.empty() == 1) || (stressMapValues.length() == 0))
	{
		buildConnectTree(pointStoredTree, stressMapValues, referenceMeshV);
	}

	//get the input mesh points and store in public variable(in header)
	MFnMesh inMeshFn(inputMeshV);
	inMeshFn.getPoints(inputPos, MSpace::kObject);

	//get the reference mesh points
	MFnMesh refMeshFn(referenceMeshV);
	refMeshFn.getPoints(referencePos, MSpace::kObject);

	int intLength = inputPos.length();
	//check input point size
	if (intLength != referencePos.length())
	{
		MGlobal::displayError("Mismatching point number between input mesh and reference mesh!");
		return MS::kSuccess;
	}

	//check if size of the stored point is the same of the inpoints
	if (pointStoredTree.size() != intLength)
	{
		MGlobal::displayError("Mismatching in the reference and main data try to rebuild!");
		return MS::kSuccess;
	}

	double value = 0;
	MVector storedLen, currentLen;
	int connIndex;
	//loop every vertex to calculate the stress data
	for (int v = 0; v < intLength; v++)
	{
		value = 0;
		//loop connect vtx of the current vertex
		for (int n = 0; n < pointStoredTree[v].size; n++)
		{
			//alias for the neighbours for better readability
			connIndex = pointStoredTree[v].neighbours[n];
			//get the vectors length
			storedLen = MVector(referencePos[connIndex] - referencePos[v]);
			currentLen = MVector(inputPos[connIndex] - inputPos[v]);
			//accumulate
			value += (currentLen.length() / storedLen.length());

		}
		//average the full value by the number of edges
		value = value / double(pointStoredTree[v].size);
		//remap to -1 to 1 range
		value -= 1;
		// multiply the value by the multiplier
		value *= multiplierV;
		//clamp the value 
		if (normalizeV == 1 && value > clampMaxV)
		{
			value = clampMaxV;
		}
		stressMapValues[v] = value;
	}

	//set the output data 
	MFnDoubleArrayData outDatafn;
	MObject outData = outDatafn.create(stressMapValues);
	dataBlock.outputValue(aOutput).setMObject(outData);
	dataBlock.outputValue(aOutput).setClean();

	dataBlock.outputValue(aFakeOut).set(0);
	dataBlock.outputValue(aFakeOut).setClean();

	return MS::kSuccess;
}

void StressMap::draw(M3dView& view,
					const MDagPath&,
					M3dView::DisplayStyle style,
					M3dView::DisplayStatus status)
{
	MPlug drawitP(thisMObject(), aIsDrawing);
	bool drawItV;
	drawitP.getValue(drawItV);

	if (drawItV == 0)
	{
		return;
	}

	//force the node to evaluate
	MPlug fakeP(thisMObject(), aFakeOut);
	bool fakeV;
	fakeP.getValue(fakeV);
	//output value
	MPlug outP(thisMObject(), aOutput);
	MObject outV;
	outP.getValue(outV);

	//get the input mesh
	MPlug inputMeshP(thisMObject(), aInputMesh);
	MObject inputMeshV;
	inputMeshP.getValue(inputMeshV);
	//inputmesh
	MFnMesh meshFn(inputMeshV);
	MPointArray inPoint;
	meshFn.getPoints(inPoint);
	MItMeshPolygon faceIt(inputMeshV);

	//get drawing colors
	MPlug squashColorP(thisMObject(), aSquashColor);
	MObject squashObject;
	squashColorP.getValue(squashObject);
	MFnNumericData squashFn(squashObject);
	
	//squash color
	MPlug transparentP(thisMObject(), aIsTransparent);
	float transparentV;
	transparentP.getValue(transparentV);

	float tempColor[] = { 0,0,0,1 };
	squashFn.getData(tempColor[0], tempColor[1], tempColor[2]);
	double squashColorV[] = { tempColor[0], tempColor[1], tempColor[2], transparentV};

	//stretchColor
	MPlug stretchColorP(thisMObject(), aStretchColor);
	MObject stretchObject;
	stretchColorP.getValue(stretchObject);
	MFnNumericData stretchFn(stretchObject);

	stretchFn.getData(tempColor[0], tempColor[1], tempColor[2]);
	double stretchColorV[] = { tempColor[0], tempColor[1], tempColor[2], transparentV};

	//color multiplier
	MPlug intensityP(thisMObject(), aIntensity);
	double intensityV;
	intensityP.getValue(intensityV);

	//lineWidth
	//MPlug lineWidthP(thisMObject(), aLineWidth);
	//float lineWidthV;
	//lineWidthP.getValue(lineWidthV);

	if (stressMapValues.length() != inPoint.length())
	{
		return;
	}
	//*******************************************
	//      initialize the opengl
	//*******************************************
	//glStart
	view.beginGL();
	//setup states
	glPushAttrib(GL_CURRENT_BIT);
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLineWidth(2.0);
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
	glColor3f(solidColor.r, solidColor.g, solidColor.b);
	faceIt.reset();
	std::vector<int> edgesDone;
	int size = meshFn.numEdges();
	edgesDone.resize(size);
	for (int i = 0; i < size; i++)
	{
		edgesDone[i] = 0;
	}
	//loop the faces
	int len;
	int vtx1, vtx2;
	MIntArray facePoint;
	MIntArray edges;

	for (; faceIt.isDone() != 1; faceIt.next())
	{
		//draw the edges
		faceIt.getEdges(edges);
		//get the vertices
		faceIt.getVertices(facePoint);

		//loop
		len = edges.length();
		for (int e = 0; e < len; e++)
		{
			/*edges are in the same order of the points
			given back which means that the first edge will have points
			index point[0] and point [1]

			check if we are not at the last edge we use point n and n+1.
			otherwise use the last and first 
			*/
			
			if (e != (len - 1))
			{
				vtx1 = facePoint[e];
				vtx2 = facePoint[e + 1];
			}
			else
			{
				vtx1 = facePoint[e];
				vtx2 = facePoint[0];
			}
			glBegin(GL_LINES);

			//draw the points
			stressLine(inPoint[vtx1],
						stressMapValues[vtx1],
						squashColorV,
						stretchColorV,
						intensityV);

			stressLine(inPoint[vtx2],
				stressMapValues[vtx2],
				squashColorV,
				stretchColorV,
				intensityV);
			//end drawing
			glEnd();
			//mark the edge drawn
			edgesDone[edges[e]] = 1;
		}
	}

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	view.endGL();
}


void StressMap::stressLine(MPoint& p,
	double& stress,
	const double* squashColor,
	const double* stretchColor,
	const double& mult)
{
	//main method that creates the lines for all the edges on the mesh

	//check if the stress1 is greater than 0, if so this means it is stretched
	// else squashed
	if (stress >= 0)
	{
		// exceding 1 max color
		if (stress > 1)
		{
			glColor4f(stretchColor[0],
				stretchColor[1],
				stretchColor[2],
				stretchColor[3]);
		}
		//scale the color amount by the stress and multiplier to blend the two colors
		else
		{
			
			double amount = stress;
			glColor4f(stretchColor[0] * amount * mult,
				stretchColor[1] * amount * mult,
				stretchColor[2] * amount * mult,
				stretchColor[3]);
		}
	}
	else
	{
		if (stress <= -0.95)
		{
			glColor4f(squashColor[0],
				squashColor[1],
				squashColor[2],
				squashColor[3]);
		}
		//scale the color amount by the stress and multiplier to blend the two colors
		else
		{
			
			double amount = -1 * stress;
			glColor4f(squashColor[0] * amount * mult,
				squashColor[1] * amount * mult,
				squashColor[2] * amount * mult,
				squashColor[3]);
		}
	}
	glVertex3f(0 + p.x, 0 + p.y, 0 + p.z);
}



void StressMap::buildConnectTree(std::vector<StressPoint>&pointTree,
								MDoubleArray &stressMapValues,
								MObject referenceMesh)
{
	//builds the connected neighbour array for the mesh

	//clear the array to free the memory
	pointTree.clear();
	//clear the stress values
	stressMapValues.clear();

	//initialize the mesh functions
	MItMeshVertex iter(referenceMesh);
	MFnMesh meshFn(referenceMesh);
	//get the mesh points
	MPointArray points;
	meshFn.getPoints(points);
	//need to create a copy of the point array to work with
	std::copy(points);

	int size = points.length();
	//allocate memory for the arrays
	pointTree.resize(size);
	stressMapValues.setLength(size);

	for (unsigned int i = 0; i < points.length(); i++, iter.next())
	{
		//current point 
		StressPoint pnt;

		MIntArray vtxs;
		//get the neighbours and store them in stressPoint class 
		iter.getConnectedVertices(vtxs);
		pnt.neighbours = vtxs;
		pnt.size = vtxs.length();
		pointTree[i] = pnt;
		stressMapValues[i] = 0;

	}

}
