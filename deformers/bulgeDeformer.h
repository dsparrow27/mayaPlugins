#ifndef BULGEDEFORMER_H
#define BULGEDEFORMER_H

#include <maya/MPxDeformerNode.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MItGeometry.h>
#include <maya/MMatrix.h>
#include <maya/MDataBlock.h>
#include <maya/MGlobal.h>
#include <maya/MFnMesh.h>
#include <maya/MFloatVectorArray.h>
#include <maya/MPoint.h>

class BulgeDeformer : public MPxDeformerNode
{
public:	BulgeDeformer();
		virtual			~BulgeDeformer();

	static void* creator();

	virtual	MStatus deform(MDataBlock& dataBlock,
							MItGeometry& itGeo,
							const MMatrix& localToWorldMatrix,
							unsigned int geoIndex);

	static MStatus initialize();

	static MTypeId id;

	static MObject aBulgeAmount;



};

#endif // !BULGEDEFORMER_H
