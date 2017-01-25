#include "metaNode.h"

void MetaNode::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus MetaNode::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	return MS::kSuccess;
}
MStatus MetaNode::initialize()
{
	return MS::kSuccess;
}

