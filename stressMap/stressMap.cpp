#include "StressMap.h"


MTypeId	StressMap::id(0x00124509);



StressMap::StressMap()
{
}

void* StressMap::creator()
{
	return new StressMap();
}

MStatus	StressMap::deform(MDataBlock& dataBlock,
								MItGeometry& itGeo,
								const MMatrix& localToWorldMatrix,
								unsigned int geomIndex)
{
	MStatus status;
	
	return MS::kSuccess;
}

MStatus	StressMap::initialize()
{	
	//main  function for specifying node attribute's
	MStatus status;
	return MS::kSuccess;
}
