#include "vertSnapDeformer.h"

#define BIG_DIST 99999


MTypeId	VertSnapDeformer::id(0x00124509);
MObject VertSnapDeformer::aReferenceMesh;
MObject VertSnapDeformer::aIdMapping;
MObject VertSnapDeformer::aDriverMesh;
MObject VertSnapDeformer::aRebind;



VertSnapDeformer::VertSnapDeformer()
{
	//constructor
	//determines if the node is first time it's being run(initialized)
	initialized = 0;
	//number of vertices
	elemCount = 0;
	//an array for id association
	bindArray = MIntArray();
}


void* VertSnapDeformer::creator()
{
	return new VertSnapDeformer();
}

MStatus	VertSnapDeformer::deform(MDataBlock& dataBlock,
								MItGeometry& itGeo,
								const MMatrix& localToWorldMatrix,
								unsigned int geomIndex)
{
	MStatus status;
	MPlug driverMeshPlug(thisMObject(), aDriverMesh);
	if (driverMeshPlug.isConnected() == false)
	{
		return MS::kNotImplemented;
	}

	//get driverMesh
	MObject oDriverMesh = dataBlock.inputValue(aDriverMesh).asMesh();
	//get vertex mapping
	MArrayDataHandle mMapData = dataBlock.inputArrayValue(aIdMapping);
	mMapData.jumpToArrayElement(0);
	//get the envelope
	double env = dataBlock.inputValue(envelope).asFloat();
	bool rebindV = dataBlock.inputValue(aRebind).asBool();

	if (env == 0.0f || initialized == 0)
	{
		return MS::kNotImplemented;
	}

	
	//get vertices in world space
	MPointArray	driverPnts;
	MFnMesh fnMesh(oDriverMesh, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	fnMesh.getPoints(driverPnts, MSpace::kWorld);
	
	// get input point
	MPointArray pos;
	itGeo.allPositions(pos, MSpace::kWorld);

	//if rebind then recalulate vert association
	if (rebindV == 1)
	{
		initData(oDriverMesh, pos, bindArray, aIdMapping);
	}
	//
	if (elemCount == 0)
	{
		elemCount = itGeo.exactCount();
	}

	
	return MS::kSuccess;
}

MStatus	VertSnapDeformer::initialize()
{	
	//main  function for specifying node attribute's
	MStatus status;
	MFnTypedAttribute	tAttr;
	MFnNumericAttribute nAttr;
	//rebinding attribute
	aRebind = nAttr.create("rebind", "rbn", MFnNumericData::kBoolean, 0);
	nAttr.setKeyable(true);
	nAttr.setWritable(true);
	addAttribute(aRebind);
	//mesh to reference
	aReferenceMesh = tAttr.create("ReferenceMesh", "ReferenceMesh", MFnData::kMesh);
	addAttribute(aReferenceMesh);
	//stores our vertex assignment
	aIdMapping = nAttr.create("vertexMapping", "vertexMapping", MFnNumericData::kInt, 0);
	nAttr.setHidden(true);
	nAttr.setArray(true);
	nAttr.setStorable(true);
	nAttr.setConnectable(false);
	addAttribute(aIdMapping);
	//driving mesh
	aDriverMesh = tAttr.create("driverMesh", "drm", MFnData::kMesh);
	addAttribute(aDriverMesh);

	attributeAffects(aDriverMesh, outputGeom);
	attributeAffects(aIdMapping, outputGeom);

	MGlobal::executeCommand("makepaintable -attrType multiFloat -sm deformer snapDeformer weights");

	return MS::kSuccess;
}

void VertSnapDeformer::initData(MObject& driverMesh, MPointArray& deformerPoints, MIntArray& bindArray, MObject& attribute)
{
	//get size of the mesh and set the array size
	int count = deformerPoints.length();
	bindArray.setLength(count);

	//declare needed functions sets and get all the points
	MFnMesh meshFn(driverMesh);
	MItMeshPolygon faceIter(driverMesh);
	MPointArray driverPoints;
	meshFn.getPoints(driverPoints, MSpace::kWorld);

	//declare all the needed variables of the loop 
	MPlug attrPlug(thisMObject(), attribute);
	MDataHandle handle;
	MPoint closest;
	int closestFace, oldIndex, minid;
	unsigned int v;
	MIntArray vertices;
	double minDist, dist;
	MVector base, end, vec;

	for (int i = 0; i < count; i++)
	{
		//get the closest face
		meshFn.getClosestPoint(deformerPoints[i],
									closest,
									MSpace::kWorld,
									&closestFace);
		//find the closest vertex
		faceIter.setIndex(closestFace, oldIndex);
		vertices.setLength(0);
		faceIter.getVertices(vertices);

		//convert the Mpoint to a vector
		base = MVector(closest);
		minDist = BIG_DIST;

		for (v = 0; v < vertices.length(); v++)
		{
			//this is the end vector
			end = MVector(driverPoints[vertices[v]]);
			//build the vector
			vec = end - base;
			dist = vec.length();
			//check if the distance is the shortest
			if (dist < minDist)
			{
				minDist = dist;
				minid = vertices[v];

			}

		}
		//store the result in the array and the attribute
		bindArray[i] = int(minid);
		attrPlug.selectAncestorLogicalIndex(i, attribute);
		attrPlug.getValue(handle);
		attrPlug.setValue(minid);

	}
	//set the controller variable
	initialized = 1;
	elemCount = count;

}

void VertSnapDeformer::ensureIndexes(MObject& attribute, int indexSize)
{

}

MStatus VertSnapDeformer::shouldSave(const MPlug& plug, bool& result)
{
	MStatus status = MS::kSuccess;
	result = true;
}