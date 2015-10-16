/*
@author David Sparrow
@Date 17/10/2015
@version : v1.0.0

node name : stressmap

Details: in order to use this node you need to provide a input mesh which is deforming
		mesh and a reference mesh which is the undeformed mesh used as a reference as 0 stress
		output is a MDoubleArray

*/
#ifndef STRESSMAP_H
#define STRESSMAP_H

#include <vector>
#include <stdlib.h>

#include <maya/MMatrix.h>
#include <maya/MGlobal.h>
#include <maya/MPoint.h>
#include <maya/MPlug.h>

#include <maya/MFnNumericAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnDoubleArrayData.h>
#include <maya/MFnIntArrayData.h>
#include <maya/MFnMesh.h>

#include <maya/MPxLocatorNode.h>
#include <maya/MDataHandle.h>
#include <maya/MDataBlock.h>
#include <maya/MItGeometry.h>
#include <maya/MPointArray.h>
#include <maya/MDoubleArray.h>
#include <maya/MItMeshPolygon.h>
#include <maya/MItMeshVertex.h>

class StressPoint
{
public:
	MIntArray neighbours;
	MDoubleArray neighboursStress;
	int size;
};


class StressMap : public MPxLocatorNode
{
public:	StressMap();
	virtual void postConstructor();
	virtual	~StressMap();
	virtual	MStatus compute(const MPlug& plug, MDataBlock& dataBlock);

	//draw function for all openGl calulations 
	virtual void draw(M3dView& view,
		const MDagPath&,
		M3dView::DisplayStyle style,
		M3dView::DisplayStatus status);

	virtual	bool isBounded() const;
	virtual	bool isTransparent() const;
	//standard node creation function
	static void* creator();
	static MStatus initialize();

	//evaluate the reference mesh
	void buildConnectTree(std::vector<StressPoint>&pointTree, MDoubleArray &stressmapValues, MObject referenceMesh);
	//for drawing the locator
	void stressLine(MPoint& p,
					double& stress,
					const double* squashColor,
					const double* stretchColor,
					const double& mult);

	int firstRun;
	MPointArray referencePos;
	MPointArray inputPos;

	/*
		Stores the node Id
	*/
	static MTypeId id;
	/*
		attribute for determining if locator is drawn
	*/
	static MObject aIsDrawing;
	/*
		attribute for determining if locator is transparent
	*/
	static MObject aIsTransparent;
	/*
		a fake attribute to force maya to evaluate this node
	*/
	static MObject aFakeOut;
	/*
		attribute to store the incoming mesh (deforming mesh)
	*/
	static MObject aInputMesh;
	/*
		attribute to store the reference mesh which will used to get the original edge lengths
	*/
	static MObject aReferenceMesh;
	/*
		the internal attribute to store the point neighbours
	*/
	std::vector<StressPoint> pointStoredTree;
	/*
		to store the stress values
	*/
	MDoubleArray aStressMapValues;
	/*
		the attribute to output the result
	*/
	static MObject aOutput;
	/*
		The attribute to hold the value that multiplies the map values
	*/
	static MObject aMultiplier;
	/*
		the attribute clamp the map values
	*/
	static MObject aClampMax;
	/*
		if the normalize the map values
	*/
	static MObject aNormalize;
	/*
		the color of the squash (probably better user wise to use rampAttribute,
								fine for first run/ debugging though)
	*/
	static MObject aSquashColor;
	/*
		the color of the stretch (probably better user wise to use rampAttribute,
								fine for first run/ debugging though)
	*/
	static MObject aStretchColor;
	/*
		attribute for the color intensity
	*/
	static MObject aIntensity;


};


#endif // #STRESSMAP_H
