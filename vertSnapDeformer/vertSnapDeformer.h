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

class VertSnapDeformer : public MPxDeformerNode
{
public : VertSnapDeformer();
	
	virtual MStatus shouldSave(const MPlug& plug, bool& result);
	virtual MStatus deform(MDataBlock& dataBlock,
							MItGeometry& itGeo,
							const MMatrix& localToWorldMatrix,
							unsigned int geomIndex);
	static void*	creator();
	static MStatus	initialize();

	static MTypeId id;
	static MObject aReferenceMesh;
	static MObject aDriverMesh;
	static MObject aIdMapping;
	static MObject aRebind;

private:
	//methods
	void initData(MObject& driverMesh, MPointArray& deformerPoints, MIntArray& bindArray, MObject& attribute);
	void ensureIndexes(MObject& attribute, int indexSize);
	//variables
	unsigned int elemCount;
	MIntArray bindArray;
	bool initialized;

};


#endif // #VERTSNAPDEFORMER_H
