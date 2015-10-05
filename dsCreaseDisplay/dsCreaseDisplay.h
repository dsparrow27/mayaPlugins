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
#include <maya/MRampAttribute.h>
#include <maya/MFnMesh.h>
#include <maya/MUintArray.h>
#include <maya/MDoubleArray.h>


class CreaseDisplay : public MPxLocatorNode
{
public:	CreaseDisplay();
		
		//main deformation function
		virtual	MStatus compute(const MPlug& plug, MDataBlock& dataBlock);

		//draw function for all openGl calulations 
		virtual void draw(M3dView& view, 
							const MDagPath&, 
							M3dView::DisplayStyle style, 
							M3dView::DisplayStatus status);

		virtual	bool isBounded() const;
		virtual	bool isTransparent() const;
		virtual MBoundingBox boundingBox() const;
		//standard node creation function
		static void* creator();
		static MStatus initialize();
		// node id 
		static MTypeId id;
		static MObject aIsDrawing;
		static MObject aColorRamp;
		static MObject aTransparent;
		static MObject aInMesh;

private:
	MUintArray creaseEdgesArray;
	MDoubleArray creaseDataArray;
	//creaseValues;
};

#endif // !creaseDisplay _H
