#include "sphereCollider.h"
#include <IOSTREAM>

MTypeId	SphereCollider::id(0x00000125);
MObject SphereCollider::aCollideMatrix;
MObject SphereCollider::aDisplace;

SphereCollider::SphereCollider()
{

}

SphereCollider::~SphereCollider()
{

}

void* SphereCollider::creator()
{
	return new SphereCollider();
}

MObject& SphereCollider::accessoryAttribute() const
{
	return aCollideMatrix;
}

MStatus	SphereCollider::accessoryNodeSetup(MDagModifier& dagMod)
{
	MStatus status;

	MObject oLocator = dagMod.createNode("locator", MObject::kNullObj, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	MFnDependencyNode fnLocator(oLocator, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	MPlug plugWorldMatrix = fnLocator.findPlug("worldMatrix", false, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	//need to support instancing 
	//use index 0 for now 
	status = plugWorldMatrix.selectAncestorLogicalIndex(0, plugWorldMatrix.attribute());
	CHECK_MSTATUS_AND_RETURN_IT(status);

	MObject oThis = thisMObject();
	MPlug plugColliderMatrix(oThis, aCollideMatrix);

	status = dagMod.connect(plugWorldMatrix, plugColliderMatrix);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	return MS::kSuccess;
}


MStatus SphereCollider::deform(MDataBlock& dataBlock,
								MItGeometry& itGeo,
								const MMatrix& localToWorldMatrix,
								unsigned int geoIndex)
{
	MStatus status;
	float env = dataBlock.inputValue(envelope).asFloat();
	float displace = dataBlock.inputValue(aDisplace).asFloat();
	MMatrix colliderMatrix = dataBlock.inputValue(aCollideMatrix).asMatrix();
	MMatrix collideInverseMatrix = colliderMatrix.inverse();
	MMatrix worldToLocalMatrix = localToWorldMatrix.inverse();
	
	MPoint point;

	float w;

	
	for (; !itGeo.isDone(); itGeo.next())
	{

		point = itGeo.position();
		MMatrix origPoint = colliderMatrix * worldToLocalMatrix;
		//get the vertex weight value
		w = weightValue(dataBlock, geoIndex, itGeo.index());



		//local to world space calculation per point
		point = (point * localToWorldMatrix) * collideInverseMatrix;

		//calculate distance from collider
		if (MVector(point).length() < 1.0)
		{
			//colliding lets normalize between 0-1
			point = MVector(point).normal();
			if (displace != 0)
			{
				point.x *= displace;
				point.y *= displace;
				point.z *= displace;
			}
		}
		point *= (colliderMatrix * worldToLocalMatrix);
		

		itGeo.setPosition(point);

	}
	return MS::kSuccess;
}


MStatus SphereCollider::initialize()
{
	MStatus status;
	MFnMatrixAttribute mAttr;
	MFnNumericAttribute nAttr;
	aCollideMatrix = mAttr.create("collideMatrix", "collideMatrix");
	addAttribute(aCollideMatrix);
	attributeAffects(aCollideMatrix, outputGeom);
	
	aDisplace = nAttr.create("displace", "displace", MFnNumericData::kFloat, 0.0);
	nAttr.setKeyable(true);
	
	addAttribute(aDisplace);
	attributeAffects(aDisplace, outputGeom);
	
	MGlobal::executeCommand("makePaintable -attrType multiFloat -sm deformer sphereCollide weights");
	return MS::kSuccess;
}