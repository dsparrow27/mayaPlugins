#ifndef RELAXDEFORMER_H
#define RELAXDEFORMER_H

#include <vector>
#include <stdlib.h>

#include <maya/MPxDeformerNode.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MItGeometry.h>
#include <maya/MMatrix.h>
#include <maya/MDataBlock.h>
#include <maya/MGlobal.h>
#include <maya/MFnMesh.h>
#include <maya/MFloatVectorArray.h>
#include <maya/MPoint.h>
#include <maya/MPointArray.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnDoubleArrayData.h>
#include <maya/MIntArray.h>

class pointNeighbours
{
public:
	//for storing the neighbours
	MIntArray neighbours;
	//store the relaxed position
	//neighbourPoint length
	int size;
};


class RelaxDeformer: public MPxDeformerNode
{
public:	RelaxDeformer();

	static void* creator();

	virtual	MStatus deform(MDataBlock& dataBlock,
							MItGeometry& itGeo,
							const MMatrix& localToWorldMatrix,
							unsigned int geoIndex);

	static MStatus initialize();

	static MTypeId id;
	MDoubleArray pointRelaxValues;
	void buildNeighbourTree(std::vector<pointNeighbours>&pointNeighbours, MDoubleArray &pointRelaxValues, MObject inputMesh);
	
	std::vector<pointNeighbours> pointStoredTree;
	/*
		This attribute stores the amount of times to relax
	*/
	static MObject aIterations;
	/*
		the strengh of the relax
	*/
	static MObject aStrength;



};

#endif // !RELAXDEFORMER_H
