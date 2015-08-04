#ifndef BLENDSHAPEDEFORMER_H
#define BLENDSHAPEDEFORMER_H

#include <maya/MPxDeformerNode.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnMesh.h>
#include <maya/MPointArray.h>
#include <maya/MGlobal.h>
#include <maya/MMatrix.h>
#include <maya/MItGeometry.h>
#include <maya/MDataHandle.h>
#include <maya/MDataBlock.h>



class BlendShapeDeformer : public MPxDeformerNode
{
public:	BlendShapeDeformer();
		virtual			~BlendShapeDeformer();

	static void* creator();

	virtual	MStatus deform(MDataBlock& dataBlock,
							MItGeometry& itGeo,
							const MMatrix& localToWorldMatrix,
							unsigned int geoIndex);

	static MStatus initialize();

	static MTypeId id;

	static MObject aBlendMesh;
	static MObject aBlendWeight;



};

#endif // !BLENDSHAPEDEFORMER_H
