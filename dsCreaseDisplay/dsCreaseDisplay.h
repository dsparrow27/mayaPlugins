/* 

*/
#ifndef creaseDisplay_H
#define creaseDisplay_H


#include <maya/MDataHandle.h>
#include <maya/MDataBlock.h>
#include <maya/MBoundingBox.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MPxLocatorNode.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MRampAttribute.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MFnMesh.h>
#include <maya/MUintArray.h>
#include <maya/MPointArray.h>
#include <maya/MDoubleArray.h>
#include <maya/MString.h>
#include <maya/MBoundingBox.h>
#include <maya/MFnData.h>
#include <maya/MGlobal.h>

class CreaseDisplay : public MPxLocatorNode
{
public:	CreaseDisplay();
		virtual void postConstructor();
		virtual	~CreaseDisplay();
		//main deformation function
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
private:
	
	MPointArray startPoints;
	MPointArray endPoints;
	MUintArray creaseEdgesIdArray;
	MDoubleArray creaseValues;

public:
		// node id 
		static MTypeId id;
		static MObject fakeOutput;
		static MObject aInMesh;
		static MObject aIsDrawing;
		static MObject aColorRamp;
		static MObject aTransparent;
		//for draw options, 
		static MObject aDrawOptions;
		static MObject aMinCreaseValue;
		static MObject aMaxCreaseValue;
};

#endif // !creaseDisplay _H
