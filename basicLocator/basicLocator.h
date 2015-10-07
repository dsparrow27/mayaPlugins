/* 

*/
#ifndef basicLocator_H
#define basicLocator_H


#include <maya/MDataHandle.h>
#include <maya/MDataBlock.h>
#include <maya/MBoundingBox.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MPxLocatorNode.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MFloatPointArray.h>


class BasicLocator : public MPxLocatorNode
{
public:	BasicLocator();
		virtual void postConstructor();
		virtual	~BasicLocator();
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
		void drawArrow();
		void drawDisc(float radius, int divisions, bool filled);
		
		//standard node creation function
		static void* creator();
		static MStatus initialize();
		// node id 
		static MTypeId id;
		static MObject aIsDrawing;
		static MObject aShapeType;
		static MObject aShapeColor;
		static MObject aIsTransparent;
};

#endif // !basicLocator_H
