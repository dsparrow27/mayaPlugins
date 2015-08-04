#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H

#include <maya/MPxDeformerNode.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MDagModifier.h>
#include <maya/MFnMesh.h>
#include <maya/MGlobal.h>
#include <maya/MMatrix.h>
#include <maya/MItGeometry.h>
#include <maya/MDataHandle.h>
#include <maya/MDataBlock.h>
#include <maya/MPoint.h>


class SphereCollider : public MPxDeformerNode
{
public:	SphereCollider();
		virtual			~SphereCollider();

		static void* creator();

		virtual	MStatus deform(MDataBlock& dataBlock,
								MItGeometry& itGeo,
								const MMatrix& localToWorldMatrix,
								unsigned int geoIndex);

		virtual MObject&	accessoryAttribute() const;
		virtual MStatus		accessoryNodeSetup(MDagModifier& dagMod);


		static MStatus initialize();

		static MObject aCollideMatrix;
		static MObject aDisplace;
		static MTypeId id;



};

#endif // !SPHERECOLLIDER_H
