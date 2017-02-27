#include <maya/MFnPlugin.h>
#include <maya/MString.h>

#include "nodeId.h"
#include "pushDeformer.h"
#include "pointOnCurve.h"
#include "scalarOps.h"
#include "angularOps.h"
#include "vectorOps.h"
#include "dummies.h"
#include "parentSingle.h"
#include "matrixOps.h"
#include "aimNode.h"

const char* kAUTHOR = "David Sparrow";
const char* kVERSION = "1.1.0";
const char* kREQUIRED_API_VERSION = "Any";

MTypeId Sum::kId = mayaIds::SUM_ID;
MTypeId Substract::kId = mayaIds::SUBSTRACT_ID;
MTypeId Multiply::kId = mayaIds::MULTIPLY_ID;
MTypeId Divide::kId = mayaIds::DIVIDE_ID;
MTypeId Power::kId = mayaIds::POWER_ID;
MTypeId Clamp::kId = mayaIds::CLAMP_ID;
MTypeId Floor::kId = mayaIds::FLOOR_ID;
MTypeId Ceiling::kId = mayaIds::CEILING_ID;
MTypeId Round::kId = mayaIds::ROUND_ID;
MTypeId Truncate::kId = mayaIds::TRUNCATE_ID;
MTypeId BlendPair::kId = mayaIds::BLENDPAIR_ID;
MTypeId PushDeformer::kId = mayaIds::PUSHDEFORMER_ID;
MTypeId PointOnCurve::kId = mayaIds::POINTONCURVE_ID;
MTypeId MetaNode::kId = mayaIds::METANODE_ID;
MTypeId ParentSingle::kId = mayaIds::PARENTSINGLE_ID;
MTypeId Gaussian::kId = mayaIds::GAUSSIAN_ID;
MTypeId AimNode::kId = mayaIds::AIM_ID;
MTypeId VectorSum::kId = mayaIds::VECTORSUM_ID;
MTypeId VectorSubstract::kId = mayaIds::VECTORSUBSTRACT_ID;
MTypeId VectorMultiply::kId = mayaIds::VECTORMULTIPLY_ID;
MTypeId VectorDivide::kId = mayaIds::VECTORDIVIDE_ID;
MTypeId VectorCross::kId = mayaIds::VECTORCROSS_ID;
MTypeId VectorDot::kId = mayaIds::VECTORDOT_ID;
MTypeId VectorBlendPair::kId = mayaIds::VECTORBLENDPAIR_ID;
MTypeId Remap::kId = mayaIds::REMAP_ID;
MTypeId AngularSine::kId = mayaIds::ANGULARSINE_ID;
MTypeId AngularCosine::kId = mayaIds::ANGULARCOSINE_ID;
MTypeId AngularTan::kId = mayaIds::ANGULARTAN_ID;
MTypeId MatrixBlend::kId = mayaIds::MATRIXBLEND_ID;
MTypeId MatrixConstant::kId = mayaIds::MATRIXCONSTANT_ID;
MTypeId MetaNode::kId = mayaIds::METANODE_ID;
MTypeId MetaSubSystem::kId = mayaIds::METARIGSYSTEMCONSTANT_ID;
MTypeId MetaSupportSystem::kId = mayaIds::METASUPPORTSYSTEMCONSTANT_ID;
MTypeId MetaRigSystem::kId = mayaIds::METARIGSYSTEMCONSTANT_ID;
MTypeId MetaFaceSystem::kId = mayaIds::METAFACESYSTEMCONSTANT_ID;
MTypeId RootNode::kId = mayaIds::ROOTNODECONSTANT_ID;
MTypeId ComponentLayer::kId = mayaIds::COMPONENTLAYERCONSTANT_ID;
MTypeId RigLayer::kId = mayaIds::RIGLAYERCONSTANT_ID;
MTypeId DeformLayer::kId = mayaIds::DEFORMLAYERCONSTANT_ID;
MTypeId GuideLayer::kId = mayaIds::GUIDELAYERCONSTANT_ID;
MTypeId InputLayer::kId = mayaIds::INPUTLAYERCONSTANT_ID;
MTypeId OutputLayer::kId = mayaIds::OUTPUTLAYERCONSTANT_ID;
MTypeId XGroupLayer::kId = mayaIds::XGROUPLAYERCONSTANT_ID;
MTypeId SettingsNode::kId = mayaIds::SETTINGSNODECONSTANT_ID;
MTypeId ControlPanel::kId = mayaIds::CONTROLPANELCONSTANT_ID;

MString Substract::kName = "ds_substract";
MString Sum::kName = "ds_sum";
MString Multiply::kName = "ds_multiply";
MString Divide::kName = "ds_divide";
MString Power::kName = "ds_power";
MString Clamp::kName = "ds_clamp";
MString Floor::kName = "ds_floor";
MString Ceiling::kName = "ds_ceiling";
MString Round::kName = "ds_round";
MString Truncate::kName = "ds_truncate";
MString BlendPair::kName = "ds_blendpair";
MString PushDeformer::kName = "ds_pushDeformer";
MString PointOnCurve::kName = "ds_pointOnCurve";
MString MetaNode::kName = "ds_metaNode";
MString ParentSingle::kName = "ds_parentSingle";
MString Gaussian::kName = "ds_gaussian";
MString AimNode::kName = "ds_aim";
MString VectorSum::kName = "ds_vectorSum";
MString VectorSubstract::kName = "ds_vectorSubstract";
MString VectorMultiply::kName = "ds_vectorMultiply";
MString VectorDivide::kName = "ds_vectorDivide";
MString VectorCross::kName = "ds_vectorCross";
MString VectorDot::kName = "ds_vectorDot";
MString VectorBlendPair::kName = "ds_vectorBlendpair";
MString Remap::kName = "ds_remapScalar";
MString AngularSine::kName = "ds_angularSine";
MString AngularCosine::kName = "ds_angularCosine";
MString AngularTan::kName = "ds_angularTan";
MString MatrixBlend::kName = "ds_MatrixBlend";
MString MatrixConstant::kName = "ds_MatrixConstant";
MString MetaNode::kName = "ds_metaNode";
MString MetaSubSystem::kName = "ds_metaSubSystem";
MString MetaSupportSystem::kName = "ds_metaSupportSystem";
MString MetaRigSystem::kName = "ds_metaRigSystem";
MString MetaFaceSystem::kName = "ds_metaFaceSystem";
MString RootNode::kName = "ds_rootNode";
MString ComponentLayer::kName = "ds_componentLayer";
MString RigLayer::kName = "ds_rigLayer";
MString DeformLayer::kName = "ds_deformLayer";
MString GuideLayer::kName = "ds_guideLayer";
MString InputLayer::kName = "ds_inputLayer";
MString OutputLayer::kName = "ds_outputLayer";
MString XGroupLayer::kName = "ds_xGroupLayer";
MString SettingsNode::kName = "ds_settingsNode";
MString ControlPanel::kName = "ds_controlPanel";


#define REGISTER_NODE(NODE, TYPE)	\
    status = fnPlugin.registerNode(NODE::kName,NODE::kId,NODE::creator, NODE::initialize, TYPE);	\
    CHECK_MSTATUS_AND_RETURN_IT(status);

#define DEREGISTER_NODE(NODE)	\
    status = fnPlugin.deregisterNode(NODE::kId);	\
    CHECK_MSTATUS_AND_RETURN_IT(status);

#define REGISTER_TRANSFORM(NODE, TYPE)	\
	status = fnPlugin.registerTransform(NODE::kName, NODE::kId, NODE::creator, NODE::initialize, NODE::creator, NODE::kId); 	\
	CHECK_MSTATUS_AND_RETURN_IT(status);


MStatus initializePlugin(MObject obj)
{
	MStatus status;
	MFnPlugin fnPlugin(obj, kAUTHOR, kVERSION, kREQUIRED_API_VERSION);
	REGISTER_NODE(Sum, MPxNode::kDependNode);
	REGISTER_NODE(Substract, MPxNode::kDependNode);
	REGISTER_NODE(Multiply, MPxNode::kDependNode);
	REGISTER_NODE(Divide, MPxNode::kDependNode);
	REGISTER_NODE(Power, MPxNode::kDependNode);
	REGISTER_NODE(Clamp, MPxNode::kDependNode);
	REGISTER_NODE(Floor, MPxNode::kDependNode);
	REGISTER_NODE(Ceiling, MPxNode::kDependNode);
	REGISTER_NODE(Round, MPxNode::kDependNode);
	REGISTER_NODE(Truncate, MPxNode::kDependNode);
	REGISTER_NODE(PushDeformer, MPxNode::kDeformerNode);
	REGISTER_NODE(PointOnCurve, MPxNode::kDependNode);
	REGISTER_NODE(MetaNode, MPxNode::kDependNode);
	REGISTER_NODE(BlendPair, MPxNode::kDependNode);
	REGISTER_NODE(ParentSingle, MPxNode::kDependNode);
	REGISTER_NODE(Gaussian, MPxNode::kDependNode);
	REGISTER_NODE(AimNode, MPxNode::kDependNode);
	REGISTER_NODE(VectorSum, MPxNode::kDependNode);
	REGISTER_NODE(VectorSubstract, MPxNode::kDependNode);
	REGISTER_NODE(VectorMultiply, MPxNode::kDependNode);
	REGISTER_NODE(VectorDivide, MPxNode::kDependNode);
	REGISTER_NODE(VectorDot, MPxNode::kDependNode);
	REGISTER_NODE(VectorCross, MPxNode::kDependNode);
	REGISTER_NODE(VectorBlendPair, MPxNode::kDependNode);
	REGISTER_NODE(Remap, MPxNode::kDependNode);
	REGISTER_NODE(AngularSine, MPxNode::kDependNode);
	REGISTER_NODE(AngularCosine, MPxNode::kDependNode);
	REGISTER_NODE(AngularTan, MPxNode::kDependNode);
	REGISTER_NODE(MatrixBlend, MPxNode::kDependNode);
	REGISTER_NODE(MatrixConstant, MPxNode::kDependNode);
	REGISTER_NODE(MetaSubSystem, MPxNode::kDependNode);
	REGISTER_NODE(MetaSupportSystem, MPxNode::kDependNode);
	REGISTER_NODE(MetaRigSystem, MPxNode::kDependNode);
	REGISTER_NODE(MetaFaceSystem, MPxNode::kDependNode);
	REGISTER_NODE(RootNode, MPxNode::kDependNode);
	REGISTER_NODE(SettingsNode, MPxNode::kDependNode);
	REGISTER_NODE(ControlPanel, MPxNode::kDependNode);
	REGISTER_TRANSFORM(ComponentLayer);
	REGISTER_TRANSFORM(RigLayer);
	REGISTER_TRANSFORM(DeformLayer);
	REGISTER_TRANSFORM(GuideLayer);
	REGISTER_TRANSFORM(InputLayer);
	REGISTER_TRANSFORM(OutputLayer);
	REGISTER_TRANSFORM(XGroupLayer);


	return MS::kSuccess;
}

MStatus uninitializePlugin(MObject obj)
{
	MStatus status;
	MFnPlugin fnPlugin(obj, kAUTHOR, kVERSION, kREQUIRED_API_VERSION);
	DEREGISTER_NODE(Sum);
	DEREGISTER_NODE(Substract);
	DEREGISTER_NODE(Multiply);
	DEREGISTER_NODE(Divide);
	DEREGISTER_NODE(Power);
	DEREGISTER_NODE(Clamp);
	DEREGISTER_NODE(Floor);
	DEREGISTER_NODE(Ceiling);
	DEREGISTER_NODE(Round);
	DEREGISTER_NODE(Truncate);
	DEREGISTER_NODE(PushDeformer);
	DEREGISTER_NODE(MetaNode);
	DEREGISTER_NODE(BlendPair);
	DEREGISTER_NODE(ParentSingle);
	DEREGISTER_NODE(Gaussian);
	DEREGISTER_NODE(AimNode);
	DEREGISTER_NODE(VectorSum);
	DEREGISTER_NODE(VectorSubstract);
	DEREGISTER_NODE(VectorMultiply);
	DEREGISTER_NODE(VectorDivide);
	DEREGISTER_NODE(VectorDot);
	DEREGISTER_NODE(VectorCross);
	DEREGISTER_NODE(VectorBlendPair);
	DEREGISTER_NODE(Remap);
	DEREGISTER_NODE(AngularSine);
	DEREGISTER_NODE(AngularCosine);
	DEREGISTER_NODE(AngularTan);
	DEREGISTER_NODE(MatrixBlend);
	DEREGISTER_NODE(MatrixConstant);
	DEREGISTER_NODE(MetaSubSystem);
	DEREGISTER_NODE(MetaSupportSystem);
	DEREGISTER_NODE(MetaRigSystem);
	DEREGISTER_NODE(MetaFaceSystem);
	DEREGISTER_NODE(RootNode);
	DEREGISTER_NODE(SettingsNode);
	DEREGISTER_NODE(ControlPanel);
	DEREGISTER_NODE(ComponentLayer);
	DEREGISTER_NODE(RigLayer);
	DEREGISTER_NODE(DeformLayer);
	DEREGISTER_NODE(GuideLayer);
	DEREGISTER_NODE(InputLayer);
	DEREGISTER_NODE(OutputLayer);
	DEREGISTER_NODE(XGroupLayer);

	return MS::kSuccess;

}
