/*
This deformer node drive's a mesh with another based based on closest point
mesh is weight paintable
	todo: kdtree for finding closest point
*/
#ifndef STRESSMAP_H
#define STRESSMAP_H


#include <maya/MFnNumericAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnMesh.h>
#include <maya/MDataBlock.h>
#include <maya/MItGeometry.h>
#include <maya/MPoint.h>
#include <maya/MFnIntArrayData.h>
#include <maya/MPointArray.h>
#include <maya/MDoubleArray.h>
#include <maya/MMatrix.h>
#include <maya/MGlobal.h>
#include <maya/MItMeshPolygon.h>
#include <maya/MDataHandle.h>
#include <vector>
#include <maya/MPxLocatorNode.h>

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

	void buildConnectTree(std::vector<StressPoint>&pointTree, MDoubleArray &stressmapValues, MObject referenceMesh);
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
	MDoubleArray stressMapValues;
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
