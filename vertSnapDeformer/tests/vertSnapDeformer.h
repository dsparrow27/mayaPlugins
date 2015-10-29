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

class VertSnapDeformer : public MPxDeformerNode
{
public : VertSnapDeformer();
	virtual ~VertSnapDeformer();

	virtual MStatus deform(MDataBlock& dataBlock,
							MItGeometry& itGeo,
							const MMatrix& localToWorldMatrix,
							unsigned int geomIndex);
	static void*	creator();
	static MStatus	initialize();

	static MTypeId	id;
	static MObject	aSnapMesh;
	static MObject	aMapping;

};


#endif // #VERTSNAPDEFORMER_H
