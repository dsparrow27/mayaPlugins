#include "bulgeDeformer.h"
#include "blendShapeDeformer.h"
#include "sphereCollider.h"
#include <maya/MFnPlugin.h>


MStatus initializePlugin(MObject obj)
{	/* Register's the plugin and settings for use in maya
	*/
	MStatus status;
	MFnPlugin fnplugin(obj, "David Sparrow", "1.0", "any");


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

	status = fnplugin.registerNode("sphereCollide", 
		SphereCollider::id, 
		SphereCollider::creator,	
		SphereCollider::initialize,
		MPxNode::kDeformerNode);
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
	status = plugin.deregisterNode(BulgeDeformer::id);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	status = plugin.deregisterNode(BlendShapeDeformer::id);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	status = plugin.deregisterNode(SphereCollider::id);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	return MS::kSuccess;


}
