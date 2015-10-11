/*
	
*/
#ifndef VERTSNAPDEFORMER_H
#define VERTSNAPDEFORMER_H


#include <maya/MPxDeformerNode.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnMesh.h>
#include <maya/MDataBlock.h>
#include <maya/MItGeometry.h>
#include <maya/MPoint.h>
#include <maya/MFnIntArrayData.h>
#include <maya/MPointArray.h>
#include <maya/MMatrix.h>
#include <maya/MGlobal.h>
#include <maya/MItMeshPolygon.h>
#include <maya/MDataHandle.h>


class VertSnapDeformer : public MPxDeformerNode
{
public : VertSnapDeformer();
	
	virtual MStatus deform(MDataBlock& dataBlock,
							MItGeometry& itGeo,
							const MMatrix& localToWorldMatrix,
							unsigned int geomIndex);
	//determines if the data should be saved or not
	virtual MStatus shouldSave(const MPlug& plug, bool& result);
	static void*	creator();
	static MStatus	initialize();
	/*
		Stores the node Id
	*/
	static MTypeId id;
	/*
		This attribute stores the mesh to attach to the driver mesh
	*/
	static MObject aReferenceMesh;
	/*
		This attribute is for storing the mesh that will be the driver
	*/
	static MObject aDriverMesh;
	/*
		This attribute stores all the id mappings
	*/
	static MObject aIdMapping;
	/*
		This attribute will recalulate the id mapping 
	*/
	static MObject aRebind;

private:
	//methods
	//for creating / initalizing the vertex aasignment
	void initData(MObject& driverMesh,
				  MPointArray& deformerPoints,
				  MIntArray& bindArray,
				  MObject& attribute);

	void ensureIndexes(MObject& attribute, int indexSize);
	//variables
	unsigned int elemCount;
	MIntArray bindArray;
	bool initialized;

};


#endif // #VERTSNAPDEFORMER_H
