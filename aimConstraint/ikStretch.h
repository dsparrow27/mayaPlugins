/* node brief

@Author : David Sparrow
@Date : 17/09/2015
@Version : 1.0.0 //major.minor.patch
@NodeName : ikStretch
@AutodeskID : 0x00124506
@Details:
		This node is a collapsed version of the dg graph for a stretch ik 
		use's translation for stretch
		includes:
				up and down stretch (order of dag)
				sliding
				locking
				globalScale

@Mel command : createNode ikStretch;

@todo : implement smooth inverse kinematics
*/

#ifndef ikStretch_H
#define ikStretch_H

#include <maya/MPxNode.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnNurbsCurve.h>
#include <maya/MPoint.h>
#include <maya/MMatrix.h>
#include <maya/MVector.h>
#include <maya/MFnMatrixAttribute.h>

class IkStretch : public MPxNode
{
public:
		//standard node creation functions
		static void*	creator();
		static MStatus	initialize();
		IkStretch();

		//main compute function
		virtual	MStatus compute(const MPlug& plug, MDataBlock& dataBlock);


public:
		// node id 
		static MTypeId id;

		//attribute values that get accessed in the compute function
		/* 
			Attribute for holding the world matrix of the start node of the ik 
		*/
		static MObject aStartMatrix;
		/*
			Attribute for holding the world matrix of the end node of the ik 
		*/
		static MObject aEndMatrix;
		/*
			Attribute for holding the inital length of the first bone
		*/
		static MObject aUpInitLength;
		/*
			ibute for holding the inital length of the second bone
		*/
		static MObject aDownInitLength;
		/*
			Attribute for outputing the scale of the first bone
		*/
		static MObject aUpScale;
		/*
			Attribute for outputing the scale of the second bone
		*/
		static MObject aDownScale;
		/*
			input global stretch
		*/
		static MObject aStretch;
		/*
			input for up bone stretch
		*/
		static MObject aUpStretch;
		/*
			input for down bone stretch
		*/
		static MObject aDownStretch;
		/*
			this attribute output the slide factor for the mid bone
		*/
		static MObject aSlide;
		/*
			this input attribute is for the global scale factor
		*/
		static MObject aGlobalScale;
		/*
			this input attribute is for the poleVector matrix
		*/
		static MObject aPoleVectorMatrix;
		/*
			This input attribute is for pole vector locking
		*/
		static MObject aPoleVectorLock;


};	

#endif // !ikStretch_H
