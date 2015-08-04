#include "jiggleDeformer.h"

MTypeId	DsJiggle::id(0x00000124);
MObject DsJiggle::aDampingMagitude;
MObject DsJiggle::aTime;
MObject DsJiggle::aStiffnessMagitude;
MObject DsJiggle::aJiggleMap;
MObject DsJiggle::aPerGeometry;
MObject DsJiggle::aWorldMatrix;


DsJiggle::DsJiggle()
{

}

DsJiggle::~DsJiggle()
{

}

void* DsJiggle::creator()
{
	return new DsJiggle();

}

MStatus DsJiggle::deform(MDataBlock& dataBlock,
						MItGeometry& itGeo,
						const MMatrix& localToWorldMatrix,
						unsigned int geoIndex)
{
	// get incoming attributes 
	float env = dataBlock.inputValue(envelope).asFloat();
	float damping = dataBlock.inputValue(aDampingMagitude).asFloat();
	float stiffness = dataBlock.inputValue(aStiffnessMagitude).asFloat();
	MMatrix worldMatrix = dataBlock.inputValue(aWorldMatrix).asMatrix();
	MTime currentTime = dataBlock.inputValue(aTime).asTime();
	MMatrix worldToLocalMatrix = localToWorldMatrix.inverse();
	
	MPointArray points;
	itGeo.allPositions(points);
	MPointArray& currentPoints = currentPoints_[geoIndex];
	MPointArray& previousPoints = previousPoints_[geoIndex];
	MTime& previousTime = previousTime_[geoIndex];

}


MStatus DsJiggle::initialize()
{
	//create the attributes for our jiggle node
	MStatus status;
	MFnNumericAttribute nAttr;
	MFnMatrixAttribute mAttr;
	MFnUnitAttribute uAttr;
	MFnCompoundAttribute cAttr;

	aTime = uAttr.create("time", "time", MFnUnitAttribute::kTime, 0.0, &status);
	addAttribute(aTime);
	attributeAffects(aTime, outputGeom);

	aStiffnessMagitude = nAttr.create("stiffness", "stiffNess", MFnNumericData::kFloat, 1.0, &status);
	nAttr.setKeyable(true);
	nAttr.setMin(0.0);
	nAttr.setMax(1.0);
	addAttribute(aStiffnessMagitude);
	attributeAffects(aStiffnessMagitude, outputGeom);

	aDampingMagitude= nAttr.create("damping", "damping", MFnNumericData::kFloat, 1.0, &status);
	nAttr.setKeyable(true);
	nAttr.setMin(0.0);
	nAttr.setMax(1.0);
	addAttribute(aDampingMagitude);
	attributeAffects(aDampingMagitude, outputGeom);

	aWorldMatrix = mAttr.create("worldMatrix", "worldMatrix");
	addAttribute(aWorldMatrix);
	attributeAffects(aWorldMatrix, outputGeom);

	aJiggleMap = nAttr.create("jiggleMap", "jiggleMap", MFnNumericData::kFloat,0.0, &status);
	nAttr.setMin(0.0);
	nAttr.setMax(1.0);
	nAttr.setArray(true);
	nAttr.setUsesArrayDataBuilder(true);
	addAttribute(aJiggleMap);
	attributeAffects(aJiggleMap, outputGeom);

	aPerGeometry = cAttr.create("perGeometry", "perGeometry", &status);
	cAttr.setArray(true);
	cAttr.addChild(aWorldMatrix);
	cAttr.addChild(aJiggleMap);
	cAttr.setUsesArrayDataBuilder(true);
	addAttribute(aPerGeometry);
	attributeAffects(aPerGeometry, outputGeom);

	return MS::kSuccess;
}
