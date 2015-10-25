#include "blendShapeDeformer.h"
#include "dsSculptDeformer.h"
#include "rippleDeformer.h"
#include "reflectionLocator.h"
#include "aimNode.h"
#include <maya/MFnPlugin.h>


MStatus initializePlugin(MObject obj)
{
	MStatus status;
	MFnPlugin fnplugin(obj, "David Sparrow", "1.0", "any");

	//register the deformerNode

	status = fnplugin.registerNode("blendShapeDeformer", 
		BlendShapeDeformer::id, 
		BlendShapeDeformer::creator,				
		BlendShapeDeformer::initialize,
		MPxNode::kDeformerNode);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	status = fnplugin.registerNode("dsSculptDeformer", 
		DsSculptDeformer::id,
		DsSculptDeformer::creator,
		DsSculptDeformer::initialize,
		MPxNode::kDeformerNode);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	
	
	status = fnplugin.registerNode("rippleDeformer",
		RippleDeformer::id,
		RippleDeformer::creator,
		RippleDeformer::initialize,
		MPxNode::kDeformerNode);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	status = fnplugin.registerNode("reflectionLocator",
		RippleDeformer::id,
		RippleDeformer::creator,
		RippleDeformer::initialize,
		MPxNode::kLocatorNode);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	status = fnplugin.registerNode("aimNode",
		RippleDeformer::id,
		RippleDeformer::creator,
		RippleDeformer::initialize,
		MPxNode::kDependNode);
	CHECK_MSTATUS_AND_RETURN_IT(status);
<<<<<<< HEAD
	//vertSnap command and deformer
=======
>>>>>>> 0e6e6e9da3aa017d9a2a61278a85de73b079ca7d

	return MS::kSuccess;

	
}

MStatus uninitializePlugin(MObject obj)
{
	MStatus status;
	MFnPlugin plugin(obj);

	//deregister the deformerNode
	status = plugin.deregisterNode(BlendShapeDeformer::id);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	
	status = plugin.deregisterNode(DsSculptDeformer::id);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	status = plugin.deregisterNode(RippleDeformer::id);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	status = plugin.deregisterNode(ReflectionLocator::id);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	status = plugin.deregisterNode(AimNode::id);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	return MS::kSuccess;


}
