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

class AngularSum : public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new AngularSum(); };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();
	static MTypeId kId;
	static MString kName;

	static MObject aOperands;
	static MObject aResult;
};

class AngularSubstract : public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new AngularSubstract(); };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();
	static MTypeId kId;
	static MString kName;

	static MObject aOperands;
	static MObject aResult;
};

class AngularMultiply : public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new AngularMultiply(); };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();
	static MTypeId kId;
	static MString kName;

	static MObject aOperands;
	static MObject aResult;
};

class AngularDivide : public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new AngularDivide(); };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();
	static MTypeId kId;
	static MString kName;

	static MObject aValue;
	static MObject aDivisor;
	static MObject aResult;
};

class AngularPower : public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new AngularPower(); };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();
	static MTypeId kId;
	static MString kName;

	static MObject aBase;
	static MObject aExponent;
	static MObject aResult;
};

class AngularClamp :public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new AngularClamp(); };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();
	static MTypeId kId;
	static MString kName;

	static MObject aOperands;
	static MObject aResult;
	static MObject aMin;
	static MObject aMax;
};

class AngularFloor : public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new AngularFloor; };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();

	static MString kName;
	static MTypeId kId;

	static MObject aValue;
	static MObject aResult;

};

class AngularCeiling : public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new AngularCeiling; };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();

	static MString kName;
	static MTypeId kId;

	static MObject aValue;
	static MObject aResult;

};

class AngularRound : public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new AngularRound; };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();

	static MString kName;
	static MTypeId kId;

	static MObject aValue;
	static MObject aResult;

};

class AngularTruncate : public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new AngularTruncate; };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();

	static MString kName;
	static MTypeId kId;

	static MObject aValue;
	static MObject aResult;

};
class AngularBlendPair :public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new AngularBlendPair; };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();

	static MString kName;
	static MTypeId kId;

	static MObject aBlend;
	static MObject aValueA;
	static MObject aValueB;
	static MObject aResult;
};
class AngularGaussian :public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new AngularGaussian; };
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
class AngularRemap :public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new AngularRemap; };
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

class AngularNegate : public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new AngularNegate; };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();

	static MString kName;
	static MTypeId kId;

	static MObject aOperands;
	static MObject aResult;

};



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
