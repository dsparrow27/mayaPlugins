#ifndef JIGGLEDEFORMER_H
#define JIGGLEDEFORMER_H

#include <maya/MPxDeformerNode.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MItGeometry.h>
#include <maya/MGlobal.h>
#include <maya/MMatrix.h>
#include <maya/MPointArray.h>
#include <maya/MTime.h>
#include <maya/MFnMesh.h>
#include <maya/MFnData.h>
#include <maya/MThreadPool.h>

#include <math.h>
#include <stdio.h>
#include <map>



class DsJiggle : public MPxDeformerNode
{
public:	DsJiggle();
		virtual			~DsJiggle();

		static void* creator();
		
		//main 
		virtual	MStatus deform(MDataBlock& dataBlock,
			MItGeometry& itGeo,
			const MMatrix& localToWorldMatrix,
			unsigned int geoIndex);

		// attribute creator
		static MStatus initialize();

		//autodesk node id
		static MTypeId id;

		//MObjects for node attributes
		static MObject aTime;
		static MObject aDampingMagitude;
		static MObject aStiffnessMagitude;
		static MObject aJiggleMap;
		static MObject aPerGeometry;
		static MObject aWorldMatrix;

private:
	// store for per input geometry
	std::map<unsigned int, MTime> previousTime_;
	std::map<unsigned int, bool> initialized_;
	std::map<unsigned int, MPointArray> previousPoints_;
	std::map<unsigned int, MPointArray> currentPoints_;
	std::map<unsigned int, MPointArray> weights_;
	std::map<unsigned int, MPointArray> jiggleMap_;
	std::map<unsigned int, MIntArray> memberShip_;

};

#endif // !JIGGLEDEFORMER_H
