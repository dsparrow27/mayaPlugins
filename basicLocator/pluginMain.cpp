#include "basicLocator.h"
#include <maya/MFnPlugin.h>


MStatus initializePlugin(MObject obj)
{	/* Register's the plugin and settings for use in maya
	*/
	MStatus status;
	MFnPlugin fnplugin(obj, "David Sparrow", "1.0", "any");


	status = fnplugin.registerNode("basicLocator", 
		BasicLocator::id,
		BasicLocator::creator,
		BasicLocator::initialize,
		MPxNode::kLocatorNode);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	return MS::kSuccess;

	
}

MStatus uninitializePlugin(MObject obj)
{
	/* deregister's the plugin and settings from maya
	*/
	MStatus status;
	MFnPlugin plugin(obj);

	//deregister the deformerNode
	status = plugin.deregisterNode(BasicLocator::id);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	return MS::kSuccess;


}
