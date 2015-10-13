/*
This deformer node drive's a mesh with another based based on closest point
mesh is weight paintable
	todo: kdtree for finding closest point
*/
#ifndef STRESSMAP_H
#define STRESSMAP_H


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


class StressMap : public MPxDeformerNode
{
public : StressMap();
	
	virtual MStatus deform(MDataBlock& dataBlock,
							MItGeometry& itGeo,
							const MMatrix& localToWorldMatrix,
							unsigned int geomIndex);
	static void*	creator();
	static MStatus	initialize();
	/*
		Stores the node Id
	*/
	static MTypeId id;

};


#endif // #STRESSMAP_H
