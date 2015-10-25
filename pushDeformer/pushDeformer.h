#ifndef PUSHDEFORMER_H
#define PUSHDEFORMER_H

#include <maya/MPxDeformerNode.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MItGeometry.h>
#include <maya/MMatrix.h>
#include <maya/MDataBlock.h>
#include <maya/MGlobal.h>
#include <maya/MFnMesh.h>
#include <maya/MFloatVectorArray.h>
#include <maya/MPoint.h>
#include <maya/MPointArray.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnDoubleArrayData.h>


class PushDeformer : public MPxDeformerNode
{
public:	PushDeformer();

	static void* creator();

	virtual	MStatus deform(MDataBlock& dataBlock,
							MItGeometry& itGeo,
							const MMatrix& localToWorldMatrix,
							unsigned int geoIndex);

	static MStatus initialize();

	static MTypeId id;

	static MObject aAmount;
	static MObject aStressMap;
	static MObject aUseStress;


};

#endif // !BULGEDEFORMER_H