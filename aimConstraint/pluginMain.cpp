#include "ikStretch.h"
#include <maya/MFnPlugin.h>


MStatus initializePlugin(MObject obj)
{	/* Register's the plugin and settings for use in maya
	*/
	MStatus status;
	MFnPlugin fnplugin(obj, "David Sparrow", "1.0", "any");


	status = fnplugin.registerNode("ikStretch", 
		IkStretch::id,
		IkStretch::creator,
		IkStretch::initialize,
		MPxNode::kDependNode);

	CHECK_MSTATUS_AND_RETURN_IT(status);

	return MS::kSuccess;
}


MStatus uninitializePlugin(MObject obj)
{
	/* deregister's the plugin and settings from maya
	*/
	MStatus status;
	MFnPlugin plugin(obj);

	//deregister the node
	status = plugin.deregisterNode(IkStretch::id);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	return MS::kSuccess;
}
