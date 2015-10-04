#include "dsCreaseDisplay.h"
#include <maya/MFnPlugin.h>


MStatus initializePlugin(MObject obj)
{	/* Register's the plugin and settings for use in maya
	*/
	MStatus status;
	MFnPlugin fnplugin(obj, "David Sparrow", "1.0", "any");


	status = fnplugin.registerNode("creaseDisplay", 
		CreaseDisplay::id,
		CreaseDisplay::creator,
		CreaseDisplay::initialize,
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
	status = plugin.deregisterNode(CreaseDisplay::id);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	return MS::kSuccess;


}
