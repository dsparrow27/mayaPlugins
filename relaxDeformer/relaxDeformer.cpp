#include "relaxDeformer.h"
MTypeId	RelaxDeformer::id(0x00124502);


RelaxDeformer::RelaxDeformer()
{

}


void* RelaxDeformer::creator()
{
	return new RelaxDeformer();
}


MStatus RelaxDeformer::deform(MDataBlock& dataBlock,
								MItGeometry& itGeo,
								const MMatrix& localToWorldMatrix,
								unsigned int geomIndex)
{
	MStatus status;

	return MS::kSuccess;

}


MStatus RelaxDeformer::initialize()
{
	MStatus status;

	return MS::kSuccess;
}