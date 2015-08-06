/* experiment doing a collision deformer similiar to maya sculpt deformer.

*/
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
#include <maya/MPoint.h>


class DsSculptDeformer : public MPxDeformerNode
{
public:	DsSculptDeformer();
		virtual			~DsSculptDeformer();

		static void* creator();
		//main deformation function
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
