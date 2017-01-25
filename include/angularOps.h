#pragma once


#include "maya/MPxNode.h"
#include "maya/MDataBlock.h"
#include "maya/MFnNumericAttribute.h"
#include "maya/MFnUnitAttribute.h"
#include "maya/MAngle.h"



class AngularSine :public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new AngularSine; };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();

	static MString kName;
	static MTypeId kId;

	static MObject aResult;
	static MObject aValue;

};
class AngularCosine :public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new AngularCosine; };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();

	static MString kName;
	static MTypeId kId;

	static MObject aResult;
	static MObject aValue;

};
class AngularTan :public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new AngularTan; };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();

	static MString kName;
	static MTypeId kId;

	static MObject aResult;
	static MObject aValue;

};
