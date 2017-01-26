#pragma once

#include "utils.h"
#include "maya/MPxNode.h"
#include "maya/MDataBlock.h"
#include "maya/MFnNumericAttribute.h"
#include "maya/MFnTypedAttribute.h"
#include "maya/MVector.h"


class VectorSum : public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new VectorSum(); };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();
	static MTypeId kId;
	static MString kName;

	static MObject aOperands;
	static MObject aResult;
};


class VectorSubstract : public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new VectorSubstract(); };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();
	static MTypeId kId;
	static MString kName;

	static MObject aOperands;
	static MObject aResult;
};

class VectorMultiply : public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new VectorMultiply(); };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();
	static MTypeId kId;
	static MString kName;

	static MObject aVector;
	static MObject aScalar;
	static MObject aResult;
};

class VectorDivide : public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new VectorDivide(); };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();
	static MTypeId kId;
	static MString kName;

	static MObject aValue;
	static MObject aDivisor;
	static MObject aResult;
};

class VectorDot : public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new VectorDot(); };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();
	static MTypeId kId;
	static MString kName;

	static MObject aVecA;
	static MObject aVecB;
	static MObject aResult;
};

class VectorCross : public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new VectorCross(); };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();
	static MTypeId kId;
	static MString kName;

	static MObject aVecA;
	static MObject aVecB;
	static MObject aResult;
};

class VectorBlendPair :public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& data);
	static void* creator() { return new VectorBlendPair; };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();

	static MString kName;
	static MTypeId kId;
	
	static MObject avecA;
	static MObject avecB;
	static MObject ablend;
	static MObject aOutVec;

};
