/* 
Custom Locator that will reflect a matrix from a plane
Currently doesn't support viewport 2.0
*/
#ifndef REFLECTIONLOCATOR_H
#define REFLECTIONLOCATOR_H

#include <maya/MMatrix.h>
#include <maya/MVector.h>
#include <maya/MPoint.h>
#include <maya/MDataHandle.h>
#include <maya/MDataBlock.h>
#include <maya/M3dView.h>
#include <maya/MBoundingBox.h>
#include <maya/MFloatPointArray.h>

#include <maya/MFnDependencyNode.h>
#include <maya/MPxLocatorNode.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnNumericAttribute.h>



class ReflectionLocator : public MPxLocatorNode
{
public:	ReflectionLocator();

		virtual void	postConstructor();
		virtual			~ReflectionLocator();
		
		
		//main deformation function
		virtual	MStatus compute(const MPlug& plug, MDataBlock& dataBlock);

		//draw function for all openGl calulations 
		virtual void	draw(M3dView& view, const MDagPath&, M3dView::DisplayStyle style, M3dView::DisplayStatus status);
		virtual	bool		isBounded() const;
		virtual	bool		isTransparent() const;
		virtual	MBoundingBox	boundingBox() const;

		// openGl code for a disc shape
		void drawDisc(float radius, int divisions, bool filled);
		void drawReflection(const MPoint& src, const MPoint& dest);

		//standard node creation function
		static void* creator();
		static MStatus initialize();
		// node id 
		static MTypeId id;
		//attribute values that get accessed in the compute function
		static MObject aPlaneMatrix;
		static MObject aPoint;
		static MObject aReflectedPoint;
		static MObject aReflectedParentInverse;
		static MObject aScale;


private:
	//for storing points for openGl access
	MPoint mSrcPoint, mDestPoint, mPlanePoint;


};

#endif // !REFLECTIONLOCATOR_H
