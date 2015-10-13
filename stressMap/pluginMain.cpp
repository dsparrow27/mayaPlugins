#include "stressMap.h"
#include <maya/MFnPlugin.h>


MStatus initializePlugin(MObject obj)
{
	MStatus status;
	MFnPlugin fnplugin(obj, "David Sparrow", "1.0", "any");

	//register the deformerNode
	status = fnplugin.registerNode("stressMap",
		StressMap::id,
		StressMap::creator,
		StressMap::initialize,
		StressMap::kDeformerNode);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	return MS::kSuccess;

}

MStatus uninitializePlugin(MObject obj)
{
	MStatus status;
	MFnPlugin plugin(obj);

	status = plugin.deregisterNode(StressMap::id);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	return MS::kSuccess;

}
