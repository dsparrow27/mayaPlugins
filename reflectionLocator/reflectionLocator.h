/* 
*/
#ifndef REFLECTIONLOCATOR_H
#define REFLECTIONLOCATOR_H

#include <maya/MPxDeformerNode.h>
#include <maya/MMatrix.h>
#include <maya/MDataBlock.h>
#include <maya/M3dView.h>
#include <maya/MBoundingBox.h>


#include <maya/MFnNumericAttribute.h>
#include <maya/MFnMatrixAttribute.h>



class ReflectionLocator : public MPxDeformerNode
{
public:	ReflectionLocator();

		virtual void*	postConstructor();
		virtual			~ReflectionLocator();
		
		
		//main deformation function
		virtual	MStatus compute(const MPlug& plug, MDataBlock& dataBlock);

		//draw function for all openGl calulations 
		virtual void	draw(M3dView&, const MDagPath&, M3dView::DisplayStyle, M3dView::DisplayStyle);
		virtual			isBound() const;
		virtual			isTransparent() const;
		virtual	MBoundingBox	boundingBox() const;

		// openGl code for a disc shape
		void drawDisc(float radius, int divisions, bool filled);
		void drawReflection(const MPoint& src, const MPoint& dest);

		//standard node creation function
		static void* creator();
		static MStatus initialize();

		static MTypeId id;
		static



};

#endif // !REFLECTIONLOCATOR_H
