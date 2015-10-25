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
VertSnapDeformer::~VertSnapDeformer()
{

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
	//return if driver mesh not connected
	MPlug driverMeshPlug(thisMObject(), aDriverMesh);
	if (driverMeshPlug.isConnected() == false)
	{
		return MS::kNotImplemented;
	}

	//get driverMesh
	MObject oDriverMesh = dataBlock.inputValue(aDriverMesh, &status).asMesh();
	CHECK_MSTATUS_AND_RETURN_IT(status);
	//get vertex mapping
	MArrayDataHandle mMapData = dataBlock.inputArrayValue(aIdMapping, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	mMapData.jumpToArrayElement(0);
	//get the envelope
	double env = dataBlock.inputValue(envelope, &status).asFloat();
	CHECK_MSTATUS_AND_RETURN_IT(status);
	bool rebindV = dataBlock.inputValue(aRebind, &status).asBool();
	CHECK_MSTATUS_AND_RETURN_IT(status);
	
	if (env == 0.0)
	{
		return MS::kSuccess;
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
		elemCount = itGeo.exactCount(&status);
		CHECK_MSTATUS_AND_RETURN_IT(status);
	}

	int arrayLength = bindArray.length();
	if (elemCount != arrayLength || initialized == 0 || arrayLength == 0)
	{
		//read from attribute 
		ensureIndexes(aIdMapping, itGeo.exactCount());

		//loop the attribute and read the value
		MArrayDataHandle idsHandle = dataBlock.inputArrayValue(aIdMapping, &status);
		CHECK_MSTATUS_AND_RETURN_IT(status);
		idsHandle.jumpToArrayElement(0);

		int count = itGeo.exactCount(&status);
		CHECK_MSTATUS_AND_RETURN_IT(status);
		bindArray.setLength(count);
		for (int i=0; i<count; i++, idsHandle.next())
		{
			bindArray[i] = idsHandle.inputValue(&status).asInt();
			CHECK_MSTATUS_AND_RETURN_IT(status);

		}
		//set value in controller variables
		elemCount = count;
		initialized = 1;
	}
	if (elemCount != itGeo.exactCount())
	{
		MGlobal::displayError("MisMatch between saved bind index and current mesh vertex, please rebind");
		return MS::kSuccess;
	}
	
	//loop all the elements and set the size
	MVector delta, current, target;
	float w;
	for (unsigned int i=0; i<elemCount; i++)
	{
		
		//compute the delta from the input position and final position
		delta = driverPnts[bindArray[i]] - pos[i];
		//scale the vector to calculate envelopes
		pos[i] = pos[i] + (delta * env );
	}
	//dump all vertex positions
	itGeo.setAllPositions(pos);

	return MS::kSuccess;
}

MStatus	VertSnapDeformer::initialize()
{	
	//main  function for specifying node attribute's
	MStatus status;
	MFnTypedAttribute	tAttr;
	MFnNumericAttribute nAttr;
	//rebinding attribute
	aRebind = nAttr.create("rebind", "rbn", MFnNumericData::kBoolean, 0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setKeyable(true);
	nAttr.setStorable(true);
	addAttribute(aRebind);
	//stores our vertex assignment
	aIdMapping = nAttr.create("vertexMapping", "vertexMapping", MFnNumericData::kInt, 0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	nAttr.setArray(true);
	nAttr.setKeyable(true);
	nAttr.setStorable(true);
	addAttribute(aIdMapping);
	//driving mesh
	aDriverMesh = tAttr.create("driverMesh", "drm", MFnData::kMesh);
	tAttr.setKeyable(true);
	tAttr.setStorable(true);
	addAttribute(aDriverMesh);

	attributeAffects(aDriverMesh, outputGeom);
	attributeAffects(aRebind, outputGeom);

	MGlobal::executeCommand("makePaintable -attrType multiFloat -sm deformer meshSnap weights");

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
	
	for (int i=0; i<count; i++)
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

		for (v=0; v<vertices.length(); v++)
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
	//loops the index in order to create them if needed
	MPlug attrPlug(thisMObject(), attribute);
	MDataHandle handle;

	for (int i = 0; i < indexSize; i++)
	{
		attrPlug.selectAncestorLogicalIndex(i, attribute);
		attrPlug.getValue(handle);
	}
}

MStatus VertSnapDeformer::shouldSave(const MPlug& plug, bool& result)
{
	// set each plug to save
	result = true;
	return MS::kSuccess;
}