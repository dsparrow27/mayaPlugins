#include "bulgeDeformer.h"
#include "blendShapeDeformer.h"
#include "dsSculptDeformer.h"
#include "rippleDeformer.h"
#include <maya/MFnPlugin.h>


MStatus initializePlugin(MObject obj)
{
	MStatus status;
	MFnPlugin fnplugin(obj, "David Sparrow", "1.0", "any");

	//register the deformerNode
	status = fnplugin.registerNode("bulgeDeformer", 
		BulgeDeformer::id, 
		BulgeDeformer::creator,
		BulgeDeformer::initialize,
		MPxNode::kDeformerNode);
	CHECK_MSTATUS_AND_RETURN_IT(status);

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

	return MS::kSuccess;

	
}

MStatus uninitializePlugin(MObject obj)
{
	MStatus status;
	MFnPlugin plugin(obj);

	//deregister the deformerNode
	status = plugin.deregisterNode(BulgeDeformer::id);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	status = plugin.deregisterNode(BlendShapeDeformer::id);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	
	status = plugin.deregisterNode(DsSculptDeformer::id);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	status = plugin.deregisterNode(RippleDeformer::id);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	
	return MS::kSuccess;


}
