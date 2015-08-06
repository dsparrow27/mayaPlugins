#ifndef RIPPLEDEFORMER_H
#define RIPPLEDEFORMER_H

#include <math.h>
#include <maya/MPxDeformerNode.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MDataBlock.h>
#include <maya/MItGeometry.h>
#include <maya/MMatrix.h>
#include <maya/MGlobal.h>
#include <maya/MPointArray.h>
#include <maya/MDataHandle.h>
#include <maya/MVector.h>
#include <maya/MPoint.h>



class RippleDeformer : public MPxDeformerNode
{
public:
	RippleDeformer();
	virtual ~RippleDeformer();
	static void* creator();

	virtual MStatus deform(MDataBlock& dataBlock,
							MItGeometry& itGeo,
							const MMatrix& localToWorldMatrix,
							unsigned int geomIndex);
	static MTypeId id;
	static MStatus	initalize();

	static MObject	aAmplitude;
	static MObject	aDisplace;
};

#endif // !RIPPLEDEFORMER_H
