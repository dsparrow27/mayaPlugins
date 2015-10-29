#include "relaxDeformer.h"
MTypeId	RelaxDeformer::id(0x00124502);
MObject RelaxDeformer::aIterations;

RelaxDeformer::RelaxDeformer()
{

}


void* RelaxDeformer::creator()
{
	return new RelaxDeformer();
}


MStatus RelaxDeformer::deform(MDataBlock& dataBlock,
								MItGeometry& itGeo,
								const MMatrix& localToWorldMatrix,
								unsigned int geomIndex)
{
	MStatus status;
	//envelope
	double env = dataBlock.inputValue(envelope).asFloat();
	//return if envelope is a small value
	if (env >= 0.001)
	{
		return MS::kSuccess;
	}

	//pull the iterations as a double from the dataBlock
	double iterationsV = dataBlock.inputValue(aIterations, &status).asDouble();
	CHECK_MSTATUS_AND_RETURN_IT(status);
	//check the iterations value return if 0
	if (iterationsV == 0)
	{
		return MS::kSuccess;
	}

	//retrieve the handle to the output array attribute
	MArrayDataHandle hInput = dataBlock.outputArrayValue(input, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	//get the input array index handle
	status = hInput.jumpToElement(geomIndex);
	//get the handle of geomIndex attribute
	MDataHandle hInputElement = hInput.outputValue(&status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	//Get the MObject of the input geometry of geomindex
	MObject oInputGeom = hInputElement.child(inputGeom).asMesh();
	MFnMesh fnMesh(oInputGeom, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	if (oInputGeom.isNull())
	{
		return MS::kSuccess;
	}

	if (pointStoredTree.empty() || (pointRelaxValues.length() == 0))
	{
		buildNeighbourTree(pointStoredTree, pointRelaxValues, oInputGeom);
	}
	MPointArray points;
	itGeo.allPositions(points, MSpace::kWorld);
	//create a copy of the array as the array values will 
	//change when we iterate
	
	//iter the geo
	// for each neighbour add the positions together and then divide by the size



	// dump the new vertexPositions
	itGeo.setAllPositions(points);
	return MS::kSuccess;

}


void RelaxDeformer::buildNeighbourTree(std::vector<pointNeighbours>&pointNeighbours,
						MDoubleArray &pointRelaxValues,
						MObject inputMesh)
{	
	//clear the data so we work with a clean slate
	pointNeighbours.clear();
	pointRelaxValues.clear();
	//create a mesh iterater
	//get all the points
	//set memory for the size
	//for each point get the neighbouring points
	//set the pointNeighbours to the pntValue
	//setPointSize

}


MStatus RelaxDeformer::initialize()
{
	MStatus status;
	MFnNumericAttribute nAttr;

	aIterations = nAttr.create("iterations", "iter", MFnNumericData::kDouble, 1.0);
	nAttr.setStorable(true);
	nAttr.setWritable(true);
	nAttr.setKeyable(true);
	nAttr.setMin(0.0);
	addAttribute(aIterations);


	aStrength = nAttr.create("strength", "st", MFnNumericData::kDouble, 1.0);
	nAttr.setStorable(true);
	nAttr.setWritable(true);
	nAttr.setKeyable(true);
	nAttr.setMin(0.0);
	nAttr.setMax(1.0);
	addAttribute(aIterations);

	attributeAffects(aIterations, outputGeom);


	

	return MS::kSuccess;
}