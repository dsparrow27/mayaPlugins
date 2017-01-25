#pragma once

#include <algorithm>
#include "utils.h"
#include "maya/MPxNode.h"
#include "maya/MDataBlock.h"
#include "maya/MFnNumericAttribute.h"
#include "maya/MFnUnitAttribute.h"
#include "maya/MFnTypedAttribute.h"
#include "maya/MDoubleArray.h"
#include "maya/MFnDoubleArrayData.h"
#include "maya/MAngle.h"
#include "maya/MArrayDataBuilder.h"
#include <cmath>


using namespace std;

class Sum : public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new Sum(); };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();
	static MTypeId kId;
	static MString kName;

	static MObject aOperands;
	static MObject aResult;
};

class Substract : public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new Substract(); };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();
	static MTypeId kId;
	static MString kName;

	static MObject aOperands;
	static MObject aResult;
};

class Multiply : public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new Multiply(); };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();
	static MTypeId kId;
	static MString kName;

	static MObject aOperands;
	static MObject aResult;
};

class Divide : public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new Divide(); };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();
	static MTypeId kId;
	static MString kName;

	static MObject aValue;
	static MObject aDivisor;
	static MObject aResult;
};

class Power : public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new Power(); };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();
	static MTypeId kId;
	static MString kName;

	static MObject aBase;
	static MObject aExponent;
	static MObject aResult;
};

class Clamp :public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator(){return new Clamp();};
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();
	static MTypeId kId;
	static MString kName;

	static MObject aOperands;
	static MObject aResult;
	static MObject aMin;
	static MObject aMax;
};

class Floor : public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new Floor; };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();

	static MString kName;
	static MTypeId kId;

	static MObject aValue;
	static MObject aResult;

};

class Ceiling : public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new Ceiling; };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();

	static MString kName;
	static MTypeId kId;

	static MObject aValue;
	static MObject aResult;

};

class Round : public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new Round; };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();

	static MString kName;
	static MTypeId kId;

	static MObject aValue;
	static MObject aResult;

};

class Truncate : public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new Truncate; };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();

	static MString kName;
	static MTypeId kId;

	static MObject aValue;
	static MObject aResult;

};
class BlendPair :public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new BlendPair; };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();

	static MString kName;
	static MTypeId kId;

	static MObject aBlend;
	static MObject aValueA;
	static MObject aValueB;
	static MObject aResult;
};
class Gaussian :public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new Gaussian; };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();

	static MString kName;
	static MTypeId kId;

	static MObject aResult;
	static MObject aInValue; //x
	static MObject aMagnitude; //a
	static MObject aMean;//b
	static MObject aVariance; //c
};
class Remap :public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new Remap; };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();

	static MString kName;
	static MTypeId kId;

	static MObject aResult;
	static MObject aInValue;
	static MObject aOldMin;
	static MObject aOldMax;
	static MObject aNewMin;
	static MObject aNewMax;
};


//sign
//negate
//reciprocal
//log
//squareroot
//cubric root

