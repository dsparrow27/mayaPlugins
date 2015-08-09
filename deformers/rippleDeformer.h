/* real simple ripple deformer ported from my python version nothing special it was the first 
plugin node i created :D
*/
#ifndef RIPPLEDEFORMER_H
#define RIPPLEDEFORMER_H


#include <maya/MPxDeformerNode.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MDataBlock.h>
#include <maya/MItGeometry.h>
#include <maya/MMatrix.h>
#include <maya/MGlobal.h>
#include <maya/MFnMesh.h>
#include <maya/MFloatVectorArray.h>
#include <maya/MDataHandle.h>
#include <maya/MVector.h>
#include <maya/MPoint.h>



class RippleDeformer : public MPxDeformerNode
{
public:
	RippleDeformer();
	virtual ~RippleDeformer();

	virtual MStatus deform(MDataBlock& dataBlock,
							MItGeometry& itGeo,
							const MMatrix& localToWorldMatrix,
							unsigned int geomIndex);
	static void* creator();
	static MTypeId id;
	static MStatus	initialize();

	static MObject	aAmplitude;
	static MObject	aDisplace;

};

#endif // !RIPPLEDEFORMER_H
