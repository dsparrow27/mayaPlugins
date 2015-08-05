#include "reflectionLocator.h"

MObject ReflectionLocator::aPlaneMatrix;
MObject ReflectionLocator::aPoint;
MObject ReflectionLocator::aReflectedPoint;
MObject ReflectionLocator::aReflectionMatrix;
MObject ReflectionLocator::aScale;

ReflectionLocator::ReflectionLocator()
{
}

ReflectionLocator::~ReflectionLocator()
{
}

void* ReflectionLocator::creator()
{
	return new ReflectionLocator;
}


MStatus ReflectionLocator::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus	status;
	// make sure current compute plug is valid 
	if (plug != aReflectedPoint && plug.parent() != aReflectedPoint)
	{
		return MS::kSuccess;
	}

	//get attributes
	MMatrix planeMatrix = dataBlock.inputValue(aPlaneMatrix).asMatrix;
	MMatrix reflectedParentInverse= dataBlock.inputValue(aReflectionMatrix).asMatrix;
	MMatrix inputMatrix = dataBlock.inputValue(aPoint).asMatrix();
	//extract the translation from the matrices 
	MVector planePos = MTransformationMatrix(planeMatrix).getTranslation(MSpace::kPostTransform);
	MVector inputPoint = MTransformationMatrix(inputMatrix).getTranslation(MSpace::kPostTransform);
	double scale = dataBlock.inputValue(aScale).asDouble;

	/////////Reflection math///////
	//formula = R = 2 * (V dot N) * N - V
	//N vector
	MVector normal(0.0, 1.0, 0.0);
	normal *= planeMatrix;
	normal.normalize();

	//vector to reflect
	MVector V = inputPoint - planePos;

	//Reflected vector
	MVector R = 2 * ((normal * V) * normal) - V;

	//reflected point position
	mDestPoint = planePos + R;
		
	
	
	
	return MS::kSuccess;

}