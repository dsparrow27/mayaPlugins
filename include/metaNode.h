#pragma once

#include "maya/MPxNode.h"
#include "maya/MDataBlock.h"

class MetaNode: public MPxNode
{
public:
	virtual void postConstructor();
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
	static void* creator() { return new MetaNode(); };
	virtual const int schedulingType() { return kParallel; };
	static MStatus initialize();
	static MTypeId kId;
	static MString kName;

};