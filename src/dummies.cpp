#include "dummies.h"

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

void MetaSubSystem::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus MetaSubSystem::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	return MS::kSuccess;
}
MStatus MetaSubSystem::initialize()
{
	return MS::kSuccess;
}

void MetaSupportSystem::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus MetaSupportSystem::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	return MS::kSuccess;
}
MStatus MetaSupportSystem::initialize()
{
	return MS::kSuccess;
}

void MetaRigSystem::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus MetaRigSystem::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	return MS::kSuccess;
}
MStatus MetaRigSystem::initialize()
{
	return MS::kSuccess;
}

void MetaFaceSystem::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus MetaFaceSystem::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	return MS::kSuccess;
}
MStatus MetaFaceSystem::initialize()
{
	return MS::kSuccess;
}

void RootNode::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus RootNode::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	return MS::kSuccess;
}
MStatus RootNode::initialize()
{
	return MS::kSuccess;
}

void ComponentLayer::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus ComponentLayer::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	return MS::kSuccess;
}
MStatus ComponentLayer::initialize()
{
	return MS::kSuccess;
}

void RigLayer::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus RigLayer::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	return MS::kSuccess;
}
MStatus RigLayer::initialize()
{
	return MS::kSuccess;
}

void DeformLayer::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus DeformLayer::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	return MS::kSuccess;
}
MStatus DeformLayer::initialize()
{
	return MS::kSuccess;
}

void GuideLayer::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus GuideLayer::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	return MS::kSuccess;
}
MStatus GuideLayer::initialize()
{
	return MS::kSuccess;
}

void InputLayer::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus InputLayer::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	return MS::kSuccess;
}
MStatus InputLayer::initialize()
{
	return MS::kSuccess;
}

void OutputLayer::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus OutputLayer::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	return MS::kSuccess;
}
MStatus OutputLayer::initialize()
{
	return MS::kSuccess;
}

void XGroupLayer::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus XGroupLayer::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	return MS::kSuccess;
}
MStatus XGroupLayer::initialize()
{
	return MS::kSuccess;
}

void SettingsNode::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus SettingsNode::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	return MS::kSuccess;
}
MStatus SettingsNode::initialize()
{
	return MS::kSuccess;
}


void ControlPanel::postConstructor()
{
	this->setExistWithoutInConnections(true);
	this->setExistWithoutOutConnections(true);
}

MStatus ControlPanel::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	return MS::kSuccess;
}
MStatus ControlPanel::initialize()
{
	return MS::kSuccess;
}