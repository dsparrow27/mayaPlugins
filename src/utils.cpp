#include "utils.h"
using namespace utils;
MTransformationMatrix::RotationOrder utils::rotationOrderByIndex(int rotOrder)
{
	MTransformationMatrix::RotationOrder rotationOrder;

	switch (rotOrder)
	{
	case(MTransformationMatrix::RotationOrder::kXZY):
		rotationOrder = MTransformationMatrix::RotationOrder::kXZY;
		break;
	case(MTransformationMatrix::RotationOrder::kYXZ) :
		rotationOrder = MTransformationMatrix::RotationOrder::kYXZ;
		break;
	case(MTransformationMatrix::RotationOrder::kYZX) :
		rotationOrder = MTransformationMatrix::RotationOrder::kYZX;
		break;
	case(MTransformationMatrix::RotationOrder::kZXY) :
		rotationOrder = MTransformationMatrix::RotationOrder::kZXY;
		break;
	case(MTransformationMatrix::RotationOrder::kZYX) :
		rotationOrder = MTransformationMatrix::RotationOrder::kZYX;
		break;
	default:
		rotationOrder = MTransformationMatrix::RotationOrder::kXYZ;
		break;
	}
	return rotationOrder;
}

float utils::remap(float value, float oldMin, float oldMax, float newMin, float newMax)
{
	return (((value - oldMin) * (newMax - newMin)) / (oldMax - oldMin)) + newMin;
}

bool utils::almostEqual(float x, float y, int tailCount)
{
	return fabsf(x - y) < std::numeric_limits<float>::epsilon() * fabsf(x + y) * tailCount 
		|| fabsf(x - y) < std::numeric_limits<float>::min();
}
float utils::lerp(float goal, float current, float blend)
{
	return (1 - blend) * goal + (blend* current);
}
MVector utils::lerp(MVector goal, MVector current, float blend)
{
	return (1 - blend) * goal + (blend* current);
}